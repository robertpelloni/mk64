# TODO List

## Immediate Priorities
- [ ] **PC Input Abstraction:** Create `src/pc_port/platform_input.c` for SDL controller support (stubbed for N64).
- [ ] **PC Filesystem Abstraction:** Fully implement `PC_SaveFile` and `PC_LoadFile` in `platform_save.c` using standard C `<stdio.h>` when built for PC.

## Short Term
- [ ] **PC Port:** Full SDL/OpenGL Backend (Renderer translation).
- [ ] **Online Play:** Abstract N64 controller inputs over ENet sockets.

## Long Term / Tech Debt
- [ ] **Lua API:** Expose `Player` structs to Lua scripts loaded at runtime (PC Port only).
- [ ] **Build System:** Improve `Makefile` dependency tracking for header changes.
