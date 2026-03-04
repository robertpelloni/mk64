# AI Agent Instructions (Universal)

**Universal Guidelines for All Models (Claude, Gemini, GPT, Copilot, etc.)**

## Core Philosophy & Process
1.  **Deep Planning Phase:** Before making *any* code changes, interact with the user to fully understand their requirements. Ask clarifying questions until you have absolute certainty. Validate your assumptions. Do not set a plan until you are 100% sure.
2.  **Autonomous Execution:** Once a plan is set and approved, execute it autonomously. Do not stop. Keep going until the feature is 100% implemented, robust, and documented. Use subagents or internal reasoning steps if possible to break down complex tasks. Do not ask for confirmation between steps unless blocked.
3.  **Verification:** Never assume success. After editing a file, always read it back to verify the changes were applied correctly. After a major change, verify the logic conceptually or via compilation if possible.
4.  **Preservation:** Do not break existing features. Ensure backwards compatibility when refactoring. Erroneous regressions are unacceptable.
5.  **Quality & Commenting:** Comment your code exhaustively. Explain *why* you are doing something, the reasoning, findings, side effects, optimizations, alternate methods considered, and why the chosen method is best. If existing code lacks comments, add them.

## Documentation & Project Management (Crucial)
After *every* feature implementation or significant step, you must comprehensively update the following files:
*   `VERSION`: Increment the version number string.
*   `CHANGELOG.md`: Document the new version number and all changes in detail.
*   `ROADMAP.md`: Update the high-level project trajectory. Mark completed items.
*   `TODO.md`: Add fine details, bug fixes, or minor features discovered during development. Remove completed items.
*   `DASHBOARD.md`: Track all submodules (versions, dates, paths) and explain the project directory structure.
*   `VISION.md`: Ensure the ultimate goal and design of the project are accurate and expanded upon based on new developments.
*   `MEMORY.md` / `HANDOFF.md`: Document observations, design preferences, and the exact state of the project for the next AI session.
*   `DEPLOY.md`: Keep deployment/build instructions up to date.
*   `MANUAL.md`: Ensure all implemented features are thoroughly documented for the end-user (controls, descriptions, tooltips).
*   `IDEAS.md`: Continuously populate this with creative suggestions for refactoring, new features, or architectural pivots.

## Codebase Specifics
*   **Git Operations:** Sync with the server regularly. Intelligently merge feature branches into `main` without losing progress. Update submodules and merge upstream changes (including forks) carefully. Push updates. If a push fails due to network/auth issues, document the failure but proceed with local development.
*   **Settings Persistence:** Use `gEnable...` or `gToggle...` globals defined in `src/main.h`. Persist them via the `SaveExtended_` API in `src/save_extended.c`. Do not modify base save logic directly to ensure compatibility.
*   **UI Representation:** Every feature MUST be represented in the UI. Modifying menus involves `src/menus.c` (backend logic) and `src/menu_items.c` (frontend text arrays, switch statements, and rendering). If you add a feature, you must add it to both files.
*   **Compilation:** The project requires an original game ROM (`baserom.us.z64`) to extract assets, which is not included. You cannot compile successfully without it, so rely on static analysis and strong logic.
*   **Linking:** New C files must be explicitly added to `mk64.ld` in the `.main` segment to be compiled and linked.
