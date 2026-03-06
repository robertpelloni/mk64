#include "pc_port/platform_audio.h"

// This file serves as a stub for the future PC SDL Audio backend.
// In the current N64 target environment, these functions do nothing.
// Once a native PC target is configured via the Makefile, this file
// will be replaced or #ifdef'd to include <SDL_audio.h> logic, which
// will receive mixed 16-bit PCM samples from the decompiled audio engine.

void PC_AudioInit(void) {
    // SDL_AudioSpec desired, obtained;
    // desired.freq = 32000; // Standard N64 mixing freq
    // desired.format = AUDIO_S16SYS;
    // desired.channels = 2; // Stereo
    // desired.samples = 512;
    // desired.callback = PC_AudioCallback; // Custom callback to pull from synth
    // SDL_OpenAudio(&desired, &obtained);
    // SDL_PauseAudio(0);
}

void PC_AudioProcess(void) {
    // In a push-based PC audio system (like some modern backends),
    // we would queue synthesized audio buffers here.
    // e.g., SDL_QueueAudio(dev, synthesized_buffer, size);
}

void PC_AudioShutdown(void) {
    // SDL_CloseAudio();
}
