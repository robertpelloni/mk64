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
- [x] **PC Port Backend:** Filesystem (`stdio.h`), Window/Audio stubs, and Input polling overrides abstracted.
- [ ] **PC Port Renderer:** SDL/OpenGL hardware translation pipeline.
- [ ] **Modding Support (Advanced):** Lua Scripting API.
- [ ] **Online Play:** ENet integration.
