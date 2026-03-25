# TODO List

## Immediate Priorities
- [ ] **Filter N64 Assembly:** Update `Makefile.pc` to explicitly filter out `.s` assembly files and specific N64 OS/RSP hardware source files that will cause compilation errors on a native PC target (e.g., `src/os/osSpTaskYield.c`).
- [ ] **SDL Renderer:** Begin translating `gSPDisplayList` and N64 ABI commands into an OpenGL/Vulkan rendering loop within `platform_window.c`.

## Short Term
- [ ] **PC Port:** Full SDL/OpenGL Backend (Renderer translation).
- [ ] **Online Play:** Abstract N64 controller inputs over ENet sockets.

## Long Term / Tech Debt
- [ ] **Lua API:** Expose `Player` structs to Lua scripts loaded at runtime (PC Port only).
- [ ] **Build System:** Improve `Makefile` dependency tracking for header changes.
