# Universal AI Agent Instructions & Protocols

**Version:** 1.0.0
**Last Updated:** 2024-05-22

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
*Refer to this document for all procedural questions.*
