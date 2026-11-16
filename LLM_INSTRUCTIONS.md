# AI Agent Instructions

**Universal Guidelines for All Models (Claude, Gemini, GPT, etc.)**

## Core Philosophy
1.  **Deep Planning:** Always start with a "Deep Planning" phase. Verify requirements, verify code state, and plan your steps explicitly using `set_plan`.
2.  **Verification:** Never assume. Always verify file existence, content, and the success of your actions (e.g., `read_file` after `write_file`).
3.  **Documentation:** Update documentation (`ROADMAP.md`, `TODO.md`, `CHANGELOG.md`, `DASHBOARD.md`) after every significant change.
4.  **Preservation:** Do not break existing features. Use `SaveExtended` API for new persistent settings.
5.  **Quality:** Comment your code. Explain *why* you are doing something, not just *what*.

## Codebase Specifics
*   **Settings:** Use `gEnable...` or `gToggle...` globals defined in `src/main.h`. Persist them via `src/save_extended.c`.
*   **Menus:** Modifying menus involves `src/menus.c` (logic) and `src/menu_items.c` (text/rendering).
*   **Compilation:** The project requires a specific ROM asset extraction. You cannot compile here, so rely on static analysis and strong logic.
*   **Submodules:** The `tools/` directory contains submodules. Do not modify them unless explicitly instructed.

## Model-Specific Notes

### Claude
*   Focus on architectural integrity and comprehensive explanations.
*   Use your large context window to analyze multiple files simultaneously.

### Gemini
*   Leverage your reasoning to infer missing context (like the `itemOverride` logic).
*   Be proactive in suggesting improvements.

### GPT
*   Follow the plan strictly.
*   Double-check your diffs/file writes.

## Versioning
*   Increment `VERSION` file on every feature completion.
*   Update `CHANGELOG.md` with the new version and details.
