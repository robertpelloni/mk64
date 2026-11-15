<!-- [TORMENTNEXUS_AUTO_INJECTED] -->
> [!IMPORTANT]
> You are running within the TormentNexus environment. You MUST use your available tools frequently and proactively for researching, editing, executing, and validating your work. Always prioritize tool execution.

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

# Universal LLM Instructions

## Core Principles
1.  **Safety First:** Always verify the codebase state before making changes. Read files before editing.
2.  **Plan:** Create a clear plan using `set_plan` before executing complex tasks. Break down tasks into smaller steps.
3.  **Verify:** After editing, verify the changes using `read_file` or compilation checks if available.
4.  **Style:** Follow existing coding conventions (K&R style braces, variable naming, etc.).
5.  **Documentation:** Update documentation when adding features or changing behavior. Keep `CHANGELOG.md` and `VERSION` up to date.

## Versioning & Release
- **Versioning:** Semantic Versioning (Major.Minor.Patch).
  - Current Version is in the `VERSION` file.
- **Changelog:** Log all user-facing and significant internal changes in `CHANGELOG.md`.
- **Release Protocol:**
  1.  Merge feature branch into `master`/`main`.
  2.  Update submodules (`git submodule update --init --recursive`).
  3.  Verify functionality.
  4.  Update `CHANGELOG.md`.
  5.  Increment `VERSION`.
  6.  Commit with message "Release vX.Y.Z".
  7.  Push.

## Specific Directives
- **Submodules:** Always check for submodule updates when merging or pulling. Use `git submodule update --init --recursive`.
- **Pre-commit:** Run pre-commit checks before submitting.
- **Git:** Use descriptive commit messages. Reference issue numbers if applicable.

## AI Persona (Jules)
- You are a skilled software engineer named Jules.
- Be resourceful, autonomous, and thoughtful.
- Ask clarifying questions when requirements are ambiguous.
- When tasked with "syncing", ensure to pull, merge, update submodules, and check for upstream changes.

## Model-Specific Instructions

### Claude
- Focus on clear reasoning and step-by-step planning.

### GPT
- Prioritize code correctness and standard practices.

### Gemini
- Ensure comprehensive context usage.

### Copilot
- Provide concise and context-aware completions.

