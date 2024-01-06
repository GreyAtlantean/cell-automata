#include "../include/app.h"

#include <cstdio>
#include <raylib.h>
#include <iostream>

#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"

App::App() {
	screen_width = 1920;
	screen_height = 1080;

	offset = 100;

	grid_width = 1300;
	grid_height = screen_height;

	scale = 25;

	render_fromx = 0;
	render_fromy = 0;

	grid_dimx = 1000;
	grid_dimy = 1000;

	steps_taken = 0;

	paused = false;
	hide_ui = false;
	show_fps = true;
	show_ups = true;

	tgt_fps = 144.0f;
	tgt_ups = 60.0f;

	update_timer = 0;
	update_period = 1.0 / tgt_ups;
	
	cells.setup_grid(grid_dimx, grid_dimy);

	cells.get_rules(&min_n, &max_n, &n_need);
}

void App::run() {
	
	// Setup window for raylib
	InitWindow(screen_width, screen_height, "cell auto");
	GuiLoadStyleDefault();
	GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
	GuiSetAlpha(1.0f);
	
	// Setup the grid
	cells.reset_grid();
	cells.add_oscillator();

	// Create a reference to the gridcells location to avoid memory calls each frame
	std::vector<std::vector<int>>* cells_ref = cells.get_cells();

	SetTargetFPS(tgt_fps);
	while (!WindowShouldClose()) {
		// handle input 
		handle_input();
		
		// render
		BeginDrawing();

		ClearBackground(BLACK);
		
		int draw_x = (std::min(grid_width / scale, grid_dimx));
		int draw_y = (std::min(grid_height / scale, grid_dimy));
		render_grid(draw_x, draw_y, *cells_ref);
		handle_ui();
		EndDrawing();

		// update world
		update_world();
	}

	CloseWindow();

}

void App::handle_ui() {
	int col_width = 250;
	if (!hide_ui) {
		// Toggle FPS display
		GuiCheckBox ((Rectangle){(float)grid_width + offset, 50,  20, 20}, "Toggle FPS Display", &show_fps);
		// Change target fps
		DrawText("Adjust target FPS", grid_width + offset, 80, 10, GRAY);
		GuiSlider((Rectangle){(float)grid_width + offset, 100, 120, 20}, "T", TextFormat("%2.2f", tgt_fps), &tgt_fps, 60, 360);
		SetTargetFPS(tgt_fps);
		
		// Toggle UPS display
		GuiCheckBox ((Rectangle){(float)grid_width + offset + col_width, 50,  20, 20}, "Toggle UPS Display", &show_ups);
		// Change target ups
		DrawText("Adjust target UPS", grid_width + offset + col_width, 80, 10, GRAY);
		GuiSlider((Rectangle){(float)grid_width + offset + col_width, 100, 120, 20}, "T", TextFormat("%2.2f", tgt_ups), &tgt_ups, 10, 100);
		update_period = 1 / tgt_ups;
		

		
		// Change rules for game
		DrawText("Min neighbours to live", grid_width + offset, 185, 15, GRAY);	
		GuiSpinner((Rectangle){(float)grid_width + offset, 200, 140, 30}, NULL, &min_n, 0, 8, false);
		DrawText("Max neighbours to live", grid_width + offset, 235, 15, GRAY);	
		GuiSpinner((Rectangle){(float)grid_width + offset, 250, 140, 30}, NULL, &max_n, 0, 8, false);
		DrawText("Need neighbours to live", grid_width + offset, 285, 15, GRAY);	
		GuiSpinner((Rectangle){(float)grid_width + offset, 300, 140, 30}, NULL, &n_need, 1, 8, false);
		cells.update_rules(&min_n, &max_n, &n_need);
		
		// Display controls
		DrawText("Controls", grid_width + offset, 400, 30, GRAY);
		DrawText("WASD for camera", grid_width + offset, 430, 25, GRAY);
		DrawText("Left click to add cells", grid_width + offset, 455, 25, GRAY);
		DrawText("Right click to remove cells", grid_width + offset, 480, 25, GRAY);
		DrawText("Scroll for zoom", grid_width + offset, 505, 25, GRAY);
		DrawText("P to toggle pause", grid_width + offset, 530, 25, GRAY);
		DrawText("N to step through (single)", grid_width + offset, 555, 25, GRAY);
		DrawText("G to step through (multiple)", grid_width + offset, 580, 25, GRAY);
		DrawText("R to reset simulation", grid_width + offset, 605, 25, GRAY);
		DrawText("ESC to quit", grid_width + offset, 630, 25, GRAY);
		DrawText("H to toggle UI visibility", grid_width + offset, 655, 25, GRAY);
	}	
	
	// Display info
	if (show_fps)
		DrawFPS(grid_width + offset, 20);
	if (show_ups) {
		snprintf(txt_buf, 50, "%i UPS", (int)tgt_ups);
		DrawText(txt_buf, grid_width + offset + col_width, 20, 20, LIME);
	}
	
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
	DrawLine(grid_width, 0, grid_width, grid_height, PURPLE);
}

void App::update_world() {
	if (!paused) {
		update_timer += GetFrameTime();
	}
	while (!paused && update_timer >= update_period) {
		cells.update_grid();
		if (steps_taken % 15 == 0) {
			cells.add_glider();
		}
		update_timer -= update_period;
		steps_taken++;
	} 	
}

void App::handle_input() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		if (GetMouseX() < grid_width && GetMouseY() < grid_height) {
			int posX = GetMouseX() / scale + render_fromx; 
			int posY = GetMouseY() / scale + render_fromy;
			cells.toggle_on(posX, posY);
		}
	} 
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		if (GetMouseX() < grid_dimx && GetMouseY() < grid_dimy) {	
			int posX = GetMouseX() / scale + render_fromx; 
			int posY = GetMouseY() / scale + render_fromy;
			cells.toggle_off(posX, posY);
		}
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
	
	// Reset the simulation
	if (IsKeyPressed(KEY_R)) {
		cells.reset_grid();
	}

	if (IsKeyPressed(KEY_H)) {
		hide_ui = !hide_ui;
	}

}
