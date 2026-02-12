# Universal AI Agent Instructions & Protocols

**Version:** 1.0.0
**Last Updated:** 2024-05-23

This document serves as the **Single Source of Truth** for all AI models (Google Jules, Claude, Gemini, GPT, Copilot, etc.) working on this repository. All other agent-specific instruction files should reference this document.

## 1. Core Philosophy: "The Ultimate Vision"

**Goal:** Create the definitive, most robust, and feature-rich open-source version of Mario Kart 64.
**Mantra:** "Keep on goin'! Don't ever stop! Don't ever quit!"

*   **Authenticity:** Preserve the original game's soul (physics, balancing) unless explicitly toggled.
*   **Modernization:** Integrate modern features (60FPS, Widescreen, HD Textures) seamlessly into the engine.
*   **Configurability:** EVERYTHING must be toggleable via the in-game UI (Extras Menu).
*   **Documentation:** Code without documentation is unfinished. Update docs with every change.

## 2. Operational Protocols

### A. Autonomy & Planning
1.  **Deep Analysis:** Before writing code, deeply analyze the project state, `VISION.md`, `ROADMAP.md`, and conversation history.
2.  **Plan First:** Create a detailed plan. Verify assumptions. Ask clarifying questions if the user's intent is ambiguous.
3.  **Execute & Verify:** Implement features iteratively. Verify usage with static analysis or compilation if available.
4.  **No Pausing:** Complete a feature, commit, push, and immediately proceed to the next. Do not ask for confirmation unless stuck.

### B. Coding Standards
1.  **Style:** Match existing C code style (K&Rish, specific naming conventions `gVariable`, `func_800...`).
2.  **Safety:** Avoid hard crashes. Use defensive programming.
3.  **Integration:** Hook features into existing systems (`src/main.c`, `src/menus.c`) rather than creating isolated silos.
4.  **UI Representation:** Every backend feature MUST have a frontend UI element (Label, Toggle, Slider, Tooltip).

### C. Submodule Management
1.  **Keep Clean:** Ensure submodules are initialized and updated.
2.  **Documentation:** Update `DASHBOARD.md` with version/commit hashes when submodules change.
3.  **Merging:** When merging, resolve conflicts intelligently. Prioritize preserving local features.

## 3. Versioning & Release Protocol

*   **File:** `VERSION` (Plain text, e.g., `1.2.0`).
*   **Scheme:** Semantic Versioning (Major.Minor.Patch).
    *   **Major:** Breaking changes.
    *   **Minor:** New features (e.g., New Menu Option).
    *   **Patch:** Bug fixes.
*   **Changelog:** ALWAYS update `CHANGELOG.md` before committing a version bump.
*   **Commit Message:** Must include "Bump version to X.Y.Z".

## 4. Documentation Requirements

*   **`MANUAL.md`:** User-facing guide. Update with new features.
*   **`VISION.md`:** Long-term goals.
*   **`PROJECT_STRUCTURE.md`:** File layout explanation.
*   **`DASHBOARD.md`:** Submodule tracking.
*   **Doxygen:** Add `/** @brief ... */` comments to all new functions and global variables.

## 5. Handoff Protocol

When finishing a session:
1.  **Commit & Push:** Ensure all work is saved.
2.  **Create `HANDOFF.md`:** Summarize what was done, what is broken, and exactly what the next agent should do.
3.  **Sync:** Fetch and pull to ensure the repo is up to date.

---

## 6. Deep Technical Analysis & Implementation Guide

This section documents critical architectural patterns and reverse-engineered structures to assist future agents in maintaining and expanding the codebase.

### A. Save Data & Persistence Strategy
The game uses EEPROM for saving. To avoid shifting offsets and invalidating existing saves, we use a **Bit-Packing Strategy** to store new settings within existing, unused, or repurposed fields.

*   **File:** `src/save.c`
*   **Structure:** `SaveData.main`
*   **Packing Map:**
    *   **`soundMode` (8 bits):** Originally just Stereo/Mono/Headphone (2 bits). We use the upper 6 bits.
        *   Bit 0-1: Original Sound Mode
        *   Bit 2: **60 FPS**
        *   Bit 3: **Widescreen**
        *   Bit 4: **Fast Boot**
        *   Bit 5: **Disable Rubber Banding**
        *   Bit 6: **Debug Mode**
        *   Bit 7: **Fly Cam**
    *   **`checksum[0]` (8 bits):** Originally a checksum byte, now repurposed.
        *   Bit 7: **Resource Meters** (Boolean)
        *   Bit 6: **Toggle Music** (Boolean)
        *   Bit 5: **Toggle SFX** (Boolean)
        *   Bits 0-4: **Analog Stick Deadzone** (Integer 0-31)

**Protocol:** When adding a new boolean setting, find a spare bit in `checksum` bytes or unused struct padding. **DO NOT** change the size of `SaveData`.

### B. Menu System Architecture
The menu system is split between definition and logic.

1.  **Definitions (`src/menu_items.c`):**
    *   `gTextExtrasMenu`: Array of strings for the menu labels.
    *   `gTextExtrasHelp`: Array of strings for tooltips.
    *   `setup_menus()`: Function where `add_menu_item(...)` is called to construct the menu tree.
2.  **Logic (`src/menus.c`):**
    *   `handle_menus_default()`: The main input loop.
    *   **Rendering:** Switch cases in `func_800A1FB0` (or similar large render functions) handle drawing specific menu types.
    *   **Input:** Switch cases in update functions (like `func_800A9E58`) handle button presses.

**Protocol:** To add a menu item:
1.  Add string to `src/menu_items.c`.
2.  Register it in `setup_menus`.
3.  Implement input handling in `src/menus.c` (often by hooking into the generic Extras menu handler or creating a new case).

### C. 60 FPS Decoupling Logic
The N64 original runs logic and rendering tightly coupled at 30Hz. To achieve 60FPS without speeding up the game:

*   **File:** `src/main.c`
*   **Mechanism:** Time Accumulator.
*   **Variables:**
    *   `gTickSpeed`: Logic updates per frame (standard is 1).
    *   `accum`: Accumulates time deltas from `osGetTime`.
*   **Logic:** The render loop runs as fast as possible (vsync limited to 60). The game logic (`update_game()`) runs in a `while (accum >= LOGIC_STEP)` loop.
*   **Caveat:** Some systems (audio, certain animations) might still be frame-bound. Check `gGlobalTimer` usage.

### D. Global Feature Flags
All enhancements are controlled by global variables defined in `src/main.c` and exposed in `src/main.h`.

*   **Naming Convention:** `gEnable[Feature]` (e.g., `gEnable60FPS`) or `gToggle[Feature]` (e.g., `gToggleMusic`).
*   **Usage:** Wrap logic modifications in `if (gEnableFeature) { ... } else { original_logic(); }` to preserve authenticity.

### E. Submodule Quirks
*   **Tools:** `asm-differ`, `decomp-permuter`, `fast64` are in `tools/`.
*   **Common Error:** `refusing to merge unrelated histories`.
*   **Fix:** `git submodule update --init --recursive` followed by a hard reset if necessary: `cd tools/submodule && git fetch origin && git reset --hard origin/main`.

---
*Refer to this document for all procedural questions.*
