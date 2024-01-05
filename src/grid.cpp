#include "../include/grid.h"
#include <iterator>
#include <raylib.h>

Grid::Grid(int x, int y, int w) {
	grid_x = x;
	grid_y = y;
	grid_w = w;

	cells = std::vector<std::vector<int>>(grid_x, std::vector<int>(grid_y, false));

}

void Grid::toggle_square(int x, int y) {
	cells[x][y] = !cells[x][y];
}

void Grid::reset_grid() {
	cells = std::vector<std::vector<int>>(grid_x, std::vector<int>(grid_y, false));
}

void Grid::update_grid() {
	copy = cells;


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
			if ((count < 2 || count > 3) && cells[i][j] != false) {
				cells[i][j] = false;
			}
			if (count == 3 && cells[i][j] == false) {
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

std::vector<std::vector<int>>* Grid::get_cells() {
	return &cells;
}
