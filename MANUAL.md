# Mario Kart 64 Enhanced - User Manual

This modified version of Mario Kart 64 includes several enhancements and new features accessible through the **Options** menu.

## Extras Menu

Navigate to **Options** -> **Extras** to access the new settings.

### Feature Descriptions

#### 1. 60 FPS Mode
*   **Default:** OFF
*   **Description:** Increases the game's rendering framerate from the original 30 FPS to 60 FPS.
*   **Note:** Game logic speed is preserved (it does not run at double speed). This provides a smoother visual experience.

#### 2. Widescreen 16:9
*   **Default:** OFF
*   **Description:** Adjusts the game's aspect ratio to 16:9 for modern widescreen displays.
*   **Details:** This setting also widens the field of view (FOV) to prevent objects from "popping" in and out at the edges of the screen, a common issue when stretching 4:3 games.

#### 3. Fast Boot
*   **Default:** OFF
*   **Description:** Skips the startup logos and intro sequence, booting directly to the Start Menu.
*   **Usage:** Useful for quick testing or resetting. Note: You must save the settings for this to take effect on the next boot (settings persistence depends on the emulator/console state save capabilities, as these settings are currently runtime-only).

#### 4. Disable Rubber Banding
*   **Default:** OFF
*   **Description:** Disables the "Rubber Banding" AI logic.
*   **Details:** In the original game, AI opponents artificially speed up when behind and slow down when ahead to keep races close. Enabling this option removes this artificial speed adjustment, making the AI rely on their standard speed stats.

#### 5. Unlock All
*   **Default:** OFF
*   **Description:** Temporarily unlocks all game content.
*   **Content:** Unlocks the "Extra" mode (Mirror Mode), all cups, and potentially other hidden content.
*   **Note:** This is a runtime toggle. It does not permanently overwrite your save file unless you complete a race or perform a save action while it is active.

## Saving Settings

Currently, these "Extras" settings are stored in memory and may reset upon powering off the console, depending on the specific implementation of the save system or emulator state. Standard game progress (Save Data) works as normal.
