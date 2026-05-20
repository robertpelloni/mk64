# AI Agent Instructions (MK64)

> **CRITICAL: THIS MODULE IS PART OF THE OMNI-WORKSPACE.**

ALL AI AGENTS OPERATING IN THIS REPOSITORY MUST READ AND FOLLOW THE UNIVERSAL PROTOCOLS DEFINED AT:
`docs/UNIVERSAL_LLM_INSTRUCTIONS.md`.

## Local Context (MK64)
Refer to the parent monorepo's `DASHBOARD.md` for project-wide structure.
This repository handles the decompilation, porting, and AI-enhancement of Mario Kart 64.

Active Tasks:
- Label unknown C functions (e.g., `func_800...`).
- Implement Rust integrations for physics.
- Construct WASM cross-compilation configurations.

## System Map
### Decompilation
- **Source:** `src/` - Original C source.
- **Assembly:** `asm/` - Handwritten/unmatched assembly.
- **Assets:** `assets/` - Extracted rom data.
### Submodules
- **fast64:** Blender plugin for N64 layout editing.
- **torch:** N64 toolchain asset management.
