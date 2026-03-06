#include <ultra64.h>
#include <macros.h>
#include "save_extended.h"
#include "save.h"
#include "main.h"
#include "save_data.h"

// Helper macros for bit access
#define BIT(x) (1 << (x))
#define CHECK_BIT(var, pos) ((var) & BIT(pos))
#define SET_BIT(var, pos) ((var) |= BIT(pos))
#define CLEAR_BIT(var, pos) ((var) &= ~BIT(pos))

// Checksum[0] Map:
// Bit 7: Resource Meters
// Bit 6: Music
// Bit 5: SFX
// Bit 4: Input Display
// Bits 0-3: Deadzone

// UnknownBytes[0] Map:
// Bit 0: Speedometer
// Bit 1: Level Reset
// Bits 2-6: Item Option (5 bits)
// Bit 7: Lap Skip

// UnknownBytes[1] Map:
// Bit 0: Timer Freeze
// Bit 1: Custom Assets (Modding)

void SaveExtended_Init(void) {
    // Nothing special needed, logic handled in getters/setters
}

void SaveExtended_Save(void) {
    // Checksum[0] packing
    u8 checksum0 = 0;
    if (gEnableResourceMeters) checksum0 |= BIT(7);
    if (gToggleMusic) checksum0 |= BIT(6);
    if (gToggleSFX) checksum0 |= BIT(5);
    if (gEnableInputDisplay) checksum0 |= BIT(4);
    checksum0 |= (gStickDeadzone & 0xF);

    gSaveData.main.checksum[0] = checksum0;

    // UnknownBytes packing
    u8 unknown0 = 0;
    if (gEnableSpeedometer) unknown0 |= BIT(0);
    if (gEnableLevelReset) unknown0 |= BIT(1);
    unknown0 |= (gPracticeItemOption & 0x1F) << 2; // Bits 2-6
    if (gEnableLapSkip) unknown0 |= BIT(7);

    gSaveData.onlyBestTimeTrialRecords[0].unknownBytes[0] = unknown0;

    // UnknownBytes[1] packing
    u8 unknown1 = 0;
    if (gPracticeTimerFreeze) unknown1 |= BIT(0);
    if (gEnableCustomAssets) unknown1 |= BIT(1);
    gSaveData.onlyBestTimeTrialRecords[0].unknownBytes[1] = unknown1;

    // Commit
    // Note: We depend on save.c functions which might not be exposed.
    // Ideally we'd call write_save_data... here, but for now we rely on the caller (menus.c)
    // to trigger the actual write via save_options().
    // Actually, save_options() in save.c does the writing. We should call SaveExtended_Save() INSIDE save_options().
}

// Getters
s32 SaveExtended_GetSpeedometer(void) {
    return (gSaveData.onlyBestTimeTrialRecords[0].unknownBytes[0] >> 0) & 1;
}

s32 SaveExtended_GetLevelReset(void) {
    return (gSaveData.onlyBestTimeTrialRecords[0].unknownBytes[0] >> 1) & 1;
}

s32 SaveExtended_GetInputDisplay(void) {
    return (gSaveData.main.checksum[0] >> 4) & 1;
}

s32 SaveExtended_GetMusic(void) {
    return (gSaveData.main.checksum[0] >> 6) & 1;
}

s32 SaveExtended_GetSFX(void) {
    return (gSaveData.main.checksum[0] >> 5) & 1;
}

s32 SaveExtended_GetDeadzone(void) {
    return gSaveData.main.checksum[0] & 0xF;
}

s32 SaveExtended_GetResourceMeters(void) {
    return (gSaveData.main.checksum[0] >> 7) & 1;
}

s32 SaveExtended_GetItemOption(void) {
    return (gSaveData.onlyBestTimeTrialRecords[0].unknownBytes[0] >> 2) & 0x1F;
}

s32 SaveExtended_GetLapSkip(void) {
    return (gSaveData.onlyBestTimeTrialRecords[0].unknownBytes[0] >> 7) & 1;
}

s32 SaveExtended_GetTimerFreeze(void) {
    return (gSaveData.onlyBestTimeTrialRecords[0].unknownBytes[1] >> 0) & 1;
}

s32 SaveExtended_GetCustomAssets(void) {
    return (gSaveData.onlyBestTimeTrialRecords[0].unknownBytes[1] >> 1) & 1;
}

// Setters (Updates globals, persistence happens on Save)
void SaveExtended_SetSpeedometer(s32 value) {
    gEnableSpeedometer = value;
}

void SaveExtended_SetLevelReset(s32 value) {
    gEnableLevelReset = value;
}

void SaveExtended_SetInputDisplay(s32 value) {
    gEnableInputDisplay = value;
}

void SaveExtended_SetMusic(s32 value) {
    gToggleMusic = value;
}

void SaveExtended_SetSFX(s32 value) {
    gToggleSFX = value;
}

void SaveExtended_SetDeadzone(s32 value) {
    if (value > 15) value = 15;
    gStickDeadzone = value;
}

void SaveExtended_SetResourceMeters(s32 value) {
    gEnableResourceMeters = value;
}

void SaveExtended_SetItemOption(s32 value) {
    gPracticeItemOption = value;
}

void SaveExtended_SetLapSkip(s32 value) {
    gEnableLapSkip = value;
}

void SaveExtended_SetTimerFreeze(s32 value) {
    gPracticeTimerFreeze = value;
}

void SaveExtended_SetCustomAssets(s32 value) {
    gEnableCustomAssets = value;
}
