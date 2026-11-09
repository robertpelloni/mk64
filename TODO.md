# mk64 TODO

## High Priority
- Port the core "Item & Collision" logic to Rust to enable the "Zero-Latency" Engine.
- Cross-compile the decompiled code to WASM with Shared Memory for browser emulation.
- Create missing specific documentation files required by universal instructions: `ROADMAP.md`, `CHANGELOG.md`, `HANDOFF.md`, `DEPLOY.md`, `AGENTS.md`, `CLAUDE.md`, `GEMINI.md`, `GPT.md`, `copilot-instructions.md`, `MEMORY.md`.
- Label more functions in `src/audio`, `src/menus`, and `src/save` (ongoing: completed all unnamed routines in `src/save.h` and `src/audio/external.h`, labeled alternative MIO0 decompressor `mio0decode_alt`, labeled menu textured rectangle routines, labeled screen transition / viewport fading routines, labeled 2D coordinate rotation routines, and labeled audio heap & load routines `init_sample_dma_buffers`, `audio_dma_load_sample_immediate`, `audio_load_instrument_samples_immediate`, `patch_seq_file`, `patch_audio_bank_by_id`, `sound_alloc_pool_clear`, `session_pools_init`, `audio_calculate_filter_coefficients`, `audio_load_asset_to_pool`).
- Expand documentation around memory layout and `mk64.ld`.

## Backlog
- Build the "Level-Gen" Sandbox with AI manipulation.
- Implement the "Private Grand-Prix" Mesh for P2P Multiplayer (using libp2p).
- Construct a VR/MR Kart Experience utilizing WebXR.
