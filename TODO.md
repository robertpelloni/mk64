# mk64 TODO

## High Priority
- Port the core "Item & Collision" logic to Rust to enable the "Zero-Latency" Engine.
- Cross-compile the decompiled code to WASM with Shared Memory for browser emulation.
- Create missing specific documentation files required by universal instructions: `ROADMAP.md`, `CHANGELOG.md`, `HANDOFF.md`, `DEPLOY.md`, `AGENTS.md`, `CLAUDE.md`, `GEMINI.md`, `GPT.md`, `copilot-instructions.md`, `MEMORY.md`.
- Label more functions in `src/audio`, `src/menus`, and `src/save` (ongoing: labeled surface skid effect selection `audio_determine_surface_skid_effect`, tyre skid sounds `audio_update_tyre_skid_sound`, skid volume `audio_update_skid_sound_volume`, frequency `audio_update_skid_sound_frequency`, player sound bank init `audio_init_player_sound_bank`, throttle counter `audio_update_kart_throttle_timer`, engine rev sounds `audio_update_kart_engine_rev_sound`).
- Expand documentation around memory layout and `mk64.ld`.

## Backlog
- Build the "Level-Gen" Sandbox with AI manipulation.
- Implement the "Private Grand-Prix" Mesh for P2P Multiplayer (using libp2p).
- Construct a VR/MR Kart Experience utilizing WebXR.
