#pragma once
#include "grid.h"

#include <raylib.h>
class App {
	public:
		App();
	//	~App();
		
		void run();

		void render_grid(int x, int y, std::vector<std::vector<int>>& grid);
		void render_fps();
		void render_ui();

		void handle_input();
		void update_world();

		
		
	private:
		int screen_height, screen_width;
		int grid_height, grid_width;
		
		int render_fromx;
		int render_fromy;
		int grid_dimx;
		int grid_dimy;
		
		int steps_taken;
		
		bool paused;

		int scale;

		int tgt_fps, tgt_ups;
		
		float update_timer, update_period;

		Grid cells;
	
};
