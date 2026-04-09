# Roadmap

## 1. Enhancements & Modernization (Completed)
- [x] **60 FPS Mode:** Decoupled game logic from rendering loop.
- [x] **Widescreen Support:** 16:9 aspect ratio with FOV adjustment and HUD pillarboxing.
- [x] **Fast Boot:** Skip intro logos.
- [x] **Disable Rubber Banding:** Toggle for AI speed modification.
- [x] **Unlock All:** Persistent unlock for tracks and characters.
- [x] **Fly Cam:** Free camera mode for debug/cinematic use.
- [x] **Resource Meters:** On-screen CPU/RDP/RSP usage bars.
- [x] **Debug Mode:** Re-enabled developer debug menus and shortcuts.
- [x] **Crash Handler:** Enhanced crash screen with register dump.
- [x] **Analog Deadzone:** Configurable stick deadzone.
- [x] **Audio Toggles:** Music and SFX toggles.

## 2. Practice Mode & Tools (Completed)
- [x] **Input Display:** Visual overlay of controller inputs.
- [x] **Speedometer:** On-screen speed bar.
- [x] **Level Reset:** L+R+Start to restart race instantly.
- [x] **Save States (Lite):** Position save/load (L+Left/Right).
- [x] **Item Control:** Force specific items or disable items.
- [x] **Lap Skip:** Skip current lap (L+Up).
- [x] **Timer Freeze:** Stop race timer.

## 3. UI & UX Polish (Completed)
- [x] **Extras Menu:** Centralized configuration menu.
- [x] **Practice Submenu:** Organized practice tools.
- [x] **On-Screen Descriptions:** Tooltip text for menu options.
- [x] **Manual:** Comprehensive documentation.

## 4. Future Goals
- [x] **Ghost Data Enhancement:** Abstracted save/ghost data to PC filesystem.
- [x] **Modding Support:** Core hooks (`OnGameTick`, `OnRaceStart`) implemented.
- [x] **Modding Support (Advanced):** Asset Replacement UI Toggle and Registry skeleton.
- [x] **PC Port Backend:** Filesystem (`stdio.h`), Window/Audio stubs, Input overrides, and `Makefile.pc` Build Pipeline created.
- [x] **PC Port Renderer:** Intercepted `gSPDisplayList` inside the N64 Task Queue (`platform_renderer.c`).
- [x] **PC Port Renderer:** Created GLSL shader skeletons and `Gfx` Opcode parsing loop (`platform_renderer.c`).
- [x] **PC Port Renderer:** Vtx arrays correctly extracted and float-scaled to intermediate `PCVertex` array.
- [x] **PC Port Renderer:** `G_SETTIMG` and `G_SETTILESIZE` logic added to extract raw texture bounds and format structs.
- [x] **PC Port Renderer:** N64 RGBA16 and IA16 decoders built and injected into Gfx parsing loop.
- [x] **PC Port Window:** SDL2 `SDL_Window` and `SDL_GLContext` (OpenGL 3.3 Core) fully implemented.
- [ ] **PC Port Audio/Input:** Implement SDL controller/keyboard polling and SDL Audio pushing.
- [ ] **Modding Support (Advanced):** Lua Scripting API.
- [ ] **Online Play:** ENet integration.
