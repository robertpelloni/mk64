# Project Dashboard

## Project Structure
*   **root:** Main build files and documentation (`LLM_INSTRUCTIONS.md`, `VISION.md`, `ROADMAP.md`).
*   **src/**: Source code (C and Assembly).
    *   `src/racing/`: Core racing logic (actors, physics).
    *   `src/audio/`: Sound and music.
    *   `src/menu_items.c`, `src/menus.c`: UI logic and rendering.
    *   `src/pc_port/`: Platform abstraction layer for File I/O and future PC dependencies.
    *   `src/modding/`: Event hooks and asset replacement registries.
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

*(Note: The `bobcoin` submodule was explicitly removed in v1.6.0)*

## Build Info
*   **Current Version:** 1.6.2
*   **Target:** N64 (US v1.0) / Future: SDL PC
*   **Compiler:** IDO 5.3 / 7.1 (via recomp)

## Recent Architectural Changes
*   **1.6.2:** Universal AI Documentation Overhaul.
*   **1.6.1:** Refactored Replay Logic & Implemented Fast Reset.
*   **1.6.0:** PC Save Abstraction & Modding Hooks.
*   **1.5.0:** Robust Save States.
*   **1.4.0:** Practice Tools: Lap Skip & Timer Freeze.