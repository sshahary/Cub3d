# Cub3D

## Overview

**Cub3D** is a project developed as part of the curriculum at 42, designed to introduce students to the basics of raycasting, a technique used in early 3D game engines. Inspired by classic games like Wolfenstein 3D, Cub3D challenges you to create a simple 3D game engine using a 2D map and a first-person perspective. The project emphasizes understanding the mathematics behind 3D rendering, handling player input, and managing graphics rendering in real-time.

## Features

- **Raycasting Engine:** Implement a basic 3D rendering engine using raycasting.
- **Player Movement:** Handle player movement and rotation in a 3D space.
- **Simple Map System:** Load and interpret a 2D map to represent the game world.
- **Textures and Colors:** Apply wall textures and floor/ceiling colors to enhance visual representation.
- **Basic Game Mechanics:** Implement collision detection and basic interaction with the environment.

## Prerequisites

To build and run this project, you need the following:

- GCC or another C compiler
- Make
- MLX42 (a simple graphics library provided by 42)

## Installation

To set up the project locally, follow these steps:

1. **Clone the repository:**
    ```bash
    git clone https://github.com/sshahary/Cub3d.git
    cd cub3d
    ```

2. **Compile the project:**
    ```bash
    make
    ```

3. **Run the game:**
    ```bash
    ./cub3D <map_file>
    ```

   Replace `<map_file>` with the path to a valid map file.

## Map Files

Map files define the layout of the game world in 2D. The map consists of different characters that represent walls, empty spaces, and the player's starting position.

### Example Maps

Instead of directly providing text-based map examples, you can visualize how the map layout works with these images:

#### Basic Map Layout:
![Basic Map Layout](path-to-your-basic-map-image.png)

#### Advanced Map Layout:
![Advanced Map Layout](path-to-your-advanced-map-image.png)

Each character in the map corresponds to different elements in the game:
- `1`: Wall
- `0`: Empty space
- `N`, `S`, `E`, `W`: Player’s starting position, facing North, South, East, or West respectively.


## Controls

- **W/A/S/D:** Move the player forward, left, backward, and right, respectively.
- **Left/Right Arrow Keys:** Rotate the player's view.
- **ESC:** Exit the game.

## Customization

You can customize various aspects of the game by editing the map files or modifying the textures and colors used for walls, floor, and ceiling. Textures should be in `.xpm` format and stored in the appropriate directory.

## Testing

You can test the game with different map files to evaluate the rendering performance, collision detection, and overall functionality. Ensure that your maps are well-formed to avoid unexpected behavior.

## Troubleshooting

- **Black Screen or No Rendering:** Ensure that the map file is correctly formatted and that all required assets are in place.
- **Crashes or Segmentation Faults:** Debug using tools like `gdb` or by adding print statements to trace the issue. Common issues might include invalid memory access or incorrect map data.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

- Thanks to 42 for the opportunity to learn and explore the fundamentals of 3D graphics and game development.
- Special thanks to the creators of MLX42, which provided the foundational graphics library for this project.
