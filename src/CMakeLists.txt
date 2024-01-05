cmake_minimum_required(VERSION 3.28)
project(cellauto CXX)

# Find raylib package
find_package(raylib REQUIRED)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}include)

# Set source files
set(SOURCE_FILES
    main.cpp
	grid.cpp
)

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_compile_options(${PROJECT_NAME} PUBLIC
	-Wall
	-Wextra
	-O2
)

# Include raylib headers
include_directories(${raylib_INCLUDE_DIRS})

# Link raylib libraries
target_link_libraries(${PROJECT_NAME} ${raylib_LIBRARIES})
