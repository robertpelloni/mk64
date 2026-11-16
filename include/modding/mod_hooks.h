#ifndef MOD_HOOKS_H
#define MOD_HOOKS_H

#include <ultra64.h>
#include <mk64.h>

// Mod Event Types
typedef enum {
    MOD_EVENT_GAME_INIT,
    MOD_EVENT_RACE_START,
    MOD_EVENT_GAME_TICK,
    MOD_EVENT_LAP_COMPLETE,
    MOD_EVENT_ITEM_USE,
    MOD_EVENT_RENDER_FRAME
} ModEventType;

// Hook Function Prototypes
void Mod_Init(void);
void Mod_OnGameTick(void);
void Mod_OnRaceStart(void);
void Mod_OnLapComplete(s32 playerId, s32 lap);
void Mod_OnItemUse(s32 playerId, s32 itemType);

#endif
