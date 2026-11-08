# mk64 TODO

## High Priority
- Port the core "Item & Collision" logic to Rust to enable the "Zero-Latency" Engine.
- Cross-compile the decompiled code to WASM with Shared Memory for browser emulation.
- Create missing specific documentation files required by universal instructions: `ROADMAP.md`, `CHANGELOG.md`, `HANDOFF.md`, `DEPLOY.md`, `AGENTS.md`, `CLAUDE.md`, `GEMINI.md`, `GPT.md`, `copilot-instructions.md`, `MEMORY.md`.
- Label more functions in `src/audio`, `src/menus`, and `src/save` (ongoing: labeled sequence player tick updater `audio_update_sequence_players`, volume targets `seq_player_set_volume_target`, setup cancellation `seq_player_cancel_setup_operations`, sequence playback controls `seq_player_play_sequence`, `seq_player_stop_sequence`, command dispatcher `audio_execute_sequence_command`, sequence query `seq_player_get_active_sequence_id`, `audio_is_sequence_command_pending`).
- Expand documentation around memory layout and `mk64.ld`.

## Backlog
- Build the "Level-Gen" Sandbox with AI manipulation.
- Implement the "Private Grand-Prix" Mesh for P2P Multiplayer (using libp2p).
- Construct a VR/MR Kart Experience utilizing WebXR.
