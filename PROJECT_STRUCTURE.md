# Project Structure

This document outlines the directory layout of the Mario Kart 64 Decompilation project.

## Root Directory

*   **`src/`**: Source code files (.c) for the game engine, game logic, and enhancements.
    *   **`src/main.c`**: Main game loop, initialization, and 60FPS logic.
    *   **`src/camera.c`**: Camera control logic.
    *   **`src/flycam.c`**: Free-flying camera implementation.
    *   **`src/menus.c`**, **`src/menu_items.c`**: UI and menu system logic.
    *   **`src/save.c`**: Save data handling and EEPROM persistence.
    *   **`src/racing/`**: Racing-specific logic (physics, actors, collision).
    *   **`src/audio/`**: Audio subsystem.
*   **`include/`**: Header files (.h) defining structs, macros, and function prototypes.
    *   **`include/config.h`**: Global compile-time configuration flags.
    *   **`include/PR/`**: Nintendo 64 SDK headers.
*   **`asm/`**: MIPS assembly files (.s), mostly used for non-decompiled code or hand-optimized routines.
*   **`courses/`**: Course data and assets.
*   **`assets/`**: Extracted game assets (textures, models). *Note: Requires ROM extraction.*
*   **`tools/`**: External tools and scripts.
    *   **`tools/asm-differ/`**: Diff tool for matching decompilation.
    *   **`tools/decomp-permuter/`**: Code randomizer for matching.
*   **`docs/`**: Documentation files (Doxygen, images).
    *   **`docs/mainpage.md`**: Main page for generated docs.

## Key Files

*   **`Makefile`**: Build script.
*   **`mk64.ld`**: Linker script.
*   **`spec`**: Segment specification.
*   **`AGENTS.md`**: Instructions for AI contributors.
*   **`MANUAL.md`**: User manual for players.
*   **`DASHBOARD.md`**: Submodule status.
*   **`VERSION`**: Current version number.
*   **`CHANGELOG.md`**: History of changes.
