# TODO List

## Immediate Priorities
- [ ] **OpenGL Uploads:** Write the actual `glBufferSubData` and `glTexImage2D` commands in `platform_renderer.c` using the extracted `PCVertex` array and `PCTextureState`.
- [ ] **SDL Window Context:** Fully implement `PC_WindowInit` with SDL2 to generate an actual visible window on the PC so the OpenGL commands have a context to execute against.

## Short Term
- [ ] **PC Port:** Full SDL/OpenGL Backend (Renderer translation).
- [ ] **Online Play:** Abstract N64 controller inputs over ENet sockets.

## Long Term / Tech Debt
- [ ] **Lua API:** Expose `Player` structs to Lua scripts loaded at runtime (PC Port only).
- [ ] **Build System:** Improve `Makefile` dependency tracking for header changes.
