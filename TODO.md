# TODO List

## Immediate Priorities
- [ ] **SDL Window Context:** Fully implement `PC_WindowInit` with SDL2 (`SDL_CreateWindow`, `SDL_GL_CreateContext`) to generate an actual visible window on the PC so the OpenGL commands have a context to execute against.
- [ ] **GLEW Integration:** Uncomment and link GLEW in the `Makefile.pc` to activate the `glBufferSubData`, `glUseProgram`, and `glTexImage2D` calls located inside the `platform_renderer.c` switch statements.

## Short Term
- [ ] **PC Port:** Full SDL/OpenGL Backend (Renderer translation).
- [ ] **Online Play:** Abstract N64 controller inputs over ENet sockets.

## Long Term / Tech Debt
- [ ] **Lua API:** Expose `Player` structs to Lua scripts loaded at runtime (PC Port only).
- [ ] **Build System:** Improve `Makefile` dependency tracking for header changes.
