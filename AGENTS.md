# AI Agent Instructions & Protocols

This file contains universal instructions for all AI agents (Google Jules, Claude, GPT, etc.) working on this repository.

## Core Directives

1.  **Autonomous Execution:** Strive to complete tasks fully autonomously. Plan deeply, execute, verify, and document.
2.  **Documentation First:** Update documentation (`MANUAL.md`, `README.md`, `DASHBOARD.md`, etc.) alongside code changes. Code without documentation is incomplete.
3.  **No Regressions:** Always verify that new features do not break existing functionality. Use intelligent merging for feature branches.
4.  **Submodule Management:** Keep submodules clean and updated. When updating, ensure compatibility and document versions in `DASHBOARD.md`.

## Versioning & Changelog Protocol

*   **Version File:** The project version is stored in the `VERSION` file (plaintext, e.g., `1.1.0`).
*   **Versioning Scheme:** Semantic Versioning (MAJOR.MINOR.PATCH).
    *   **MAJOR:** Incompatible API changes or massive rewrites.
    *   **MINOR:** New functionality in a backward-compatible manner (e.g., new Extras menu options).
    *   **PATCH:** Backward-compatible bug fixes (e.g., Flycam logic fix).
*   **Changelog:** Update `CHANGELOG.md` with every version bump.
    *   Format: `## [Version] - YYYY-MM-DD` followed by `### Added`, `### Changed`, `### Fixed`.
*   **Commit Messages:** When bumping the version, the commit message must reference the new version number (e.g., "Bump version to 1.1.0").

## Feature Implementation Guidelines

1.  **UI Representation:** Every backend feature must have a corresponding UI element (menu item, toggle, display).
    *   Use labels, tooltips, and help text to explain functionality to the user.
2.  **Persistence:** Settings should generally be saved to EEPROM unless explicitly temporary (like "Unlock All").
    *   Use bit-packing if necessary to preserve save data structure size.
3.  **Safety:** Avoid hard-crashes. Use fallback logic (e.g., default camera modes) if a feature fails or is toggled off in an unsafe state.

## Universal Knowledge Access

*   **VISION.md:** Refer to this for the ultimate goal and design philosophy.
*   **PROJECT_STRUCTURE.md:** Refer to this for navigating the codebase.
*   **DASHBOARD.md:** Refer to this for submodule status and build info.

**Keep going! Don't ever stop!**
