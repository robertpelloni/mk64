#ifndef SAVE_EXTENDED_H
#define SAVE_EXTENDED_H

#include <ultra64.h>

// Extended options are stored in onlyBestTimeTrialRecords[0].unknownBytes[0]
// and checksum[0] of the main save struct.

void SaveExtended_Init(void);
void SaveExtended_Save(void);

// Getters
s32 SaveExtended_GetSpeedometer(void);
s32 SaveExtended_GetLevelReset(void);
s32 SaveExtended_GetInputDisplay(void);
s32 SaveExtended_GetMusic(void);
s32 SaveExtended_GetSFX(void);
s32 SaveExtended_GetDeadzone(void);
s32 SaveExtended_GetResourceMeters(void);

// Setters
void SaveExtended_SetSpeedometer(s32 value);
void SaveExtended_SetLevelReset(s32 value);
void SaveExtended_SetInputDisplay(s32 value);
void SaveExtended_SetMusic(s32 value);
void SaveExtended_SetSFX(s32 value);
void SaveExtended_SetDeadzone(s32 value);
void SaveExtended_SetResourceMeters(s32 value);

#endif
