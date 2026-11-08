# mk64 TODO

## High Priority
- Port the core "Item & Collision" logic to Rust to enable the "Zero-Latency" Engine.
- Cross-compile the decompiled code to WASM with Shared Memory for browser emulation.
- Create missing specific documentation files required by universal instructions: `ROADMAP.md`, `CHANGELOG.md`, `HANDOFF.md`, `DEPLOY.md`, `AGENTS.md`, `CLAUDE.md`, `GEMINI.md`, `GPT.md`, `copilot-instructions.md`, `MEMORY.md`.
- Label more functions in `src/audio`, `src/menus`, and `src/save` (ongoing: labeled time trial unpack/retrieval `unpack_time_trial_record`, `get_current_course_time_trial_record`, `get_course_time_trial_record`, `get_current_course_best_lap_record`, `get_course_best_lap_record`, record update `update_course_three_lap_records`, `update_course_best_single_lap_record`, and Grand Prix points update `update_current_cup_grand_prix_points`, `update_cup_grand_prix_points`, `get_cup_grand_prix_points`).
- Expand documentation around memory layout and `mk64.ld`.

## Backlog
- Build the "Level-Gen" Sandbox with AI manipulation.
- Implement the "Private Grand-Prix" Mesh for P2P Multiplayer (using libp2p).
- Construct a VR/MR Kart Experience utilizing WebXR.
