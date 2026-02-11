# Project Vision: Mario Kart 64 Enhanced Decompilation

## Ultimate Goal
To create the definitive, most robust, and feature-rich open-source version of Mario Kart 64. This project aims to fully decompile the original game while seamlessly integrating modern enhancements, developer tools, and quality-of-life improvements without compromising the original game's soul.

## Design Philosophy

1.  **Authenticity:** The core driving physics, track designs, and character balancing must remain faithful to the original N64 release unless explicitly toggled by the user.
2.  **Modernization:** Optional enhancements (60 FPS, Widescreen, HD texture support) should be first-class citizens, integrated directly into the game's engine and UI.
3.  **Configurability:** Every enhancement must be toggleable. The "Extras" menu is the hub for customization, allowing players to tailor the experience to their preference (e.g., Purist vs. Enhanced).
4.  **Developer Friendly:** The codebase should serve as a learning resource and a foundation for modding. Debug tools (DVDL, Profilers, Flycam) should be robust and accessible.

## Key Pillars

### 1. Technical Excellence
*   **60 FPS:** Decoupled game logic to ensure smooth rendering without doubling game speed.
*   **Widescreen:** Proper aspect ratio handling with FOV adjustment and HUD pillarboxing.
*   **Optimization:** Code cleanup and performance improvements where possible, provided they don't alter behavior.

### 2. User Experience
*   **Seamless UI:** All features must be configurable via in-game menus. No recompilation should be required to change settings like Widescreen or Rubber Banding.
*   **Documentation:** Comprehensive manuals (`MANUAL.md`) and in-game tooltips.

### 3. Preservation & Modding
*   **Accurate Decompilation:** Maintain matching code where possible to ensure binary compatibility references.
*   **Extension Points:** Cleanly separate enhancements (e.g., `src/flycam.c`) from original logic to facilitate easy removal or modification.

## Future Roadmap
*   **Network Play:** Investigation into netplay capabilities.
*   **Modding API:** Lua or similar scripting support for custom game modes.
*   **Asset Replacement:** Easier pipelines for custom tracks and characters.

**"Keep on goin'! Don't ever stop!"**
