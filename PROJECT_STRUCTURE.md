# Project Structure

## Root Directory
- `src/`: Source code (C files).
- `include/`: Header files.
- `asm/`: Assembly code (MIPS).
- `assets/`: Game assets (textures, models).
- `courses/`: Course data.
- `tools/`: Build tools.

## Key Source Files
- `src/main.c`: Main game loop, VSync, gamestate management.
- `src/menus.c`: Menu state handling.
- `src/save.c`: Save data management.
- `src/racing/`: Race logic, physics, rendering.
  - `src/racing/race_logic.c`: General race management.
  - `src/racing/skybox_and_splitscreen.c`: Viewport and projection settings.
  - `src/racing/update_objects.c`: Object update loop.
- `src/cpu_vehicles_camera_path/`: AI and camera logic.
  - `src/cpu_vehicles_camera_path.c`: AI pathfinding.
  - `src/cpu_vehicles_camera_path/cpu_speed_control.inc.c`: AI speed regulation.
- `src/math_util_2.c`: HUD projection matrix calculation.
- `src/code_80086E70.c`: Object visibility/culling logic.
