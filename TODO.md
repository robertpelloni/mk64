# mk64 TODO

## High Priority
- Port the core "Item & Collision" logic to Rust to enable the "Zero-Latency" Engine.
- Cross-compile the decompiled code to WASM with Shared Memory for browser emulation.
- Create missing specific documentation files required by universal instructions: `ROADMAP.md`, `CHANGELOG.md`, `HANDOFF.md`, `DEPLOY.md`, `AGENTS.md`, `CLAUDE.md`, `GEMINI.md`, `GPT.md`, `copilot-instructions.md`, `MEMORY.md`.
- Label more functions in `src/audio`, `src/menus`, and `src/save` (ongoing: labeled audio track initialization `audio_init_course_sequence` and finish status `audio_set_player_finish_state` / `audio_set_race_finish_flag`, ghost file allocator `allocate_pak1_ghost_file` and header reset `clear_and_write_pak1_ghost_header`, Pak 1/2 ghost header loaders `load_and_validate_pak1_ghost_headers` / `load_and_validate_pak2_ghost_headers` and header checksums `calculate_pak1_ghost_header_checksum` / `calculate_pak2_ghost_header_checksum`, Controller Pak 2 probe `probe_controller_pak_2`, ghost header writer `save_ghost_header_to_pak`, ghost page checksum `calculate_ghost_page_checksum`, Controller Pak 1 probe `probe_controller_pak_1`, Grand Prix rival selector `select_grand_prix_rival_characters`, screen transition faders `start_screen_fade_*`, menu screen fade transitions `set_menu_fade_*`, sequence player settings resets `audio_reset_all_sequence_player_settings`, bank mask handler, sequence dispatch, race finish sequences, and lifecycle handlers).
- Expand documentation around memory layout and `mk64.ld`.

## Backlog
- Build the "Level-Gen" Sandbox with AI manipulation.
- Implement the "Private Grand-Prix" Mesh for P2P Multiplayer (using libp2p).
- Construct a VR/MR Kart Experience utilizing WebXR.
