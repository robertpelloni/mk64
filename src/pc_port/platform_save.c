#include <ultra64.h>
#include <macros.h>
#include "main.h"
#include "save.h"

// In a real PC port, these use <stdio.h> calls.
// The macro PC_BUILD should be defined in the PC target Makefile.

#ifdef PC_BUILD
#include <stdio.h>
#endif

typedef struct {
    u32 magic;
    u32 version;
    u32 dataSize;
} PCSaveHeader;

// Mock file system state (for N64 build abstraction verification)
static u8 sMockFilesystem[16][0x2000]; // 16 files, 8KB each
static s32 sMockFileCount = 0;

s32 PC_SaveFile(char* filename, void* data, s32 size) {
#ifdef PC_BUILD
    FILE* f = fopen(filename, "wb");
    if (!f) return 0;
    size_t written = fwrite(data, 1, size, f);
    fclose(f);
    return (written == size);
#else
    // For the N64 environment, we just "pretend" success
    // or store to our mock buffer to verify logic
    return 1; // Success
#endif
}

s32 PC_LoadFile(char* filename, void* dest, s32 maxSize) {
#ifdef PC_BUILD
    FILE* f = fopen(filename, "rb");
    if (!f) return 0;
    size_t bytesRead = fread(dest, 1, maxSize, f);
    fclose(f);
    return (bytesRead > 0);
#else
    return 1; // Success
#endif
}

// Replaces Controller Pak "Repair" / "Check"
s32 PC_CheckSaveSystem(void) {
    return 1; // Always good on PC
}

// Save a "Practice Ghost" (Snapshot of current player history)
void PC_SavePracticeGhost(Player* player) {
    // Dump player's position history, inputs, etc.
    // Logic similar to save_ghost in save.c but bypassing validation
    // Construct a ghost header...
    // Write to "practice_ghost.bin"
}
