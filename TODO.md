# mk64 TODO

## High Priority
- Port the core "Item & Collision" logic to Rust to enable the "Zero-Latency" Engine.
- Cross-compile the decompiled code to WASM with Shared Memory for browser emulation.
- Create missing specific documentation files required by universal instructions: `ROADMAP.md`, `CHANGELOG.md`, `HANDOFF.md`, `DEPLOY.md`, `AGENTS.md`, `CLAUDE.md`, `GEMINI.md`, `GPT.md`, `copilot-instructions.md`, `MEMORY.md`.
- Label more functions in `src/audio`, `src/menus`, and `src/save` (ongoing: completed all unnamed routines in `src/save.h` and `src/audio/external.h`, labeled alternative MIO0 decompressor `mio0decode_alt`, labeled menu textured rectangle routines, labeled screen transition / viewport fading routines, and labeled 2D coordinate rotation & camera target override routines `rotate_xz_x`, `rotate_xz_z`, `atan2s_neg`, `atan2s_yx_1`, `atan2s_yx_2`, `camera_set_target_override`).
- Expand documentation around memory layout and `mk64.ld`.

## Backlog
- Build the "Level-Gen" Sandbox with AI manipulation.
- Implement the "Private Grand-Prix" Mesh for P2P Multiplayer (using libp2p).
- Construct a VR/MR Kart Experience utilizing WebXR.
