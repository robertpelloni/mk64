# Project Memory & Handoff Document

This document records the current state of the project, significant architectural decisions, and ongoing observations for AI models working on the repository.

## Current Project Version: 1.6.2

## Architectural State & Observations
*   **Codebase:** Built on `n64decomp/mk64`. Compiling requires an original `baserom.us.z64`.
*   **Build System:** `make -j4`. New C files must be explicitly added to `mk64.ld` in the `.main` segment.
*   **Feature Toggles:** `gEnable...` and `gToggle...` variables are declared in `src/main.h` and persisted via the `SaveExtended_` API in `src/save_extended.c`.
*   **Settings Persistence:** Extended settings are safely packed into `checksum[0]` and `onlyBestTimeTrialRecords[0].unknownBytes` within the game's EEPROM structure, bypassing standard integrity checks.
*   **Menus:** Modifying menus involves updating `src/menus.c` (backend logic, button presses) and `src/menu_items.c` (frontend string arrays, enums, switch statements, rendering).
*   **PC Porting:** The project is actively abstracting N64 dependencies. `include/pc_port/platform_save.h` and `src/pc_port/platform_save.c` handle mock file I/O for ghost data.
*   **Modding:** Basic hooks (`Mod_OnGameTick`, `Mod_OnRaceStart`, `Mod_OnLapComplete`) are injected into `src/main.c` and `src/code_80057C60.c`. `src/modding/mod_assets.c` exists for future asset replacement.
*   **Redundancy Check:** Ghost replay logic (`process_course_ghost_replay` / `process_player_ghost_replay`) has been refactored into `process_ghost_replay_generic` (`src/replays.c`).
*   **Fast Reset:** L+R+Start performs a "Fast Reset" by setting `gGamestateNext = RACING` without clearing `gCurrentlyLoadedCourseId`, skipping track reloads (`src/main.c`).
*   **Timer Freeze / Lap Skip:** Implemented in `src/main.c`. Lap skip is restricted to 1P mode to prevent issues. Timer Freeze prevents `gCourseTimer` accumulation.
*   **Robust Save States:** L+Left (Save) / L+Right (Load) captures Position, Rotation, Velocity, Held Item (`currentItemCopy`), Lap Count, and RNG Seed (`gRandomSeed16`).
*   **Item Control:** Forces specific items via `gPracticeItemOption` overriding logic in `src/update_objects.c` (`func_8007AFB0`).
*   **Visual Enhancements:** 60 FPS uses an `osGetTime` delta. 16:9 Widescreen adjusts the FOV and pillarboxes the HUD (`guOrtho` in `src/math_util_2.c`).

## Critical Rules for Next Steps
1.  **Always refer to `LLM_INSTRUCTIONS.md` for core directives.**
2.  Do not edit `baserom` files.
3.  Any new UI feature *must* be added to `gTextPracticeMenu`/`gTextExtrasMenu` in `src/menu_items.c` and its corresponding enum in `src/menu_items.h`.
4.  Do not assume compilation works without the ROM. Rely on strong static analysis.
5.  When adding new settings, use `SaveExtended` and ensure they default to OFF.
6.  Update `VERSION`, `CHANGELOG.md`, `ROADMAP.md`, and `TODO.md` after every successful feature implementation.