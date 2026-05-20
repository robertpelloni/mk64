# Project Memory & Observations

## Codebase Patterns
- Functions prefixed with `func_800` are typically unnamed routines translated directly from MIPS assembly. Finding matching calls and renaming them is a core ongoing task.
- Fixed-point matrix conversions (e.g. within `src/racing/math_util.c`) are heavily susceptible to precision-loss crashes (PU crashes) when converting N64 float semantics to integers.
- The global build config relies heavily on `tools/` (specifically `torch` and `decomp-permuter`) to format the assets JSON and align the linker (`mk64.ld`).

## Recent Audits
- The `bobcoin` submodule was completely removed to reflect the cleanup phase of the monorepo sync. All `.gitmodule` linkages and reference documentation have been purged.
- Several audio routines in `src/menus.c` and `src/audio/external.c` (`func_800CA388`) were recently mapped to `fade_all_channel_volume_scale`.
