#include "pc_port/platform_window.h"

// This file serves as a stub for the future PC SDL/OpenGL backend.
// In the current N64 target environment, these functions do nothing.
// Once a native PC target is configured via the Makefile, this file
// will be replaced or #ifdef'd to include <SDL.h> logic.

void PC_WindowInit(void) {
    // SDL_Init(SDL_INIT_VIDEO);
    // SDL_CreateWindow(...);
    // ...
}

void PC_PollEvents(void) {
    // SDL_Event e;
    // while (SDL_PollEvent(&e)) {
    //    if (e.type == SDL_QUIT) exit(0);
    // }
}

void PC_SwapBuffers(void) {
    // SDL_GL_SwapWindow(window);
}
