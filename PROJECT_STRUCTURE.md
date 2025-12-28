# Project Structure

This document outlines the high-level architecture and directory layout of the **MK64 Greatest Racing Game Mod**.

## Root Directory
- **`src/`**: Contains the core source code for the game.
  - `main.c`: Main game loop and VSync logic (modified for 60FPS).
  - `racing/`: Racing logic, skybox, and splitscreen rendering.
  - `menus.c`: Menu state machine and initialization.
  - `save.c`: Save data management and unlock logic.
  - `cpu_vehicles_camera_path.c`: AI pathfinding and speed control.
- **`include/`**: Header files defining structs, macros, and global variables.
- **`tools/`**: Scripts and binaries used for the build process.
- **`courses/`**: Course data and assets.

## Submodules
The project relies on external tools managed as git submodules:

1.  **`tools/asm-differ`**: A tool to diff assembly output against the target ROM.
2.  **`tools/blender/fast64`**: Fast64 is a Blender plugin for N64 display list generation.
3.  **`tools/decomp-permuter`**: Randomizes C code to help match assembly instructions.
4.  **`tools/torch`**: An asset extraction tool for N64 ROMs.
5.  **`doxygen-awesome-css`**: A modern CSS theme for Doxygen documentation.

## Key Modified Files
- `src/main.c`: **60FPS Patch**. Adjusted VBlank wait and `gTickSpeed`.
- `src/racing/skybox_and_splitscreen.c`: **Widescreen**. Updated aspect ratios.
- `src/math_util_2.c`: **HUD Fix**. Corrected orthographic projection for 16:9.
- `src/code_80086E70.c`: **Culling Fix**. Widened frustum checks.
- `src/save.c`: **Unlocks**. Force enabled all cups and modes.

## Build System
The project uses `make` for compilation. The toolchain requires MIPS GCC (via IDO or similar) and relies on the extracted assets from a US v1.0 ROM.
