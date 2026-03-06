#ifndef PLATFORM_AUDIO_H
#define PLATFORM_AUDIO_H

#include <ultra64.h>

/**
 * Initializes the PC Audio backend (e.g., SDL_Audio).
 * In the N64 build, this simply returns success immediately.
 */
void PC_AudioInit(void);

/**
 * Processes audio streams, filling the SDL audio buffer with mixed samples.
 * On N64 hardware, the RSP handles this via ABI commands, so this is a no-op.
 */
void PC_AudioProcess(void);

/**
 * Cleans up the PC Audio backend resources upon shutdown.
 */
void PC_AudioShutdown(void);

#endif // PLATFORM_AUDIO_H
