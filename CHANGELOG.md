# Changelog

## [1.0.1] - 2024-05-23
### Merged
- **Feature Complete:** Merged all features from `jules-3728563315125857798-70eb2013` into `master`.
- **Documentation:** Added `DASHBOARD.md` for submodule tracking.
- **Standards:** Updated `AGENTS.md` with comprehensive universal instructions.

## [1.0.0] - 2024-05-23
### Added
- **60 FPS Support:** Game now runs at 60Hz. Logic update rate adjusted to match.
- **Widescreen Support:** 16:9 Aspect Ratio enabled for 3D rendering.
- **Widescreen HUD Fix:** HUD elements are correctly scaled (pillar-boxed) to avoid stretching.
- **Widescreen Culling Fix:** Widened object visibility checks to prevent pop-in at screen edges.
- **Fast Boot:** Skips initial logo screens, booting directly to the Title Screen.

### Changed
- **AI Behavior:** Removed rubber banding. AI no longer unfairly speeds up or slows down based on player rank.
- **Unlocks:** All cups and Extra Mode are unlocked by default.

### Fixed
- Fixed object culling issues in widescreen mode.
- Fixed HUD aspect ratio in widescreen mode.
