# copilot-instructions

**Refer to `LLM_INSTRUCTIONS.md` for universal guidelines.**

*   **Focus:** Provide extremely accurate and concise snippets for refactoring C code (MIPS assembly abstraction).
*   **Safety:** When providing suggestions, always verify they do not introduce endianness issues or pointer type mismatches common in N64 decompilations.
*   **Comments:** Emphasize generating highly detailed Doxygen comments for all new functions.