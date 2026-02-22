# Changelog

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
