# Project Memory & Observations

## Codebase Patterns
- Functions prefixed with `func_800` are typically unnamed routines translated directly from MIPS assembly. Finding matching calls and renaming them is a core ongoing task.
- Fixed-point matrix conversions (e.g. within `src/racing/math_util.c`) are heavily susceptible to precision-loss crashes (PU crashes) when converting N64 float semantics to integers.
- The global build config relies heavily on `tools/` (specifically `torch` and `decomp-permuter`) to format the assets JSON and align the linker (`mk64.ld`).

## Recent Audits
- The `bobcoin` submodule was completely removed to reflect the cleanup phase of the monorepo sync. All `.gitmodule` linkages and reference documentation have been purged.
- Several audio routines in `src/menus.c` and `src/audio/external.c` (`func_800CA388`) were recently mapped to `fade_all_channel_volume_scale`.
- Audio engine tick function (`func_800CB2C4`) labeled as `audio_game_loop_tick`.
- Thunder state handlers (`func_800CAC08` -> `reset_thunder_sound_effect`, `func_800C8920` -> `check_and_reset_thunder_effect`) and landing sound (`func_800CADD0` -> `play_kart_landing_sound_effect`) documented and labeled.
- Cutscene losing ceremony trigger (`func_800CB134`) labeled as `trigger_losing_ceremony_sequence`.
- Audio command queue in `src/audio/port_eu.c` dispatches commands via ring buffer `sAudioCmd` using `audio_cmd_queue_push_*`, flushes to the audio thread via `audio_cmd_queue_flush`, and unpacks in the RSP task runner via `audio_cmd_queue_process`. Sequence fade-in handled via `seq_player_fade_in`.
