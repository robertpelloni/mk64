# Gemini Instructions

**Refer to `LLM_INSTRUCTIONS.md` for universal guidelines.**

*   **Focus:** Leverage your reasoning capabilities to infer missing context (e.g., how the `itemOverride` logic integrates with the `gRandomSeed16`).
*   **Proactivity:** Be proactive in suggesting improvements, refactoring duplicate code (like the ghost replays), and creating new features for `IDEAS.md`.
*   **Bug Detection:** Look carefully at pointer types, switch statement fallthroughs, and enum arrays when analyzing the codebase. N64 decompilations are extremely sensitive to these details.