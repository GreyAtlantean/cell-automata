#include <iostream>
#include <string>
#include <vector>

#include <raylib.h>

#include "../include/grid.h"


void draw_grid(int gridX, int gridY, int w, std::vector<std::vector<int>>& grid);

int main (int argc, char *argv[]) {
	
	std::cout << "test" << std::endl;
	
	int screen_width = 1920;
	int screen_height = 1080;
	
	int grid_width = 1300;
	int grid_height = 1080;

	int gridW = 5;
	int gridX = grid_width / gridW;
	int gridY = grid_height / gridW;

	int steps = 0;
	int stepstaken = 0;
	int updatetime = 1;

	bool paused = false;
	

	Grid grid(grid_width, grid_height, grid_width);
	grid.reset_grid();	
	InitWindow(screen_width, screen_height, "cell auto");
	grid.add_oscillator();
	
	// Create a reference to the gridcells location to avoid memory calls each frame
	std::vector<std::vector<int>>* g = grid.get_cells();

	while (!WindowShouldClose()) {

		// render loop
		BeginDrawing();
		ClearBackground(BLACK);
		draw_grid(gridX, gridY, gridW, *g);
		DrawFPS(grid_width + 20, 20);
		EndDrawing();
		

		// make this update at a fixed interval/time period that is scalable 
		// update loop
		if (!paused && steps == updatetime) {
			grid.update_grid();
			steps = 0;
			if (stepstaken % 15 == 0) {
				grid.add_glider();
			}
			stepstaken++;
		} else {
			steps++;
		}
	}

	CloseWindow();

	return 0;
}
void draw_grid(int gridX, int gridY, int w, std::vector<std::vector<int>>& grid) {
	for (int i = 0; i < gridX; i++) {
		for (int j = 0; j < gridY; j++) {
			Rectangle rec;
			rec.x = i * w + 1;
			rec.y = j * w;
			rec.width = w;
			rec.height = w;
			
			if (grid[i][j]) {
	 			DrawRectangleRec(rec, PURPLE); 
			} else {
	 			DrawRectangleRec(rec, BLACK); 
			}
	  }
	}
}
