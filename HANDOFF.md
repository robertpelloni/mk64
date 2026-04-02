# Project Memory & Handoff Document

This document records the current state of the project, significant architectural decisions, and ongoing observations for AI models working on the repository.

## Current Project Version: 1.6.8

## Architectural State & Observations
*   **Codebase:** Built on `n64decomp/mk64`. Compiling requires an original `baserom.us.z64`. The codebase contains over 1,500 instances of the `UNUSED` macro (primarily padding and legacy decomp arrays) and one remaining `TODO` flag for audio function labeling in `src/menus.c`.
*   **Build System:** `Makefile` handles N64 hardware targets (`make -j4`). `Makefile.pc` handles native PC targets (SDL/OpenGL), defining `PC_BUILD` and filtering out raw MIPS assembly directories (`src/os/`, `src/gu/`). New C files must be explicitly added to `mk64.ld` in the `.main` segment.
*   **Feature Toggles:** `gEnable...` and `gToggle...` variables are declared in `src/main.h` and persisted via the `SaveExtended_` API in `src/save_extended.c`.
*   **Settings Persistence:** Extended settings are safely packed into `checksum[0]` and `onlyBestTimeTrialRecords[0].unknownBytes` within the game's EEPROM structure, bypassing standard integrity checks.
*   **Menus:** Modifying menus involves updating `src/menus.c` (backend logic, button presses) and `src/menu_items.c` (frontend string arrays, enums, switch statements, rendering).
*   **PC Porting (Active Focus):** The project is actively abstracting N64 dependencies. `src/pc_port/` houses stubs for filesystem (`platform_save.c`, now using `stdio.h`), audio (`platform_audio.c`), input (`platform_input.c`, overriding `osContGetReadData`), and rendering (`platform_renderer.c`).
*   **SDL Renderer Abstraction:** `PC_RenderDisplayList` is injected into `exec_display_list` (`src/main.c`) to intercept the Fast3DEX macro stream (`gSPDisplayList`) right before RSP dispatch. The stub currently parses `Gfx` opcodes (e.g., `G_VTX`, `G_TRI1`) and contains OpenGL 3.3 Core GLSL shader skeletons. It now actively translates `Vtx` structures to `PCVertex` representations.
*   **Modding:** Basic hooks (`Mod_OnGameTick`, `Mod_OnRaceStart`, `Mod_OnLapComplete`) are injected into `src/main.c` and `src/code_80057C60.c`. `src/modding/mod_assets.c` acts as a data-driven Asset Registry, toggled via the UI (`gEnableCustomAssets`).
*   **Redundancy Check:** Ghost replay logic (`process_course_ghost_replay` / `process_player_ghost_replay`) has been refactored into `process_ghost_replay_generic` (`src/replays.c`).
*   **Practice Tools:** Fast Reset (L+R+Start, bypasses `load_course` in `src/main.c`), Timer Freeze, Lap Skip (1P only), Item Forcing (`gPracticeItemOption` overrides `src/update_objects.c`), Speedometer, Input Display, Flycam, and Robust Save States (L+Left/Right, capturing Position, Rotation, Velocity, Held Item, Lap Count, RNG Seed `gRandomSeed16`).
*   **Visual Enhancements:** 60 FPS uses an `osGetTime` delta (`src/main.c`). 16:9 Widescreen adjusts the FOV and pillarboxes the HUD (`guOrtho` in `src/math_util_2.c`).

## Critical Rules for Next Steps
1.  **Always refer to `LLM_INSTRUCTIONS.md` for core directives.**
2.  Any new UI feature *must* be added to both `gTextPracticeMenu`/`gTextExtrasMenu` in `src/menu_items.c` AND its corresponding enum in `src/menu_items.h`. The enum count must map 1:1 with the string array size.
3.  When updating the `Makefile.pc` to support the SDL renderer translation, do not modify the core `Makefile`. Keep the N64 compilation target strictly separated from the PC target.
4.  Do not assume compilation works without the ROM. Rely on strong static analysis.
5.  Update `VERSION`, `CHANGELOG.md`, `ROADMAP.md`, and `TODO.md` after every successful feature implementation.
