# Submodule Dashboard

## Overview
This dashboard tracks the status of all submodules in the project. The repository uses several external tools and libraries managed as git submodules.

## Current Submodule Status
| Submodule Path | Version (Commit) | Branch | Status |
| :--- | :--- | :--- | :--- |
| `doxygen-awesome-css` | `1f36200` (v2.4.1) | `main` | Up to date |
| `tools/asm-differ` | `4eb23bc` | `main` | Up to date |
| `tools/blender/fast64` | `67552ca` | `main` | Up to date |
| `tools/decomp-permuter` | `ec2efee` | `main` | Up to date |
| `tools/torch` | `73f7a4a` | `main` | Up to date |

## Project Directory Structure
The following tree outlines the project layout and the location of each submodule:

```
.
├── AGENTS.md               # Instructions for AI agents
├── CHANGELOG.md            # Version history
├── DASHBOARD.md            # This file
├── HANDOFF.md              # Project handoff notes
├── PROJECT_STRUCTURE.md    # Detailed architecture documentation
├── VERSION                 # Current version string
├── include/                # Header files
├── src/                    # Source code
├── tools/                  # Build tools and utilities
│   ├── asm-differ/         # [Submodule] Diff tool for decompilation
│   ├── blender/fast64/     # [Submodule] Fast64 Blender plugin
│   ├── decomp-permuter/    # [Submodule] Code permuter for matching
│   └── torch/              # [Submodule] Asset extraction tool
└── doxygen-awesome-css/    # [Submodule] Doxygen theme
```

## Update Protocol
To update these submodules to their latest upstream versions:
```bash
git submodule update --remote --merge
```

*Last Updated: 2024-05-23 (Build 1.0.2)*
