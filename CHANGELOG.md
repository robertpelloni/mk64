# Changelog

## [1.7.0] - PC Renderer N64 Texture Decoding
### Added
- **Texture Format Decoding:** Implemented standard C decoding algorithms (`decode_rgba16_to_rgba32` and `decode_ia16_to_rgba32`) in `src/pc_port/platform_renderer.c`. The `G_SETTILESIZE` logic block now correctly unpacks big-endian N64 16-bit texture payloads into 32-bit `GL_RGBA` arrays, resolving one of the largest hardware translation hurdles.
- **OpenGL Memory Stubs:** Added correctly formatted (currently commented) OpenGL API calls (`glBufferSubData` and `glTexImage2D`) at the translation interception points to immediately push decoded vertices and textures to the GPU once the SDL2 context is finalized.

## [1.6.9] - PC Renderer Texture State Parsing
### Added
- **Texture Decoding Logic:** Fleshed out the `G_SETTIMG`, `G_SETTILESIZE`, and `G_LOADBLOCK` macro parsers in `src/pc_port/platform_renderer.c`. It now correctly extracts N64 texture formats (CI/RGBA), sizes, physical addresses, and calculates the true rendering width and height required for OpenGL `glTexImage2D` uploads.
- **Texture State Tracking:** Added `PCTextureState sCurrentTexture` struct to maintain the active texture context during display list rendering.

## [1.6.7] - PC Renderer Shaders & Gfx Parsing
### Added
- **PC Renderer Abstraction:** Added GLSL Shader source skeletons (OpenGL 3.3 Core) to `platform_renderer.c`.
- **Gfx Parsing:** Implemented the core `while` loop within `PC_RenderDisplayList` that iterates over the Fast3DEX macro stream, extracting opcodes from the high byte of `w0` and dispatching them via a `switch` statement (handling `G_VTX`, `G_TRI1`, `G_SETTIMG`, `G_SETCOMBINE`, etc.). This logic is guarded by `#ifdef PC_BUILD`.

## [1.6.6] - PC Rendering Intercept & Pipeline refinement
### Added
- **PC Renderer Abstraction:** Added `src/pc_port/platform_renderer.c`. Intercepted the N64 Fast3D display list (`Gfx*`) directly within `exec_display_list` in `src/main.c`. This provides the critical hook for translating `gSP*` macros to OpenGL calls in the future.

### Changed
- **Makefile.pc:** Added a `filter-out` routine to explicitly ignore N64 hardware-specific assembly files (e.g., `src/os/`, `src/gu/`) during native PC builds.

## [1.6.5] - PC Port Build Pipeline
### Added
- **Native PC Build:** Created `Makefile.pc` to compile the C codebase using a modern GCC/Clang toolchain. It defines the `PC_BUILD` macro, filters out N64 hardware dependencies (`TARGET_N64=0`), and sets up output directories for the `mk64_pc` executable.

## [1.6.4] - PC Input & Filesystem Finalization
### Added
- **PC Input Abstraction:** Created `src/pc_port/platform_input.c` and `.h`. Hooked `PC_ReadInput` into the primary controller polling function (`read_controllers` in `main.c`) to allow native SDL controller mapping to override N64 struct states.
- **PC Filesystem Abstraction:** Fully implemented `PC_SaveFile` and `PC_LoadFile` in `platform_save.c` using standard C `<stdio.h>` calls (`fopen`, `fread`, `fwrite`) wrapped in `#ifdef PC_BUILD` guards.

## [1.6.3] - Modding UI & Audio Abstraction
### Added
- **Custom Assets Toggle:** Added a "CUSTOM ASSETS" option to the Extras menu. This persists to EEPROM and controls whether the game attempts to load external textures/models via the Modding Asset Registry.
- **PC Audio Abstraction:** Created `src/pc_port/platform_audio.c` as a skeleton for future SDL audio backend integration.

### Changed
- **TODO Cleanup:** Re-prioritized roadmap and todo lists to focus on advanced modding and PC backend ports.

## [1.6.0] - PC Porting & Modding Support
### Added
- **PC Save System:** Abstracted save logic to use file I/O instead of N64 Controller Pak calls. Added support for saving "Practice Ghosts" to disk.
- **Modding Hooks:** Implemented `Mod_OnRaceStart`, `Mod_OnLapComplete`, and `Mod_OnGameTick` hooks for external scripting support.
- **Asset Registry:** Added `mod_assets.c` to facilitate data-driven asset replacement (textures/models).

### Changed
- **UI Updates:** Renamed "Controller Pak" menu options to "Save File" / "Disk" to reflect the PC environment.
- **Refactoring:** Created `src/pc_port/` and `src/modding/` directories to separate platform-specific logic.

## [1.5.2] - Save System Safety & Optimization
### Changed
- **Performance:** Optimized menu save logic. Settings like "Stick Deadzone" and "Item Control" now only trigger a save when exiting the menu, preventing EEPROM wear and menu lag.
- **Verification:** Confirmed that the extended settings storage in `checksum[0]` is safe and does not conflict with the game's integrity checks or checksum calculations.

## [1.5.0] - Robust Save States & Feedback
### Added
- **Robust Save States:** Save States (L + D-Pad Left/Right) now preserve:
    - **Held Item:** The item currently in the player's inventory.
    - **Lap Count:** The current lap number.
    - **RNG State:** The Random Number Generator seed, ensuring consistent outcomes for deterministic events.
- **On-Screen Feedback:** Added "STATE SAVED" and "STATE LOADED" text overlays to provide immediate visual confirmation of save state actions.

### Changed
- Updated `MANUAL.md` with detailed Save State information.
- Refined Save State logic in `src/main.c` to integrate deeply with player and game state variables.

## [1.4.0] - Practice Tools: Lap Skip & Timer Freeze
### Added
- **Lap Skip:** Added "Lap Skip" feature (L + D-Pad Up) to instantly complete the current lap. Useful for practicing specific laps or finishing races quickly.
- **Timer Freeze:** Added "Timer Freeze" feature to stop the race timer. Useful for infinite practice sessions.
- **Practice Menu:** Updated Practice Menu UI to include Lap Skip and Timer Freeze options with tooltips.
- **Persistence:** Both features are saved to extended save data.

### Changed
- Updated `MANUAL.md` with new features.
- Updated `ROADMAP.md` and `TODO.md` to reflect progress.
- Extended save data logic to support `unknownBytes[1]` for Timer Freeze persistence.

## [1.3.0] - Item Control & Practice Enhancements
### Added
- **Item Control:** New "Practice Options" menu item allowing players to force specific items (Banana, Shells, Stars, etc.) or disable items completely.
- **UI Descriptions:** Added on-screen help text/tooltips for all Extras and Practice menu options to explain functionality.
- **Practice Menu Polish:** Reorganized Practice Menu with "Item Control" and improved navigation.
- **Persistence:** Item Control settings are saved to EEPROM (extended save data).

### Changed
- Updated `MANUAL.md` with new features.
- Updated `ROADMAP.md` and `TODO.md` to reflect progress.

## [1.2.0] - Audio & Deadzone
### Added
- Analog Stick Deadzone configuration.
- Music and SFX toggles.
- Robust save data persistence for new settings using `checksum[0]` packing.

## [1.1.0] - Practice Tools
### Added
- Input Display.
- Speedometer.
- Level Reset (L+R+Start).
- Fly Cam.
- Widescreen, 60FPS, Fast Boot.
