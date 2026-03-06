# Project Dashboard

## Project Structure
*   **root:** Main build files and documentation.
*   **src/**: Source code (C and Assembly).
    *   `src/racing/`: Core racing logic (actors, physics).
    *   `src/audio/`: Sound and music.
    *   `src/menu_items.c`, `src/menus.c`: UI logic.
*   **include/**: Header files.
*   **asm/**: Disassembled ASM files (non-decompiled).
*   **assets/**: Extracted game assets (textures, models).
*   **tools/**: Build tools and submodules.

## Submodules Status

| Submodule | Path | Description | Status |
| :--- | :--- | :--- | :--- |
| **asm-differ** | `tools/asm-differ/` | Tool for comparing C output with original ASM. | Active |
| **fast64** | `tools/blender/fast64/` | Blender plugin for N64 asset creation. | Active |
| **decomp-permuter** | `tools/decomp-permuter/` | C code permuter for matching ASM. | Active |
| **torch** | `tools/torch/` | Build system / Toolchain helper. | Active |
| **doxygen-awesome-css** | `doxygen-awesome-css/` | CSS theme for Doxygen documentation. | Active |

## Build Info
*   **Version:** 1.2.0
*   **Target:** N64 (US v1.0)
*   **Compiler:** IDO 5.3 / 7.1 (via recomp)

## Recent Changes
*   **1.2.0:** Implemented Analog Deadzone, Music/SFX toggles, Save Persistence Fix.
*   **1.1.0:** Added Practice Mode (Input Display, Speedometer, Level Reset).
