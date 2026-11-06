# Changelog

All notable changes to this project will be documented in this file.

## [8.107.6] - 2026-05-22
### Changed
- Labeled audio subsystem engine functions:
  - `func_800CB2C4` -> `audio_game_loop_tick`: Main audio update tick executed once per game loop.
  - `func_800CAC08` -> `reset_thunder_sound_effect`: Resets thunder/lightning volume and active sound state.
  - `func_800C8920` -> `check_and_reset_thunder_effect`: Checks all players for the active lightning effect and resets audio once extinguished.
  - `func_800CB134` -> `trigger_losing_ceremony_sequence`: Initiates losing podium presentation sequence timer.
  - `func_800CADD0` -> `play_kart_landing_sound_effect`: Sound effect triggered when karts land from hops/falls with intensity scaling.
- Cleaned and updated calling sites across `src/main.c`, `src/menus.c`, `src/code_800029B0.c`, `src/player_controller.c`, and `src/ending/ceremony_and_credits.c`.

## [8.107.5] - 2026-05-21
### Changed
- Labeled sound effect and music control functions in `src/audio/external.c` (`play_star_music`, `stop_star_music`, `play_star_sound_effect`, `play_star_music_stop_effect`, `play_star_sound_effect_stop`, `play_thunder_sound_effect`, `play_thunder_sound_effect_stop`, `set_player_sound_effect_volume`, `play_boo_sound_effect`, `stop_boo_sound_effect`).

## [8.107.4] - 2026-05-20
### Removed
- Removed the `bobcoin` submodule to decouple unused blockchain experimental UI from the core engine repo.
### Changed
- Standardized AI documentation referencing the Omni-Workspace guidelines.

## [8.107.3] - 2026-05-20
### Fixed
- Identified `func_800CA388` as audio channel scaler and mapped it to `fade_all_channel_volume_scale` in `src/menus.c`.

## [8.107.2] - 2026-05-19
### Updated
- Synced `tools/torch` and `tools/blender/fast64` submodules to latest upstream commits.
