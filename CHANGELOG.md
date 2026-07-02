# Changelog

All notable changes to this project will be documented in this file.

## [8.107.6] - 2026-07-01
### Added
- Created `DASHBOARD.md` to map out the status of new mechanics and features per the `UNIVERSAL_LLM_INSTRUCTIONS.md`.

### Changed
- Massively refactored and renamed `func_800C...` functions and `D_80...` global data variables in `src/audio/external.c` and `src/audio/port_eu.c` to improve code readability and maintainability.
- Renamed ghost data and save management functions in `src/save.c`, `src/menus.c`, and `src/replays.c` to reflect their true purposes.

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
- Renamed remaining func_800... routines in src/racing/race_logic.c and src/racing/actors.c to descriptive names.
