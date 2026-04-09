# TODO List

## Immediate Priorities
- [ ] **PC Input Abstraction:** Flesh out the `PC_ReadInput` stub in `platform_input.c`. Poll `SDL_GameController` and `SDL_Keyboard` to map native PC inputs to the N64 `OSContPad` bitmasks.
- [ ] **PC Audio Backend:** Integrate `SDL_Audio` callback logic in `platform_audio.c`. Investigate how the decompiled `audio/external.c` pushes synthesized 16-bit PCM buffers to `osAiSetNextBuffer` and route that payload to the SDL queue.

## Short Term
- [ ] **PC Port:** Full SDL/OpenGL Backend (Renderer translation).
- [ ] **Online Play:** Abstract N64 controller inputs over ENet sockets.

## Long Term / Tech Debt
- [ ] **Lua API:** Expose `Player` structs to Lua scripts loaded at runtime (PC Port only).
- [ ] **Build System:** Improve `Makefile` dependency tracking for header changes.
