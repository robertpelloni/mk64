# mk64 TODO

## High Priority
- Port the core "Item & Collision" logic to Rust to enable the "Zero-Latency" Engine.
- Cross-compile the decompiled code to WASM with Shared Memory for browser emulation.
- Create missing specific documentation files required by universal instructions: `ROADMAP.md`, `CHANGELOG.md`, `HANDOFF.md`, `DEPLOY.md`, `AGENTS.md`, `CLAUDE.md`, `GEMINI.md`, `GPT.md`, `copilot-instructions.md`, `MEMORY.md`.
- Label more functions in `src/audio` (ongoing: labeled sequence dispatch `audio_push_sequence_command`, `audio_process_sequence_commands`, `audio_fade_out_all_sequences`, race finish sequences, and lifecycle handlers).
- Expand documentation around memory layout and `mk64.ld`.

## Backlog
- Build the "Level-Gen" Sandbox with AI manipulation.
- Implement the "Private Grand-Prix" Mesh for P2P Multiplayer (using libp2p).
- Construct a VR/MR Kart Experience utilizing WebXR.
