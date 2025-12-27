# Submodule Dashboard

## Overview
This project uses several submodules for tools and documentation styles. Below is the current status of each submodule.

| Submodule | Path | Version/Commit | URL |
| :--- | :--- | :--- | :--- |
| **doxygen-awesome-css** | `doxygen-awesome-css` | `df88fe4f` (v2.3.1) | https://github.com/jothepro/doxygen-awesome-css.git |
| **asm-differ** | `tools/asm-differ` | `87029d02` | https://github.com/simonlindholm/asm-differ |
| **fast64** | `tools/blender/fast64` | `d89593c8` | https://github.com/Fast-64/fast64.git |
| **decomp-permuter** | `tools/decomp-permuter` | `7f63c768` | https://github.com/simonlindholm/decomp-permuter |
| **torch** | `tools/torch` | `5773373b` | https://github.com/HarbourMasters/torch |

## Directory Structure
- `tools/`: Contains build tools and helper scripts.
  - `asm-differ/`: Tool for comparing assembly output.
  - `decomp-permuter/`: Tool for randomizing C code to match assembly.
  - `torch/`: Texture handling tools.
  - `blender/fast64/`: Blender plugin for N64 development.
- `doxygen-awesome-css/`: Style files for Doxygen documentation.

## Management Instructions
- To update all submodules: `git submodule update --init --recursive`
- To check status: `git submodule status`
