#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>

#include "../include/grid.h"

void draw_grid(int gridX, int gridY, int w, int rendX, int rendY, std::vector<std::vector<int>>& grid);

int main (int argc, char *argv[]) {
	
	std::cout << "test" << std::endl;
	
	int screen_width = 1920;
	int screen_height = 1080;
	
	int grid_width = 1450;
	int grid_height = 1080;

	int scale = 25;


	int gridX = 1000;
	int gridY = 1000;

	int render_fromX = 0;
	int render_fromY = 0;

	int steps = 0;
	int stepstaken = 0;
	int updatetime = 3;

	bool paused = false;
	
	int target_ups = 40;
	int target_fps = 144;
	float update_timer = 0.0;
	float update_period = 1.0 / target_ups;
	
	SetTargetFPS(target_fps);

	Grid grid(gridX, gridY, scale);
	grid.reset_grid();	
	InitWindow(screen_width, screen_height, "cell auto");
	grid.add_oscillator();
	
	// Create a reference to the gridcells location to avoid memory calls each frame
	std::vector<std::vector<int>>* g = grid.get_cells();

	while (!WindowShouldClose()) {
		// input loop 
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			int posX = GetMouseX() / scale + render_fromX; 
			int posY = GetMouseY() / scale + render_fromY;
			grid.toggle_on(posX, posY);
		} 
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
			int posX = GetMouseX() / scale + render_fromX; 
			int posY = GetMouseY() / scale + render_fromY;
			grid.toggle_off(posX, posY);
		}
		

		float wheel = GetMouseWheelMove();
		if (wheel != 0) {
			scale += wheel;
			if (scale < 5)
				scale = 5;
			if (scale > 25)
				scale = 25;

	
			render_fromX += wheel * scale;
			render_fromY += wheel * scale;

			if (render_fromY > gridY - grid_height / scale) {
				render_fromY = gridY - grid_height / scale;
			}
			if (render_fromY < 0) {
				render_fromY = 0;
			} 
			
			if (render_fromX > gridX - grid_width / scale) {
				render_fromX = gridX - grid_width / scale;
			}
			if (render_fromX < 0) {
				render_fromX = 0;
			} 
		

		}

		if (IsKeyPressed(KEY_P)) {
			paused = !paused;
		}
			if (IsKeyDown(KEY_W)) {
			if (render_fromY > 0)
				render_fromY--;
		}
		if (IsKeyDown(KEY_A)) {
			if (render_fromX > 0)
				render_fromX--;
		}
		if (IsKeyDown(KEY_S)) {
			if (render_fromY < gridY - grid_height / scale)
				render_fromY++;
		}

		if (IsKeyDown(KEY_D)) {
			if (render_fromX < gridX - grid_width / scale)
				render_fromX++;
		}
		
		if (IsKeyDown(KEY_G) || IsKeyPressed(KEY_N)) {
			paused = true;
			grid.update_grid();
		}

		// render loop
		BeginDrawing();
		ClearBackground(BLACK);
		int draw_x = (std::min(grid_width / scale, gridX));
		int draw_y = (std::min(grid_height / scale, gridY));
		draw_grid(draw_x, draw_y, scale, render_fromX, render_fromY, *g);
		//grid.render_grid(scale, render_fromX, render_fromY);
		DrawFPS(grid_width + 20, 20);
		EndDrawing();

		// TODO make this update at a fixed interval/time period that is scalable 
		// update loop
		if (!paused && update_timer >= update_period) {
			grid.update_grid();
			if (stepstaken % 15 == 0) {
				grid.add_glider();
			}
			update_timer = 0;
			stepstaken++;
		} 	
		update_timer +=  GetFrameTime();

	}

	CloseWindow();

	return 0;
}
void draw_grid(int x, int y, int w, int rendX, int rendY, std::vector<std::vector<int>>& grid) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			Rectangle rec;
			rec.x = i * w;
			rec.y = j * w;
			rec.width = w;
			rec.height = w;
			
			if (grid[i + rendX][j + rendY]) {
	 			DrawRectangleRec(rec, PURPLE); 
			}	  
		}
	}
}
