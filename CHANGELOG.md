# Changelog

## [8.107.6] - 2026-06-27

### Refactored
- Continued decompilation and renaming of `func_800...` audio and core logic routines (e.g., `fade_and_issue_audio_command`, `issue_audio_command`) across multiple modules to support Phase 1 perfect decompilation goals.

All notable changes to this project will be documented in this file.

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

## [1.7.2] - Phase 2 Modern Mechanics
### Added
- **Item Holding (Double Dash):** Players can now carry a secondary reserve item (`sReserveItems`). If the active item slot is occupied, new items from boxes are placed in reserve.
- **Item Swapping:** Pressing `L_TRIG` swaps the currently active item with the reserve item, allowing for tactical item holding and defensive dragging.

## [1.7.3] - Phase 2 Coin Mechanics
### Added
- **Coin Speed Boost:** The physics engine (`player_controller.c`, `spawn_players.c`) now calculates `topSpeed` using a modifier based on the player's active coin count (`sCoins`), giving a 1.5f maximum velocity boost per coin.

## [8.109.0] - 2026-06-23
### Added
- **Phase 5 Dynamics:** Anti-Gravity. `ANTI_GRAVITY_WALL` surface modifier allows karts to stick to walls. Spin Boosts occur on player collisions instead of standard crashing.
- **Phase 6 Dynamics:** Half-Pipes. `HALF_PIPE` surface modifier pulls kart to walls and forces an auto-trick pop at the apex.
