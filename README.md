# Project Overview

This project is an SDL2-based raycaster that shows a basic 3D-like environment similar to the classic "Wolfenstein 3D" style. The core of this project demonstrates fundamental raycasting techniques and showcases player movement in a 2D grid-based environment rendered in 3D perspective. The program utilizes SDL2 for graphics, event handling, and rendering.

## Features

- **Basic Raycasting:** Casts rays into a grid-based map to simulate 3D projections.
    
- **Player Movement:** WASD keys allow for forward, backward, and rotational player movement within the environment.
    
- **Event Handling:** Simple keypress events are captured to move the player around the map.
    
- **Rendering with SDL2:** Utilizes SDL2 for efficient rendering, real-time graphical updates and frame management.
    

## Technologies Used

- **SDL2:** Handles window creation, rendering, and event processing.
    
- **C Programming Language:** Core logic and raycasting implemented in C.
    
- **Mathematical Computation:** Vector math for raycasting and player movement calculations.

## Project Structure

```
─── src
   ├── draw.c            # Contains functions to render the map and the player
   ├── events.c          # Handles player movement based on key events
   ├── raycast.c         # Core raycasting logic for 3D rendering
   ├── sdl_layer.c       # SDL2 abstractions for window creation, event handling, and rendering
   └── main.c            # Entry point, main game loop, and rendering sequence

```


## Setup and Installation

In the interest of your time I have included already compiled binaries in the `bin/` folder. Whether or not they will work on the platform you're on is a mystery only you can figure out.

- Linux executable: `bin/raycastedbase`

- Windows executable: `bin/raycastedbasewin.exe` (not guaranteed to function as expected, may experience window irregularities)

Read on to see how you can build it on linux yourself!

### Prerequisites

This project requires SDL2 to be installed on your system. You can install it using your system's package manager:

For Arch Linux:

```bash
sudo pacman -S sdl2
```

For Ubuntu:

```bash
sudo apt-get install libsdl2-dev
```

### Building the Project

To build the project, simply run the following command in the terminal:

```bash
gcc -o raycaster src/*.c -lSDL2 -lm
```

This will compile the project and create an executable named `raycaster`.

### Running the Project

Once the project is compiled, you can run it using:

```bash
./raycaster
```


## Functionality

### Player Movement

Player movement is handled through the **W**, **A**, **S**, and **D** keys:

- **W:** Move forward in the current direction.
    
- **S:** Move backward in the current direction.
    
- **A:** Rotate the player counterclockwise.
    
- **D:** Rotate the player clockwise.
    

> Movement is constrained by walls in the environment, and the player cannot move through them.

# Raycasting

The raycasting engine is the core of the 3D perspective. It calculates the viewable space by casting rays from the player's position and determining intersections with the map. These intersections are then rendered to simulate the 3D walls in the game world. The technique basically simulates the process of projecting rays from the player's viewpoint to determine how far the nearest walls are in each direction. This allows us to create the illusion of a 3D environment using only a 2D map.

## Key Concepts

- **Player Position**: The position of the player is represented by a `Vector` (pPos) which stores the player's x and y coordinates.
    
- **Ray Direction**: Each ray is cast from the player's position at a specific angle, represented by the player's angle `pA`. The direction is determined using the trigonometric cosine and sine functions to yield a unit vector (`pd`).
    
- **Grid-Based World**: The world is represented as a grid where each tile is either walkable or a wall. The map is divided into blocks (usually squares), and each ray checks whether it hits a wall by scanning the blocks.

## How the Algorithm Works

I've attempted to be as detailed as possible in my explanation, so the following sections will be meticulous and in-depth. I've tried to make it as approachable as possible but regardless feel free to skip this section if you're not interested in how the internals work.

1. **Initial Setup**:
    
    - The function `castRay(Vector rd)` is responsible for casting rays from the player's position. Each ray has a direction (`rd`), which is computed based on the player's angle.
        
    - The `unitlength` variables calculate how much the ray moves horizontally or vertically per unit of distance traveled.
        
2. **Casting Rays**:
    
    - For each ray, the algorithm calculates two values, `unitlength.x` and `unitlength.y`, which represent how far the ray travels in the horizontal and vertical directions for each step.
        
    - The algorithm checks the direction of the ray (positive or negative) and sets the appropriate `raylength` (horizontal and vertical distances from the player's position) based on whether the ray is moving right/left or up/down.
        
3. **Stepping Through the Map**:
    
    - The ray moves through the grid in steps, checking at each point if it hits a wall. The decision of whether to move horizontally or vertically is based on which direction (horizontal or vertical) the ray is traveling and which is closer.
        
    - The ray keeps moving, adjusting its distance and direction at each step, until it either hits a wall or reaches a maximum distance (800 units).
        
4. **Checking for Wall Hits**:
    
    - At each step, the `hitsWall(Vector pt)` function checks if the current tile the ray is passing through contains a wall. If a wall is detected, the raycasting stops, and the distance to the wall is returned.
        
    - The ray's hit status is marked by either a horizontal or vertical wall ('h' or 'v'), which is used later to color the wall differently when rendering.
        
5. **Rendering**:
    
    - Based on the distance the ray travels before hitting a wall, the color and shading of the wall can be adjusted. The closer the wall is, the darker and more pronounced the color, simulating perspective.
        

## Result

The `castRay` function returns the distance the ray travels before hitting a wall. This distance is then used to determine how to draw the wall in the 3D-like view on the screen, giving the illusion of depth and perspective based on the player's viewpoint.

# Rendering

## Map Section

The map is a 1D array of integers (`map[225]`), representing a 15x15 grid of tiles. Each tile is either a wall (represented by `1`) or empty space (represented by `0`). This grid is rendered using the `drawMap` function, which places wall tiles in **gray** and empty tiles in **dark gray**.

### Player Position and Drawing

The player’s position is stored in the `pPos` vector, and a small rectangle is drawn at this position using `drawPlayer`. The rectangle is filled with a color (blue, RGB: `100, 100, 230, 255`) to represent the player on the screen. The player’s position is offset by `mapStart`, which defines where the grid rendering begins.

## 3D Section

The `drawIntersections` function simulates the raycasting technique mentioned in the previous section. The player’s view angle (`pA`) is used to generate rays in a certain direction, with each ray gradually incrementing in angle (`rA`). For each ray, the following steps occur:
    
1. **Distance Calculation**: Each ray is cast using the `castRay(rd)` function, which checks for wall collisions along the ray’s path and calculates the distance to the first wall hit. The function then returns this distance.
    
2. **Wall Rendering**: Using the calculated distance, the `drawIntersections` function renders vertical slices of the scene. These slices represent walls in the 2D grid. Their height is proportional to the distance from the player (closer walls appear taller, farther walls appear shorter). The slice is drawn using the `SDL_RenderFillRect()` function, and different colors are used to represent the top (`blue`), wall (`orange`), and bottom (`green`) parts of the wall slice.
    
3. **Rayline Visualization**: A line is drawn from the player’s position to the point of intersection of each ray with a wall, giving a visual representation of the raycasted path.

## How it all ties in

- The `map` array provides the foundation for the environment layout, and the `drawMap` function visually displays it by rendering walls and open spaces.
    
- The raycasting logic in `drawIntersections` uses the player’s position (`pPos`) and orientation (`pA`) to calculate where rays intersect with walls. It calls `castRay` to detect collisions and calculate the distance to the nearest wall.
    
- The raycasting result is then used to render the scene from the player’s perspective and ultimately simulates a first-person view where walls appear to have depth depending on their distance from the player.



# Future Improvements

- **Collision Detection:** Currently, simple wall checks are performed, but more advanced response systems could be implemented.
    
- **More Features:** Implement additional features to make it an actual game like enemies, levels, and textures.
    
- **Optimizations:** Performance could be enhanced with optimizations such as using a more efficient method for raycasting, introducing level-of-detail (LOD) techniques for rendering, or reducing visual distortions as much as possible.


### Summary

All in all, "The Maze" features a grid-based map system, a player controlled perspective, and a raycasting algorithm that creates a simple 3D-like effect, despite being rendered in a 2D space. What makes this project special and unique for me personally is that it combines mathematical precision and maintainable code. Sure, it showcases an ability to implement a fundamental raycasting system, but the true skill here is the ability to translate theoretical concepts into practical applications; of being given just an idea and producing a working result. It’s a testament to problem-solving, adaptability, and the satisfaction of turning abstract logic into something tangible and interactive.
