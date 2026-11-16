# Changelog

## [1.7.1] - SDL Window Context & GLEW Integration
### Added
- **SDL2 Window Integration:** Fully implemented `PC_WindowInit`, `PC_PollEvents`, and `PC_SwapBuffers` inside `src/pc_port/platform_window.c`. The PC port now spawns a native 640x480 SDL2 window with an active OpenGL 3.3 Core Profile context.
- **GLEW Linkage:** Replaced all stubbed/commented OpenGL uploads (`glBufferSubData`, `glTexImage2D`) in `platform_renderer.c` with live GL API calls. Added `-lSDL2`, `-lGLEW`, and `-lGL` to the `LDFLAGS` in `Makefile.pc` to support the rendering execution.

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

## [8.107.6] - 2026-07-01
### Added
- Created `DASHBOARD.md` to map out the status of new mechanics and features per the `UNIVERSAL_LLM_INSTRUCTIONS.md`.

### Changed
- Massively refactored and renamed `func_800C...` functions and `D_80...` global data variables in `src/audio/external.c` and `src/audio/port_eu.c` to improve code readability and maintainability.
- Renamed ghost data and save management functions in `src/save.c`, `src/menus.c`, and `src/replays.c` to reflect their true purposes.

## [8.107.4] - 2026-05-20
### Removed
- Removed the `bobcoin` submodule to decouple unused blockchain experimental UI from the core engine repo.
### Changed
- **Makefile.pc:** Added a `filter-out` routine to explicitly ignore N64 hardware-specific assembly files (e.g., `src/os/`, `src/gu/`) during native PC builds.

## [1.6.5] - PC Port Build Pipeline
### Added
- **Native PC Build:** Created `Makefile.pc` to compile the C codebase using a modern GCC/Clang toolchain. It defines the `PC_BUILD` macro, filters out N64 hardware dependencies (`TARGET_N64=0`), and sets up output directories for the `mk64_pc` executable.

## [8.107.2] - 2026-05-19
### Updated
- Synced `tools/torch` and `tools/blender/fast64` submodules to latest upstream commits.
- Renamed remaining func_800... routines in src/racing/race_logic.c and src/racing/actors.c to descriptive names.
