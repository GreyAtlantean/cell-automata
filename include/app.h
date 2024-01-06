#pragma once
#include "grid.h"

#include <raylib.h>
#include "../include/raygui.h"

class App {
	public:
		App();
	//	~App();
		
		void run();

		void render_grid(int x, int y, std::vector<std::vector<int>>& grid);
		void handle_ui();

		void handle_input();
		void update_world();

		void setup_ui();

		
		
	private:
		int screen_height, screen_width;
		int grid_height, grid_width;

		int offset;
		
		int render_fromx;
		int render_fromy;
		int grid_dimx;
		int grid_dimy;
		
		int steps_taken;
		
		bool paused;
		bool show_fps;
		bool show_ups;

		int scale;

		float tgt_fps, tgt_ups;
		float curr_f, curr_u;	

		float update_timer, update_period;

		char txt_buf[50];

		Grid cells;
	
};
