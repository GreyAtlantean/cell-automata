#include "../include/app.h"
#include <raylib.h>


App::App() {
	screen_width = 1920;
	screen_height = 1080;

	grid_width = 1300;
	grid_height = screen_height;

	scale = 25;

	render_fromx = 0;
	render_fromy = 0;

	grid_dimx = 1000;
	grid_dimy = 1000;

	steps_taken = 0;

	paused = false;

	tgt_fps = 144;
	tgt_ups = 60;

	update_timer = 0;
	update_period = 1.0 / tgt_ups;
	
	cells.setup_grid(grid_dimx, grid_dimy);
}

void App::run() {
	
	// Setup window for raylib
	InitWindow(screen_width, screen_height, "cell testtt auto");

	
	// Setup the grid
	cells.reset_grid();
	cells.add_oscillator();

	// Create a reference to the gridcells location to avoid memory calls each frame
	std::vector<std::vector<int>>* cells_ref = cells.get_cells();

	SetTargetFPS(tgt_fps);
	while (!WindowShouldClose()) {
		// input loop 
		handle_input();
	
		BeginDrawing();
		ClearBackground(BLACK);
		int draw_x = (std::min(grid_width / scale, grid_dimx));
		int draw_y = (std::min(grid_height / scale, grid_dimy));
		render_grid(draw_x, draw_y, *cells_ref);
		DrawFPS(grid_width + 20, 20);
		EndDrawing();

		// update loop
		if (!paused && update_timer >= update_period) {
			cells.update_grid();
			if (steps_taken % 15 == 0) {
				cells.add_glider();
			}
			update_timer -= update_period;
			steps_taken++;
		} 	
		update_timer +=  GetFrameTime();
	}

	CloseWindow();

}

void App::render_grid(int x, int y, std::vector<std::vector<int>>& grid) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			Rectangle rec;
			rec.x = i * scale;
			rec.y = j * scale;
			rec.width = scale;
			rec.height = scale;
			
			if (grid[i + render_fromx][j + render_fromy]) {
	 			DrawRectangleRec(rec, PURPLE); 
			}	  
		}
	}
}

void App::handle_input() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			int posX = GetMouseX() / scale + render_fromx; 
			int posY = GetMouseY() / scale + render_fromy;
			cells.toggle_on(posX, posY);
		} 
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
			int posX = GetMouseX() / scale + render_fromx; 
			int posY = GetMouseY() / scale + render_fromy;
			cells.toggle_off(posX, posY);
		}

		float wheel = GetMouseWheelMove();
		if (wheel != 0) {
			scale += wheel;
			if (scale < 5)
				scale = 5;
			if (scale > 25)
				scale = 25;

	
			render_fromx += wheel * scale;
			render_fromy += wheel * scale;

			if (render_fromy > grid_dimx - grid_height / scale) {
				render_fromy = grid_dimy - grid_height / scale;
			}
			if (render_fromy < 0) {
				render_fromy = 0;
			} 
			
			if (render_fromx > grid_dimx - grid_width / scale) {
				render_fromx = grid_dimx - grid_width / scale;
			}
			if (render_fromx < 0) {
				render_fromx = 0;
			} 

		}

		if (IsKeyPressed(KEY_P)) {
			paused = !paused;
		}
		
		// Move the camera position
		if (IsKeyDown(KEY_W)) {
			if (render_fromy > 0)
				render_fromy--;
		}
		if (IsKeyDown(KEY_A)) {
			if (render_fromx > 0)
				render_fromx--;
		}
		if (IsKeyDown(KEY_S)) {
			if (render_fromy < grid_dimy - grid_height / scale)
				render_fromy++;
		}

		if (IsKeyDown(KEY_D)) {
			if (render_fromx < grid_dimx - grid_width / scale)
				render_fromx++;
		}
		

		// step through the program step by step
		// if G is held down it will be continuous 
		// if N is pressed, it will go through a single step
		if (IsKeyDown(KEY_G) || IsKeyPressed(KEY_N)) {
			paused = true;
			cells.update_grid();
		}

}
