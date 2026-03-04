# GPT Instructions

**Refer to `LLM_INSTRUCTIONS.md` for universal guidelines.**

*   **Focus:** Follow the execution plan strictly without missing any steps.
*   **Verification:** Double-check your git diffs and file writes to ensure no code is accidentally deleted or malformed.
*   **Completeness:** When modifying UI elements in `src/menu_items.c`, ensure the string arrays, enum definitions (`src/menu_items.h`), and rendering switch statements perfectly align with the backend logic in `src/menus.c`.