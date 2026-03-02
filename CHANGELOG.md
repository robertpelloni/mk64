# Changelog

## [1.6.0] - PC Porting & Modding Support
### Added
- **PC Save System:** Abstracted save logic to use file I/O instead of N64 Controller Pak calls. Added support for saving "Practice Ghosts" to disk.
- **Modding Hooks:** Implemented `Mod_OnRaceStart`, `Mod_OnLapComplete`, and `Mod_OnGameTick` hooks for external scripting support.
- **Asset Registry:** Added `mod_assets.c` to facilitate data-driven asset replacement (textures/models).

### Changed
- **UI Updates:** Renamed "Controller Pak" menu options to "Save File" / "Disk" to reflect the PC environment.
- **Refactoring:** Created `src/pc_port/` and `src/modding/` directories to separate platform-specific logic.

## [1.5.2] - Save System Safety & Optimization
### Changed
- **Performance:** Optimized menu save logic. Settings like "Stick Deadzone" and "Item Control" now only trigger a save when exiting the menu, preventing EEPROM wear and menu lag.
- **Verification:** Confirmed that the extended settings storage in `checksum[0]` is safe and does not conflict with the game's integrity checks or checksum calculations.

## [1.5.0] - Robust Save States & Feedback
### Added
- **Robust Save States:** Save States (L + D-Pad Left/Right) now preserve:
    - **Held Item:** The item currently in the player's inventory.
    - **Lap Count:** The current lap number.
    - **RNG State:** The Random Number Generator seed, ensuring consistent outcomes for deterministic events.
- **On-Screen Feedback:** Added "STATE SAVED" and "STATE LOADED" text overlays to provide immediate visual confirmation of save state actions.

### Changed
- Updated `MANUAL.md` with detailed Save State information.
- Refined Save State logic in `src/main.c` to integrate deeply with player and game state variables.

## [1.4.0] - Practice Tools: Lap Skip & Timer Freeze
### Added
- **Lap Skip:** Added "Lap Skip" feature (L + D-Pad Up) to instantly complete the current lap. Useful for practicing specific laps or finishing races quickly.
- **Timer Freeze:** Added "Timer Freeze" feature to stop the race timer. Useful for infinite practice sessions.
- **Practice Menu:** Updated Practice Menu UI to include Lap Skip and Timer Freeze options with tooltips.
- **Persistence:** Both features are saved to extended save data.

### Changed
- Updated `MANUAL.md` with new features.
- Updated `ROADMAP.md` and `TODO.md` to reflect progress.
- Extended save data logic to support `unknownBytes[1]` for Timer Freeze persistence.

## [1.3.0] - Item Control & Practice Enhancements
### Added
- **Item Control:** New "Practice Options" menu item allowing players to force specific items (Banana, Shells, Stars, etc.) or disable items completely.
- **UI Descriptions:** Added on-screen help text/tooltips for all Extras and Practice menu options to explain functionality.
- **Practice Menu Polish:** Reorganized Practice Menu with "Item Control" and improved navigation.
- **Persistence:** Item Control settings are saved to EEPROM (extended save data).

### Changed
- Updated `MANUAL.md` with new features.
- Updated `ROADMAP.md` and `TODO.md` to reflect progress.

## [1.2.0] - Audio & Deadzone
### Added
- Analog Stick Deadzone configuration.
- Music and SFX toggles.
- Robust save data persistence for new settings using `checksum[0]` packing.

## [1.1.0] - Practice Tools
### Added
- Input Display.
- Speedometer.
- Level Reset (L+R+Start).
- Fly Cam.
- Widescreen, 60FPS, Fast Boot.
