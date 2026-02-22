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
*   **Details:**
    *   Expands the 3D rendering field of view (FOV) to prevent object pop-in at the edges.
    *   Corrects the Heads-Up Display (HUD) aspect ratio by "pillarboxing" it to the center of the screen, ensuring text and UI elements appear in their correct 4:3 proportions instead of being stretched.

#### 3. Fast Boot
*   **Default:** OFF
*   **Description:** Skips the startup logos and intro sequence, booting directly to the Start Menu.

#### 4. Disable Rubber Banding
*   **Default:** OFF
*   **Description:** Disables the "Rubber Banding" AI logic.
*   **Details:** In the original game, AI opponents artificially speed up when behind and slow down when ahead to keep races close. Enabling this option removes this artificial speed adjustment, making the AI rely on their standard speed stats.

#### 5. Unlock All
*   **Default:** OFF
*   **Description:** Unlocks all game content.
*   **Content:** Unlocks the "Extra" mode (Mirror Mode), all cups, and all characters (if any were locked).
*   **Note:** This unlock is persistent as long as the setting is enabled.

#### 6. Fly Cam
*   **Default:** OFF
*   **Description:** Enables a free-flying camera mode.
*   **Details:** Allows you to detach the camera from the player and fly around the level freely.
*   **Controls (Controller 1):**
    *   **Toggle Mode:** L Trigger (In-game)
    *   **Move:** Analog Stick (Rotate), A (Forward), B (Backward), C-Up (Up), C-Down (Down)
    *   **Speed Boost:** Z Trigger (Hold while moving)
    *   **Target Player:** R Trigger (Toggle tracking), C-Left (Next Player), C-Right (Previous Player)
    *   **Switch Cam Mode:** D-Pad Up (Toggles between player position and previous flycam position)

#### 7. Resource Meters
*   **Default:** OFF
*   **Description:** Displays system resource usage bars (CPU, GPU, etc.) on-screen.
*   **Details:** Useful for performance analysis.
    *   **Red:** Sound Updates / VBlank Duration
    *   **Yellow:** Level Script Execution / RSP Duration
    *   **Orange:** Rendering / RDP Duration

#### 8. Debug Mode
*   **Default:** OFF
*   **Description:** Enables the game's debug menu and additional developer features.
*   **Features:**
    *   **Quick Menu Navigation:** Press Start to skip through menus.
    *   **Resource Meters Shortcut:** Toggle meters during gameplay by holding R and tapping B (L must not be held).
    *   **Soft Reset:** Hold A + B + R + L to reset to the start screen.
    *   **Race Info:** During a single-player race staging, tap L while holding A + B to view player direction and path points.
    *   **Lap Skip:** Tap D-Pad Up (P1), Right (P1+P2), or Down (All) to set players to the final lap.
    *   **Instant Start:** Press Z on any controller to immediately start the race.
    *   **Character Switch:** During the ceremony cutscene, hold C-Buttons or D-Pad to switch characters.

#### 9. Stick Deadzone
*   **Default:** 7
*   **Range:** 0 to 15
*   **Description:** Adjusts the analog stick's deadzone sensitivity.
*   **Details:**
    *   **Deadzone:** The area around the center of the stick where input is ignored.
    *   **Controls:**
        *   **Left/Right:** Decrease/Increase value by 1.
        *   **A Button:** Cycles through presets (0, 7, 15, 20).
    *   **Usage:** Increase this value if your controller has drift or feels too sensitive. Decrease it for more responsive input on tight sticks.

#### 10. Toggle Music
*   **Default:** ON
*   **Description:** Toggles the in-game background music on or off.

#### 11. Toggle SFX
*   **Default:** ON
*   **Description:** Toggles the in-game sound effects (SFX) on or off.

#### 12. Input Display
*   **Default:** OFF
*   **Description:** Displays a visual overlay of the controller inputs (Analog Stick, A, B, Z, R, Start) in the bottom right corner of the screen.

#### 13. Speedometer
*   **Default:** OFF
*   **Description:** Displays an on-screen speedometer bar in the bottom left corner.
*   **Details:** Visualizes the player's current speed with a color-coded bar (Green -> Yellow -> Red).

#### 14. Level Reset & Save States
*   **Default:** OFF
*   **Description:** Enables practice tools including Level Reset and Save States.
*   **Controls:**
    *   **Restart Race:** Press **L + R + Start**.
    *   **Save State:** Press **L + D-Pad Left** (Saves position & velocity).
    *   **Load State:** Press **L + D-Pad Right** (Teleports to saved state).

#### 15. Item Control
*   **Default:** Default (Normal Logic)
*   **Description:** Allows you to override the item box probability logic.
*   **Options:**
    *   **Default:** Normal game behavior.
    *   **None:** Item boxes give nothing.
    *   **Banana, Shells, Stars, etc.:** Forces every item box to yield the selected item.

## Saving Settings

All settings changed in the **Extras** menu are now **saved permanently** to the game's EEPROM (save file).
*   Settings are saved automatically when you change them or exit the Extras menu.
*   Settings are preserved across console resets and power cycles.
*   **Note:** Resetting Save Data (Erase All Data) will reset these settings to their default (OFF) values.
