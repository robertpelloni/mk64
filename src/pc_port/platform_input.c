#include "pc_port/platform_input.h"

// This file serves as a stub for the future PC SDL Controller backend.
// In the current N64 target environment, these functions do nothing.
// Once a native PC target is configured via the Makefile, this file
// will be replaced or #ifdef'd to include <SDL_gamecontroller.h> logic.

void PC_InputInit(void) {
    // SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER);
    // Scan and open SDL controllers...
}

void PC_ReadInput(OSContPad* pads) {
    // Poll SDL state and translate to N64 OSContPad format:
    // pads[0].button = 0;
    // if (SDL_GameControllerGetButton(controller1, SDL_CONTROLLER_BUTTON_A)) {
    //     pads[0].button |= A_BUTTON;
    // }
    // ...
    // pads[0].stick_x = SDL_GameControllerGetAxis(controller1, SDL_CONTROLLER_AXIS_LEFTX) >> 8;
    // pads[0].stick_y = -(SDL_GameControllerGetAxis(controller1, SDL_CONTROLLER_AXIS_LEFTY) >> 8);
}

void PC_InputShutdown(void) {
    // Close SDL controllers
    // SDL_QuitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER);
}
