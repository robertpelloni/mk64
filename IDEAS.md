# MK64 Enhancement Ideas & Future Directions

This document outlines potential future features, refactors, and pivots for the Mario Kart 64 Enhancement project.

## 1. True PC Porting (Native Executable)
Currently, this project produces an N64 ROM. A major pivot would be to create a native PC port (similar to *sm64-port* or *Ship of Harkinian*).
*   **Rendering:** Replace the GBI/RDP commands with a modern graphics API (OpenGL, Vulkan, DirectX). This would allow for arbitrary resolutions, uncapped framerates, and texture replacement without ROM size limits.
*   **Audio:** Replace the N64 audio synthesis loop with an SDL2/OpenAL backend.
*   **Input:** Map keyboard/mouse and modern controllers directly to game inputs.
*   **Benefits:** Easier modding, better performance, wider accessibility.

## 2. Online Multiplayer (Netcode)
Implementing true online play would revolutionize the game.
*   **Architecture:** Lockstep input sharing (simpler but sensitive to lag) vs. State synchronization + Rollback (complex but smoother).
*   **Backend:** Use `ENet` or `SteamNetworkingSockets` (if PC port). For N64 hardware, maybe a serial-to-Wi-Fi adapter interface?
*   **Challenges:** RNG synchronization is critical. The current `gRandomSeed16` must be strictly deterministic.

## 3. Advanced Modding API
Expand the current "Hooks" system into a full scripting environment.
*   **Lua / Python:** Embed a lightweight interpreter to allow users to write game logic (e.g., custom game modes like "Capture the Flag" or "Elimination") without recompiling C code.
*   **Hot-Reloading:** Allow reloading scripts/assets while the game is running.

## 4. Asset Replacement System (HD Texture Pack Support)
*   **Implementation:** Hook into the texture loading functions (`load_menu_img`, `dma_copy`). Check a "mod" directory for a replacement file (PNG/BMP) matching the texture ID/address.
*   **Upscaling:** Implement runtime AI upscaling or support pre-scaled assets.

## 5. Custom Track Editor / Level Builder
*   **In-Game Editor:** A simple tile-based editor for placing objects, walls, and checkpoints.
*   **External Tool Integration:** Better integration with Blender/Fast64 to streamline the "import custom track" workflow.

## 6. Physics Overhaul / "Pro Mode"
*   **Toggles:** Option to disable specific physics quirks (wall bonking speed loss, tumbling).
*   **Tuning:** Sliders for gravity, acceleration, top speed, and turning radius in the "Practice Options" menu.

## 7. Ghost Data Cloud Sync
*   **Leaderboards:** Upload time trial ghosts to a central server.
*   **Rival Download:** Download top global ghosts to race against.

## 8. Accessibility Features
*   **Colorblind Modes:** Filters for the framebuffer.
*   **Button Remapping:** Full in-game controller remapping.
*   **Assist Mode:** Auto-accelerate, smart steering (keep on track).
