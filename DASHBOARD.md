# Submodule Dashboard

This dashboard lists all active submodules, their paths, versions, and status. Use this to track dependencies.

## Active Submodules

| Name | Path | Version/Commit | Status | Description |
| :--- | :--- | :--- | :--- | :--- |
| **doxygen-awesome-css** | `doxygen-awesome-css` | `v2.3.0` (approx) | Active | Modern CSS styling for Doxygen documentation. |
| **asm-differ** | `tools/asm-differ` | `HEAD` (main) | Active | Tool for comparing assembly output during decompilation. |
| **fast64** | `tools/blender/fast64` | `v2.5.1` | Active | Blender plugin for N64 display list generation. |
| **decomp-permuter** | `tools/decomp-permuter` | `HEAD` (main) | Active | Tool for randomizing C code to match assembly. |
| **torch** | `tools/torch` | `HEAD` (main) | Active | Decompilation support tool. |

*Note: `bobcoin` has been removed.*

## Maintenance Instructions

*   **Update:** To update a submodule, run `git submodule update --remote [path]`.
*   **Sync:** Ensure local submodules are synced with `git submodule sync`.
*   **Documentation:** When updating a submodule version, update this dashboard.
