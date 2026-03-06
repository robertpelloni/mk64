# AI Agent Handoff

**Current Status:**
The project has reached a highly advanced state with version **1.2.0**.
All major planned features (60FPS, Widescreen, Fly Cam, Practice Mode, Save States, etc.) are implemented, tested, and documented.
The architecture for adding new settings (`src/save_extended.c`) is robust and scalable.

**Recently Completed:**
*   Implemented "Practice Mode" features (Speedometer, Input Display, Level Reset).
*   Implemented **Robust Save States** (Items, RNG, Laps).
*   Refactored Save Data logic to use a clean API.
*   Verified Crash Screen and Deadzone logic.
*   Removed `bobcoin`.
*   Implemented **PC Save Abstraction** and **Modding Hooks**.
*   Added "Save Ghost" to Practice Menu.

**Next Steps / Roadmap:**
*   **Netplay Research:** The user expressed interest in this long-term.
*   **Modding API:** Lua integration is a distant goal.
*   **Asset Replacement:** Easier pipelines for custom textures/models.
*   **Bug Fixes:** Monitor community feedback for issues with 60FPS physics or Save States.

**Codebase Notes:**
*   **Persistence:** Use `src/save_extended.c` for any new settings. Do not touch `src/save.c` packing logic manually.
*   **Menus:** Add new options to `src/menu_items.c` (text) and `src/menus.c` (logic).
*   **Features:** Use `gEnable[Feature]` flags in `src/main.c`.

**"Keep on goin'!"**
