#include "pc_port/platform_window.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef PC_BUILD
#include <SDL2/SDL.h>
#include <GL/glew.h>

static SDL_Window* sWindow = NULL;
static SDL_GLContext sGLContext;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#endif

void PC_WindowInit(void) {
#ifdef PC_BUILD
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }

    // Request OpenGL 3.3 Core Profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    sWindow = SDL_CreateWindow(
        "Mario Kart 64 (PC Port)",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!sWindow) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    sGLContext = SDL_GL_CreateContext(sWindow);
    if (!sGLContext) {
        fprintf(stderr, "SDL_GL_CreateContext Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(sWindow);
        SDL_Quit();
        exit(1);
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        fprintf(stderr, "GLEW Init Error: %s\n", glewGetErrorString(glewError));
        exit(1);
    }

    // Enable VSync
    SDL_GL_SetSwapInterval(1);

    // Basic GL setup
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
}

void PC_PollEvents(void) {
#ifdef PC_BUILD
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            // Clean shutdown
            SDL_GL_DeleteContext(sGLContext);
            SDL_DestroyWindow(sWindow);
            SDL_Quit();
            exit(0);
        }
        // In the future: pass keyboard/mouse events to platform_input.c
    }
#endif
}

void PC_SwapBuffers(void) {
#ifdef PC_BUILD
    if (sWindow) {
        SDL_GL_SwapWindow(sWindow);

        // Clear for next frame
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
#endif
}