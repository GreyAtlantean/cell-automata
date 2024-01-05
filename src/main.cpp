#include <iostream>
#include <string>

#include <raylib.h>
#include <vector>




void draw_grid(int gridX, int gridY, int w, std::vector<std::vector<int>> grid);
void init_grid(std::vector<std::vector<int>>& grid);
void randomise_grid(int X, int Y, std::vector<std::vector<int>>& grid);
void add_oscillator(int X, int Y, std::vector<std::vector<int>>& grid);
void next_step(std::vector<std::vector<int>>& grid, int X, int Y);

int main (int argc, char *argv[]) {
	
	std::cout << "test" << std::endl;
	
	int screen_width = 1920;
	int screen_height = 1080;
	
	int grid_width = 1300;
	int grid_height = 1080;

	int gridW = 20;
	int gridX = grid_width / gridW;
	int gridY = grid_height / gridW;
	
	std::vector<std::vector<int>> cells(gridX, std::vector<int>(gridY));
	init_grid(cells);
	
	InitWindow(screen_width, screen_height, "cell auto");
	SetTargetFPS(1);

	//randomise_grid(gridX, gridY, cells);
	add_oscillator(gridX, gridY, cells);
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		//int fps = GetFPS();
		draw_grid(gridX, gridY, gridW, cells);
		DrawFPS(grid_width + 20, 20);
		EndDrawing();
		
		next_step(cells, gridX, gridY);
	}

	CloseWindow();

	return 0;
}

void init_grid(std::vector<std::vector<int>>& grid) {
	for (auto& row : grid) {
		for (auto& elem : row) {
			elem = false;
		}
	}
}

void randomise_grid(int X, int Y, std::vector<std::vector<int>>& grid) {
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) { 
	  		grid[i][j] = true;
			if ((i + j) % 4) {
				grid[i][j] = false;
			}
	  }
	}
}

void add_oscillator(int X, int Y, std::vector<std::vector<int>>& grid) {
	grid[10][9] = true;
	grid[10][10] = true;
	grid[10][11] = true;
}

void next_step(std::vector<std::vector<int>>& grid, int X, int Y) {
	std::vector<std::vector<int>> copy(grid.begin(), grid.end());

	const int neighbours[8][2] = {
		{-1, -1}, {-1, 0}, {-1,  1},
		{ 0, -1},          { 0,  1},
		{ 1, -1}, { 1, 0}, { 1,  1}
	};

	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			// check neighbours - possible to have eight
			int count = 0;
			for (int k = 0; k < 8; k++) {
				int ni = i + neighbours[k][0];
				int nj = j + neighbours[k][1];
				
				if (ni >= 0 && ni < X && nj >= 0 && nj < Y && copy[ni][nj])
					count++;
			}
			if ((count < 2 || count > 3) && grid[i][j] != false) {
				grid[i][j] = false;
			}
			if (count == 3 && grid[i][j] == false) {
				grid[i][j] = true;
			}
		}

	}

}



void draw_grid(int gridX, int gridY, int w, std::vector<std::vector<int>> grid) {
	for (int i = 0; i < gridX; i++) {
		for (int j = 0; j < gridY; j++) {
			Rectangle rec;
			rec.x = i * w + 1;
			rec.y = j * w;
			rec.width = w;
			rec.height = w;
			
			if (grid[i][j]) {
	 			DrawRectangleRec(rec, GRAY); 
			} else {
	 			DrawRectangleRec(rec, BLACK); 
			}
	  }
	}
}
