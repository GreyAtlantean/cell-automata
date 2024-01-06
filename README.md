# cell-automata
## Cellular Automata Visualiser

## A basic cellular automata simulator written in C++ with Raylib and Raygui

The default rules are Conway's game of life. They can be minimally changed during the running of the program using the GUI.

### Controls for the program 

WASD - Move camera

Scroll wheel - Zoom in and out

Left click - Add a cell to the grid

Right click - Remove a cell from the grid

P - Toggle pause

N - Take a single step through the simulation

G - Take continuous steps through the simulation

R - Reset the simulation

H - Toggle UI visibility (hide)

F - Toggle Stats visibility FPS/UPS

ESC - Quit the program


### Compilation

This project is built using CMake.

Ensure Raylib and OpenMP is installed on your system.



Whilst in the build folder run the following:

cmake ../src/CMakeLists.txt

make

./cellauto


### Screenshots

![ScreenShot One](/imgs/screenshot1.png?raw=true "Screenshot one")
![ScreenShot Two](/imgs/screenshot2.png?raw=true "Screenshot two")
![ScreenShot Three](/imgs/screenshot3.png?raw=true "Screenshot three")
![ScreenShot Four](/imgs/screenshot4.png?raw=true "Screenshot four")
![ScreenShot Five](/imgs/screenshot5.png?raw=true "Screenshot five")
