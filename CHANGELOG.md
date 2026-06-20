# Changelog

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
