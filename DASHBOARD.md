# Submodule Dashboard

This dashboard lists all active submodules, their paths, versions, and status. Use this to track dependencies.

## Active Submodules

| Name | Path | Version/Commit | Status | Description |
| :--- | :--- | :--- | :--- | :--- |
| **doxygen-awesome-css** | `doxygen-awesome-css` | `1f36200` (v2.4.1) | Active | Modern CSS styling for Doxygen documentation. |
| **asm-differ** | `tools/asm-differ` | `4eb23bc` (heads/main) | Active | Tool for comparing assembly output during decompilation. |
| **fast64** | `tools/blender/fast64` | `dd418d1` (v2.5.1) | Active | Blender plugin for N64 display list generation. |
| **decomp-permuter** | `tools/decomp-permuter` | `ec2efee` (heads/main) | Active | Tool for randomizing C code to match assembly. |
| **torch** | `tools/torch` | `3dde9e6` (heads/main) | Active | Decompilation support tool. |

*Note: `bobcoin` has been removed.*

## Maintenance Instructions

*   **Update:** To update a submodule, run `git submodule update --remote [path]`.
*   **Sync:** Ensure local submodules are synced with `git submodule sync`.
*   **Documentation:** When updating a submodule version, update this dashboard.
