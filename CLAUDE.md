# Claude Instructions

**Refer to `LLM_INSTRUCTIONS.md` for universal guidelines.**

*   **Focus:** Use your large context window to deeply analyze multiple files (e.g., `src/replays.c` alongside `src/menus.c` and `src/save.c`).
*   **Architectural Integrity:** When implementing features like the PC Port abstraction, think comprehensively about how it affects the entire N64 filesystem logic (`osPfs`).
*   **Documentation:** Your explanations in `HANDOFF.md` and `MEMORY.md` should be exhaustive. When refactoring, detail the exact differences between the original logic and your new logic.