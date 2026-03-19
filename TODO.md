# TODO List

## Immediate Priorities
- [ ] **PC Port Build Pipeline:** Create a `Makefile.pc` to compile the current C codebase using GCC/Clang targeting a modern OS, defining the `PC_BUILD` macro.
- [ ] **SDL Renderer:** Begin translating `gSPDisplayList` and N64 ABI commands into an OpenGL/Vulkan rendering loop within `platform_window.c`.

## Short Term
- [ ] **PC Port:** Full SDL/OpenGL Backend (Renderer translation).
- [ ] **Online Play:** Abstract N64 controller inputs over ENet sockets.

## Long Term / Tech Debt
- [ ] **Lua API:** Expose `Player` structs to Lua scripts loaded at runtime (PC Port only).
- [ ] **Build System:** Improve `Makefile` dependency tracking for header changes.
