# TODO List

## Immediate Priorities
- [ ] **SDL Renderer Implementation:** Build out the `switch` statement in `PC_RenderDisplayList` within `platform_renderer.c`. Translate macros like `G_VTX` and `G_TRI1` into intermediate Vertex Buffer Objects (VBOs) for OpenGL 3.3+.
- [ ] **Shader Generation:** Create a basic vertex/fragment shader pair in `platform_renderer.c` capable of handling N64 texture mapping (`G_SETTIMG`, `G_SETTILE`) and vertex coloring.

## Short Term
- [ ] **PC Port:** Full SDL/OpenGL Backend (Renderer translation).
- [ ] **Online Play:** Abstract N64 controller inputs over ENet sockets.

## Long Term / Tech Debt
- [ ] **Lua API:** Expose `Player` structs to Lua scripts loaded at runtime (PC Port only).
- [ ] **Build System:** Improve `Makefile` dependency tracking for header changes.
