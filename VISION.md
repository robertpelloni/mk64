# Project Vision

## Overview
The ultimate goal of this project is to create the definitive, most comprehensive, robust, and functional version of Mario Kart 64. It is built upon the `n64decomp/mk64` decompilation and is rapidly expanding into a highly configurable, moddable, and feature-rich platform.

## Core Tenets

### 1. Authenticity & Preservation
*   The core gameplay logic, physics, and feel must remain identical to the original N64 release unless explicitly modified by the user via configuration.
*   The project must serve as a learning resource, documenting the intricacies of the original game engine.

### 2. First-Class Modernization
*   **Visuals:** Native 60 FPS rendering (decoupled from game logic) and true 16:9 Widescreen support (with FOV correction and HUD pillarboxing).
*   **Usability:** Fast boot, instant level resets, and streamlined menus.
*   **Controls:** Deadzone configuration and modern input handling.

### 3. Unprecedented Practice Tools
*   Designed for speedrunners and casual players alike.
*   Features include: Robust Save States (Position, Velocity, Items, RNG, Lap Count), Timer Freezing, Lap Skipping, Item Forcing, Input Display, Speedometer, and a Free-Fly Camera.

### 4. Deep Configurability (The Extras Menu)
*   Every single implemented feature must be accessible, toggleable, and documented within the in-game UI (The "Extras" and "Practice" menus).
*   Settings must persist safely (abstracted PC file I/O or unused EEPROM bytes).
*   No hidden features; everything has a tooltip and manual entry.

### 5. PC Port & Modding Architecture
*   **Platform Abstraction:** Moving away from N64 hardware dependencies (`osPfs`, Controller Paks) to standard PC File I/O (`src/pc_port/`).
*   **Mod Hooks:** Establishing an event-driven architecture (`OnGameTick`, `OnRaceStart`, `OnLapComplete`) for external scripts.
*   **Asset Replacement:** Building a registry (`src/modding/mod_assets.c`) to load external textures, models, and audio dynamically at runtime.
*   **Future Goal:** Full SDL/OpenGL backend and potential ENet integration for online multiplayer.

## Documentation Standard
The project must be meticulously documented. This includes `ROADMAP.md`, `TODO.md`, `CHANGELOG.md`, `MANUAL.md`, a unified `LLM_INSTRUCTIONS.md`, and extensive Doxygen code comments explaining the *why* and *how* of every modification.