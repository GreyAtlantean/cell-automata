#include "../include/grid.h"

#include <raylib.h>
#include <omp.h>

Grid::Grid(int x, int y, int w) {
	grid_x = x;
	grid_y = y;
	grid_w = w;
	
	reset_grid();

}

Grid::Grid() {
	grid_w = 25;
}

void Grid::setup_grid(int x, int y) {
	grid_x = x;
	grid_y = y;

	reset_grid();
}

void Grid::toggle_square(int x, int y) {
	if (is_valid_pos(x, y))
		cells[x][y] = !cells[x][y];
}

void Grid::toggle_on(int x, int y) {
	if (is_valid_pos(x, y))
		cells[x][y] = true;
}

void Grid::toggle_off(int x, int y) {
	if (is_valid_pos(x, y))
		cells[x][y] = false;
}

bool Grid::is_valid_pos(int x, int y) {
	return (x > 0 && x < grid_x && y > 0 && y < grid_y);
}

void Grid::reset_grid() {
	cells = std::vector<std::vector<int>>(grid_x, std::vector<int>(grid_y, false));
}

void Grid::update_grid() {
	copy = cells;
	omp_set_num_threads(4);
	#pragma omp parallel for
	for (int i = 0; i < grid_x; i++) {
		for (int j = 0; j < grid_y; j++) {
			// check neighbours 
			int count = 0;
			for (int k = 0; k < 8; k++) {
				int ni = i + neighbours[k][0];
				int nj = j + neighbours[k][1];
				
				if (ni >= 0 && ni < grid_x && nj >= 0 && nj < grid_y && copy[ni][nj])
					count++;
			}
			if ((count < min_n || count > max_n) && cells[i][j] != false) {
				cells[i][j] = false;
			}
			if (count == n_to_live && cells[i][j] == false) {
				cells[i][j] = true;
			}
		}
	}

}

void Grid::add_oscillator() {
	cells[10][9] = true;
	cells[10][10] = true;
	cells[10][11] = true;
}

void Grid::add_glider() {
	cells[15][9] = true;
	cells[15][10] = true;
	cells[15][11] = true;
	cells[14][11] = true;
	cells[13][10] = true;
}

void Grid::get_rules(int* min, int* max, int* live) {
	*min = min_n;
	*max = max_n;
	*live = n_to_live;
}

void Grid::update_rules(int* min, int* max, int* live) {
	if (*min <= *max) {
		min_n = *min;
	} else {
		*max = *min;
		*min = min_n;
	}

	if (*max >= *min) {
		max_n = *max;
	} else {
		*min = *max;
		*max = max_n;
	}
	
	n_to_live = *live;
	
}

std::vector<std::vector<int>>* Grid::get_cells() {
	return &cells;
}

