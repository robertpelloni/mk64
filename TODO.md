# mk64 TODO

## High Priority
- Port the core "Item & Collision" logic to Rust to enable the "Zero-Latency" Engine.
- Cross-compile the decompiled code to WASM with Shared Memory for browser emulation.
- Create missing specific documentation files required by universal instructions: `ROADMAP.md`, `CHANGELOG.md`, `HANDOFF.md`, `DEPLOY.md`, `AGENTS.md`, `CLAUDE.md`, `GEMINI.md`, `GPT.md`, `copilot-instructions.md`, `MEMORY.md`.
- Label more functions in `src/audio`, `src/menus`, and `src/save` (ongoing: labeled best time trial record write `write_eeprom_best_time_trial_records`, checksum calculators `compute_best_time_trial_records_checksum_1`, `compute_best_time_trial_records_checksum_2`, validation `validate_best_time_trial_records_checksum`, 3D positional emission `audio_play_sound_at_position_3d`).
- Expand documentation around memory layout and `mk64.ld`.

## Backlog
- Build the "Level-Gen" Sandbox with AI manipulation.
- Implement the "Private Grand-Prix" Mesh for P2P Multiplayer (using libp2p).
- Construct a VR/MR Kart Experience utilizing WebXR.
