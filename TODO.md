# TODO List

## High Priority
- Port the core "Item & Collision" logic to Rust to enable the "Zero-Latency" Engine.
- Cross-compile the decompiled code to WASM with Shared Memory for browser emulation.
- Create missing specific documentation files required by universal instructions: `ROADMAP.md`, `CHANGELOG.md`, `HANDOFF.md`, `DEPLOY.md`, `AGENTS.md`, `CLAUDE.md`, `GEMINI.md`, `GPT.md`, `copilot-instructions.md`, `MEMORY.md`.
- Label more functions in `src/audio`, `src/menus`, and `src/save` (ongoing: completed 100% of unnamed routines in the entire `src/audio` subsystem, completed all unnamed routines in `src/save.h`, completed all unnamed routines in `src/camera.h`, completed all unnamed routines in `src/render_player.h`, completed all unnamed routines in `src/math_util_2.h`, labeled 27 core CPU vehicle, camera path, and track vehicle navigation routines in `src/cpu_vehicles_camera_path.h`, completed ghost replay and MIO0 encoding pipeline, labeled alternative MIO0 decompressor `mio0decode_alt`, and labeled menu textured rectangle and screen transition routines).
- Expand documentation around memory layout and `mk64.ld`.

## Short Term
- [ ] **PC Port:** Full SDL/OpenGL Backend (Renderer translation).
- [ ] **Online Play:** Abstract N64 controller inputs over ENet sockets.

## Long Term / Tech Debt
- [ ] **Lua API:** Expose `Player` structs to Lua scripts loaded at runtime (PC Port only).
- [ ] **Build System:** Improve `Makefile` dependency tracking for header changes.
