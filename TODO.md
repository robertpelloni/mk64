# mk64 TODO

## High Priority
- Port the core "Item & Collision" logic to Rust to enable the "Zero-Latency" Engine.
- Cross-compile the decompiled code to WASM with Shared Memory for browser emulation.
- Create missing specific documentation files required by universal instructions: `ROADMAP.md`, `CHANGELOG.md`, `HANDOFF.md`, `DEPLOY.md`, `AGENTS.md`, `CLAUDE.md`, `GEMINI.md`, `GPT.md`, `copilot-instructions.md`, `MEMORY.md`.
- Label more functions in `src/audio`, `src/menus`, and `src/save` (ongoing: completed 100% of unnamed routines in the entire `src/audio` subsystem, completed all unnamed routines in `src/save.h`, labeled ghost replay and MIO0 encoding pipeline, completed camera positioning and dynamic zoom routines `camera_trigger_screen_shake`, `player_trigger_screen_shake`, `camera_calculate_grid_start_position`, `camera_calculate_driving_follow_position`, `camera_calculate_lakitu_retrieval_position`, `camera_calculate_reverse_look_position`, `camera_calculate_close_follow_position`, `camera_update_grid_start`, `camera_update_normal_follow`, `camera_update_lakitu_follow`, `camera_update_close_follow`, `camera_update_state_machine`, `camera_update_dynamic_fov_zoom`, `camera_check_grid_start_complete`, labeled alternative MIO0 decompressor `mio0decode_alt`, labeled menu textured rectangle and screen transition routines, and labeled 2D coordinate rotation routines).
- Expand documentation around memory layout and `mk64.ld`.

## Backlog
- Build the "Level-Gen" Sandbox with AI manipulation.
- Implement the "Private Grand-Prix" Mesh for P2P Multiplayer (using libp2p).
- Construct a VR/MR Kart Experience utilizing WebXR.
