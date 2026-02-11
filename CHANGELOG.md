# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.1.0] - 2024-05-22

### Added
- **Extras Menu:** A new menu accessible from options to toggle enhancements.
- **60 FPS Mode:** Decoupled game logic allowing for smoother rendering.
- **Widescreen 16:9:** Proper aspect ratio support with HUD pillarboxing and expanded FOV.
- **Fly Cam:** A free-roaming camera mode for exploring levels (debug feature).
- **Fast Boot:** Option to skip startup logos.
- **Resource Meters:** Toggleable on-screen display of CPU/GPU usage.
- **Documentation:** Added `AGENTS.md`, `VISION.md`, `DASHBOARD.md`, and updated `MANUAL.md`.

### Changed
- **Save Data:** Enhanced options are now persisted to EEPROM using bit-packing in `soundMode` and spare checksum bytes.
- **Debug Mode:** Can now be toggled via the Extras menu and persisted.
- **Submodules:** Removed `bobcoin` submodule.

### Fixed
- **Fly Cam:** Fixed a bug where players lost control after exiting Fly Cam (bitwise logic error).
- **Fly Cam:** Fixed fallback camera logic to correctly target the player when Fly Cam is disabled.
