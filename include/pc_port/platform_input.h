#ifndef PLATFORM_INPUT_H
#define PLATFORM_INPUT_H

#include <ultra64.h>

/**
 * Initializes the PC Input backend (e.g., SDL_GameController).
 * In the N64 build, this simply returns success immediately.
 */
void PC_InputInit(void);

/**
 * Reads controller state from the PC backend and maps it directly
 * into the game's OSContPad structure.
 * On N64 hardware, this is a no-op, relying on osContGetReadData.
 */
void PC_ReadInput(OSContPad* pads);

/**
 * Cleans up the PC Input backend resources upon shutdown.
 */
void PC_InputShutdown(void);

#endif // PLATFORM_INPUT_H
