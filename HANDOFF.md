# Session Handoff - 2026-05-20 (v8.107.4)

## Executive Summary
Completed a massive repository re-initialization mapping out the MK64 documentation suite to comply with the Omni-Workspace monorepo guidelines. Synced tools submodules.

### Recent Fixes & Additions
- **Documentation Overhaul:** Created and wired up `VISION.md`, `ROADMAP.md`, `TODO.md`, `DEPLOY.md`, `CHANGELOG.md`, `MEMORY.md`, `AGENTS.md`, and all model-specific LLM instructions (`CLAUDE.md`, `GEMINI.md`, `GPT.md`, `copilot-instructions.md`).
- **Submodule Syncing:** Synced `tools/torch` and `tools/blender/fast64` and merged active main branches natively.
- **Audio Labelling:** Renamed `func_800CA388` to `fade_all_channel_volume_scale` in the C source resolving a lingering `TODO`.

## Next Steps for Implementor
1. **Zero-Latency Rust Bridge:** Review the `TODO.md` backlog regarding the porting of collision logic (`src/racing/`) into native Rust routines to circumvent N64 physics limitations.
2. **Continue C Renaming:** There are hundreds of `func_800...` references remaining across the `src/` tree, particularly in the actor and course logic segments. Contextual mapping of these functions is the primary short-term implementation priority.

# Session Handoff

## Summary
Transformation of Mario Kart 64 decompilation into a modernized "Greatest Racing Game" edition.

## Accomplishments
- **60 FPS Support:** Implemented by removing double VBlank wait and adjusting logic tick speed in `src/main.c`.
- **Widescreen (16:9):** Enabled by adjusting aspect ratio in `src/racing/skybox_and_splitscreen.c`.
- **Widescreen HUD Fix:** Corrected HUD stretching by adjusting orthographic projection in `src/math_util_2.c`.
- **Widescreen Culling Fix:** Widened object visibility check angles in `src/code_80086E70.c` to prevent pop-in.
- **Unlock Content:** Forced `is_cc_mode_complete` to true in `src/save.c`, unlocking Extra Mode and title screens.
- **Remove Rubber Banding:** Disabled AI speed cheating logic in `src/cpu_vehicles_camera_path/cpu_speed_control.inc.c` and `src/cpu_vehicles_camera_path.c`.
- **Fast Boot:** Changed initial menu state to skip logos in `src/menus.c`.

## Known Issues
- 60 FPS in multiplayer (3P/4P) might be taxing on original hardware (intended for emulation/recomp).
- HUD elements are centered in 4:3 area; UI could be repositioned to edges in future updates.

## Next Steps
- Verify all changes on target hardware/emulator.
- Consider UI element repositioning for true 16:9 HUD layout.
- Potential further AI tuning.

