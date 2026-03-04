#ifndef PLATFORM_WINDOW_H
#define PLATFORM_WINDOW_H

#include <ultra64.h>

/**
 * Initializes the PC window and OpenGL/Vulkan rendering context.
 * In the N64 build, this simply returns success immediately.
 */
void PC_WindowInit(void);

/**
 * Handles OS-level events like closing the window or minimizing.
 */
void PC_PollEvents(void);

/**
 * Swaps the framebuffers and presents the rendered frame to the screen.
 */
void PC_SwapBuffers(void);

#endif // PLATFORM_WINDOW_H
