# Session Handoff - 2026-07-01 (v8.107.5)

## Executive Summary
Focused heavily on the Phase 1 goal of perfect decompilation by aggressively renaming internal audio, save, and menu routines to descriptive names based on structural context. Created and expanded `DASHBOARD.md` to map out the status of new mechanics and features per the `UNIVERSAL_LLM_INSTRUCTIONS.md`.

### Recent Fixes & Additions
- **Audio Subsystem Overhaul:** Extensively renamed functions and data arrays in `src/audio/external.c` and `src/audio/port_eu.c`. Mapped EU-specific port macros and queue processing functions. Labeled major structures like `gAudioCmdBuffer`, `gSequenceQueue`, and `gAudioCharacterStates`.
- **Save & Replays:** Renamed functions dealing with ghost data and controller pak I/O in `src/save.c` and `src/menus.c` (e.g., `save_ghost_data_to_controller_pak`, `save_update_course_time_trial_records`). Also renamed the ghost indexing routines in `src/replays.c` (`encode_ghost_data`, `decode_ghost_data`).

## Roadblocks
- A known compilation constraint exists where `make` fails without `baserom.us.z64`. To verify code changes, we have to rely on `cc -fsyntax-only -I include -I src -D _LANGUAGE_C src/*.c` for static analysis.

## Next Steps for Implementor
1. **Continue C Renaming:** Finish the `func_800B...` renaming in `src/audio/load.c`, `src/audio/synthesis.c`, and `src/audio/playback.c`. There are still many unnamed functions handling low-level sample DMA and envelope mixing.
2. **Subsystem Pivot (Physics/Rust):** As `src/racing/collision.c` is nearly completely labeled, begin identifying the core physics loops in `src/racing/race_logic.c` or `src/racing/math_util.c` for extraction into the Rust bridge.
- Renamed remaining func_800... routines in race_logic.c and actors.c.
- Need to implement tkmk00 compressor/decompressor for menu textures (e.g. tkmk00decode) and map out the remaining menu and audio functions.
