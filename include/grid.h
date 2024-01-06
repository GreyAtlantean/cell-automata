#pragma once

#include <vector>

class Grid {
	public:
		Grid();
		Grid(int x, int y, int w);
		// Setup the grid
		void setup_grid(int x, int y);	
		// Update the grid a single step
		void update_grid();
		// Reset the grid 
		void reset_grid();
		// Load the grid from a given file
		void load_grid();
		// Toggle a single square in the grid
		void toggle_square(int x, int y);
		// Toggles a single square on
		void toggle_on(int x, int y);
		// Toggles a single square off
		void toggle_off(int x, int y);
		// Checks whether a given coord is within bounds
		bool is_valid_pos(int x, int y);
		// Add an oscillator
		void add_oscillator();
		// Adds a glider to the grid
		void add_glider();
		// Gets the rules
		void get_rules(int* min, int* max, int* live);
		// Update the rules
		void update_rules(int* min, int* max, int* live);

		// Returns a reference to the cells vector
		std::vector<std::vector<int>>* get_cells();
	private:
		std::vector<std::vector<int>> cells;
		std::vector<std::vector<int>> copy;

		int grid_x = 10;
		int grid_y = 10;
		int grid_w = 20;
		
		// default is conway's game of life
		int min_n = 2;
		int max_n = 3;
		// neighbours needed for a dead cell to become living
		int n_to_live = 3;


		const int neighbours[8][2] = {
			{-1, -1}, {-1, 0}, {-1,  1},
			{ 0, -1},          { 0,  1},
			{ 1, -1}, { 1, 0}, { 1,  1}
		};
};
