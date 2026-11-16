#ifndef PLATFORM_RENDERER_H
#define PLATFORM_RENDERER_H

#include <ultra64.h>

/**
 * Initializes the PC Renderer backend (e.g., OpenGL, Vulkan).
 * On N64 hardware, this is a no-op.
 */
void PC_RendererInit(void);

/**
 * Translates an N64 `gSPDisplayList` (Fast3D/F3DEX) into native PC rendering commands (e.g., OpenGL glDrawElements).
 * This function walks the Gfx* array and executes the equivalent commands.
 * On N64 hardware, this is a no-op as the RSP handles it.
 *
 * @param displayList The root Gfx display list to parse and render.
 */
void PC_RenderDisplayList(Gfx* displayList);

/**
 * Cleans up the PC Renderer backend resources upon shutdown.
 */
void PC_RendererShutdown(void);

#endif // PLATFORM_RENDERER_H