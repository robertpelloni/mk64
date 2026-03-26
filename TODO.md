# TODO List

## Immediate Priorities
- [ ] **VBO and Element Buffer Translation:** Implement the logic inside `case G_VTX:` to extract vertices from RAM (via `w1`) and push them into an OpenGL Vertex Buffer Object. Ensure N64 `s` and `t` texture coordinates are correctly scaled.
- [ ] **Texture Format Decoding:** Implement the logic in `case G_SETTIMG:` and `case G_LOADBLOCK:` to decode the N64's CI4/CI8/RGBA16/RGBA32 raw bytes into `glTexture2D` formats.

## Short Term
- [ ] **PC Port:** Full SDL/OpenGL Backend (Renderer translation).
- [ ] **Online Play:** Abstract N64 controller inputs over ENet sockets.

## Long Term / Tech Debt
- [ ] **Lua API:** Expose `Player` structs to Lua scripts loaded at runtime (PC Port only).
- [ ] **Build System:** Improve `Makefile` dependency tracking for header changes.
