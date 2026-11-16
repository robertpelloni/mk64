#ifndef AUDIO_EXTERNAL_H
#define AUDIO_EXTERNAL_H

#include <common_structs.h>
#include "camera.h"

#define ADSR_STATE_DISABLED 0
#define ADSR_STATE_INITIAL 1
#define ADSR_STATE_START_LOOP 2
#define ADSR_STATE_LOOP 3
#define ADSR_STATE_FADE 4
#define ADSR_STATE_HANG 5
#define ADSR_STATE_DECAY 6
#define ADSR_STATE_RELEASE 7
#define ADSR_STATE_SUSTAIN 8

#define ADSR_ACTION_RELEASE 0x10
#define ADSR_ACTION_DECAY 0x20
#define ADSR_ACTION_HANG 0x40

#define ADSR_DISABLE 0
#define ADSR_HANG -1
#define ADSR_GOTO -2
#define ADSR_RESTART -3

// Sequence arguments, passed to seq_player_play_sequence. seqId may be bit-OR'ed with
// SEQ_VARIATION; this will load the same sequence, but set a variation
// bit which may be read by the sequence script.
#define SEQUENCE_ARGS(priority, seqId) ((priority << 8) | seqId)

#define SOUND_MODE_STEREO 0
#define SOUND_MODE_MONO 3
#define SOUND_MODE_HEADSET 1

#define SEQ_PLAYER_LEVEL 0 // Level background music
#define SEQ_PLAYER_ENV 1   // Misc music like the puzzle jingle
#define SEQ_PLAYER_SFX 2   // Sound effects

#define SOUND_BANK_UNK0 0
#define SOUND_BANK_UNK1 1
#define SOUND_BANK_UNK2 2
#define SOUND_BANK_UNK3 3
#define SOUND_BANK_UNK4 4
#define SOUND_BANK_UNK5 5
#define SOUND_BANK_COUNT 6

// Almost certainly an expanded version of struct Sound from SM64
struct Sound {
    /* 0x00 */ u32 soundBits;
    /* 0x04 */ Vec3f* position;
    /* 0x08 */ u8 cameraId; // playerId? some indicator of "who" the sound is desitned for
    /* 0x09 */              // u8  compilerPadding0[3];
    /* 0x0C */ f32* unk0C;
    /* 0x10 */ f32* unk10;
    /* 0x14 */ s8* unk14;
}; // size = 0x18

struct AudioCharacterState {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ s8 unk_14;
    /* 0x15 */ // s8 comilerPadding[3];
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
}; // size = 0x3C

// I'm speculating that this struct has something to do with
// the doppler effect that happens to some sounds
struct Unk_8018EFD8 {
    // Pointers to a position
    /* 0x00 */ f32* posX;
    /* 0x04 */ f32* posY;
    /* 0x08 */ f32* posZ;
    // Pointers to a velocity
    /* 0x0C */ f32* velX;
    /* 0x10 */ f32* velY;
    /* 0x14 */ f32* velZ;
    /* 0x18 */ Vec3f unk18;
    /* 0x24 */ f32* unk24;  // Some type of multiplier/scalar
                            // Indexes in gSoundSources, not really sure what they're for though
    /* 0x28 */ u8 cameraId; // playerId? some indicator of "who" the sound is desitned for
    /* 0x29 */ u8 prev;
    /* 0x2A */ u8 next;
    /* 0x2B */ // u8 compilerPadding00;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ // u8 compilerPadding01[3];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ u32 soundBits;
}; // size = 0x3C

// This is almost certainly an expanded version of SoundCharacteristics from SM64
struct SoundCharacteristics {
    // These f32 pointers appear to point to the `Vec3f unk18` members in a struct Unk_8018EFD8
    /* 0x00 */ Vec3f* unk00;
    /* 0x04 */ f32* unk04;
    /* 0x08 */ f32* unk08;
    /* 0x0C */ u8 cameraId; // playerId? some indicator of "who" the sound is desitned for
    /* 0x0D */              // u8 compilerPadding0[3];
    /* 0x10 */ f32* unk10;
    /* 0x14 */ f32* unk14;
    /* 0x18 */ s8* unk18;
    /* 0x1C */ f32 distance; // XZ distance from the camera
    /* 0x20 */ u32 priority;
    /* 0x24 */ u32 soundBits;
    /* 0x28 */ u8 soundStatus;
    /* 0x29 */ u8 freshness;
    /* 0x2A */ u8 prev;
    /* 0x2B */ u8 next;
    /* 0x2C */ u8 unk2C;
}; // size = 0x30

struct AudioCameraState {
    /* 0x00 */ Vec3f unk00;
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ // u8 compilerPadding0[3];
}; // size = 0x10

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x06 */ // u16 compilerPadding;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ u16 unk_0C;
    /* 0x0E */ // u16 compilerPadding;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x16 */ // u16 compilerPadding;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */             // u16 compilerPadding;
} struct_D_801930D0_inner; // size = 0x20

typedef struct {
    // This will need lots of expanding/documenting
    // Its 147 words of space being used
    /* 0x000 */ f32 unk_000;
    /* 0x004 */ f32 unk_004;
    /* 0x008 */ f32 unk_008;
    /* 0x00C */ u16 unk_00C;
    /* 0x00E */ u8 unk_00E[3]; // Array size guessed
    /* 0x011 */ u8 unk_011;
    /* 0x012 */ u8 unk_012;
    /* 0x013 */ u8 unk_013;
    /* 0x014 */ u32 unk_014;
    /* 0x018 */ u16 unk_018;
    /* 0x01A */ u16 unk_01A;
    /* 0x01C */ f32 unk_01C;
    /* 0x020 */ f32 unk_020;
    /* 0x024 */ f32 unk_024;
    /* 0x028 */ u16 unk_028;
    /* 0x02A */ u16 unk_02A;
    /* 0x02C */ u32 unk_02C[5]; // Array size guessed
    /* 0x040 */ u8 unk_040;
    /* 0x041 */ u8 unk_041;
    /* 0x042 */ u8 unk_042;
    /* 0x043 */ u8 unk_043;
    /* 0x044 */ struct_D_801930D0_inner unk_044[16];
    /* 0x244 */ u16 unk_244;
    /* 0x246 */ u16 unk_246;
    /* 0x248 */ u16 unk_248;
    /* 0x24A */ u16 unk_24A;
} struct_D_801930D0_entry; // size = 0x24C

// Not quite the same as the struct found in SM64,
// not even sure that the struct or its members are even
// correct in the MK64 context
struct ChannelVolumeScaleFade {
    /* 0x000 */ f32 current;
    /* 0x004 */ f32 target;
    /* 0x008 */ f32 velocity;
    /* 0x00C */ u16 remainingFrames;
    /* 0x00A */ // u16 compilerPadding;
}; // size = 0x10

typedef struct {
    f32 unk0;
    f32 unk4;
    u8 unk8;
    u8 unk9;
} UnkStruct8018EF18; // size = 0xC

typedef struct {
    u8 thing0;
    u8 thing1;
} SequenceQueueItem;

/** @cond */

void audio_play_character_engine_sound(u8);
void audio_update_drift_sound_pitch(u8, f32);
void audio_reset_session_eu(OSMesg);
f32 audio_calculate_distance_volume(u8, u8);
s8 audio_calculate_doppler(u8, u8, u8);
s8 audio_calculate_pan(f32, f32, u8);
f32 audio_calculate_pitch(u8, u8);
void audio_update_sound_params(u8, u8, u8);
struct Unk_8018EFD8* audio_alloc_sound_source(u8, Vec3f, Vec3f, f32*, u8, u32);
void audio_update_sound_pos(Camera*, Vec3s, struct Unk_8018EFD8*);
void audio_update_doppler_effect(Camera*, Vec3f, struct Unk_8018EFD8*);
void audio_update_sound_source_cameras(void);

Vec3f* audio_get_sound_source_pos(Vec3f, u32);
void audio_process_sfx_script(u8);
void audio_init_cameras_and_state(void);
void audio_cmd_play_sequence(u8, u8, u8, u16);
void audio_cmd_stop_sequence(u8, u16);

void audio_update_sequences(void);
void audio_execute_cmd(u32);
void audio_push_cmd(u32);
void audio_process_cmd_buffer(void);
u16 audio_get_sequence_id(u8);
void audio_clear_sequence_mask(u8, u8);
u8 audio_is_cmd_not_in_queue(s32);
void audio_clear_sequence_timer(u8);
void audio_set_sequence_volume(u8, u8, u8, u8);
void audio_reset_sequence_data(void);

void audio_reset_sequence_data_partial(void);
void audio_set_bank_disabled_mask(u16);
void audio_clear_sequence_mask_bit(u8);
void play_sound(u32, Vec3f*, u8, f32*, f32*, s8*);
void audio_cancel_sound_requests(u8, struct SoundCharacteristics*);
void audio_process_sound_requests(void);
void delete_sound_from_bank(u8, u8);
void audio_process_sound_requests_for_bank(u8);
void audio_play_sound_requests(u8);

void audio_stop_all_sounds_in_bank(u8);
void audio_stop_sounds_in_bank_by_pos(u8, Vec3f*);
void audio_stop_sounds_and_requests_in_bank_by_pos(u8, Vec3f*);
void audio_stop_all_sounds_and_requests_by_pos(Vec3f*);
void audio_stop_sound_and_request_by_pos_and_id(Vec3f*, u32);
void audio_stop_sound_and_request_by_id(u32);
void audio_process_all_sound_requests(void);
void fade_channel_volume_scale(u8, u8, u16);
void audio_process_channel_volume_fade(u8);
void audio_process_sound_banks(void);
void sound_init(void);
void audio_send_character_voice_cmd(void);
void audio_reset_session(void);
void audio_init(void);
void audio_update_throttle_state(u8);
void audio_update_throttle_sound_state(u8);

void audio_update_throttle_sound_pitch(u8);
void audio_update_throttle_sound_volume(u8);
void audio_update_throttle_sound_speed(u8);
void audio_update_throttle_sound_type(u8);

void audio_update_surface_sound(u8);
void audio_handle_race_finish(u8);

void audio_update_water_sound(u8);
void audio_update_lightning_effect_sound(u8);
void audio_update_lightning_effect_pitch(u8);
void audio_check_lightning_effect_end(void);
void audio_update_star_effect_volume(void);
void audio_update_luigi_raceway_tunnel_sound(void);
void audio_update_camera_sound_volume(u8);
void audio_update_all_player_sounds(void);
void play_sound2(s32);
void play_sequence(u16);
void play_sequence2(u16);
void audio_set_sequence_volume_0(u8);
void audio_play_sound_by_player_id_and_pos(u8, u32);

void audio_stop_player_sound(u8, u32);
void audio_play_sound_by_player_id(u8, u32);
void audio_play_character_sound(u8, u32);
void audio_play_character_sound_2901(u8);
void audio_play_character_sound_with_effects(u8, u32);
void audio_play_character_engine_sound(u8);
void audio_stop_character_sounds(u8);
void audio_play_sound_by_pos(Vec3f, Vec3f, u32);
void audio_stop_sound_by_pos_and_id_all_cameras(Vec3f, s32);
void audio_play_race_finish_sound(u8);
void audio_stop_race_finish_sound(u8);
void audio_play_sound_by_pos_with_effects(Vec3f, Vec3f, u32);
void audio_stop_sound_by_pos_all_cameras(Vec3f, u32);
void audio_play_menu_sound(u8);

void audio_set_sequence_and_volume(u8, u8);
void audio_set_flag_800EA108_true(void);
void audio_set_flag_800EA108_false(void);
void audio_set_flag_800EA108_true2(void);
void audio_stop_banks_3_and_5(void);
void audio_set_player_finished(u8);
void audio_set_player_finished_2(u8);
void audio_set_flag_800EA0F4_true(void);
void audio_set_sound_param_14(u8, s8);
void audio_clear_sound_param_14(u8);
void audio_set_sound_param_0C(u8, s8);
void audio_clear_sound_param_0C(u8);
void audio_push_volume_cmd(u8);
void fade_all_channel_volume_scale(u8);
void play_sequences(u16, u16);
void audio_play_final_lap_music(u8);
void play_star_music(u8);
void play_star_sound_effect(u8);
void play_star_music_stop_effect(u8);
void play_star_sound_effect_stop(u8);
void audio_stop_thunder_sound_effect(void);
void play_thunder_sound_effect(u8);
void play_thunder_sound_effect_stop(s32);
void set_player_sound_effect_volume(u8, f32);
void play_boo_sound_effect(u8);

void audio_trigger_losing_ceremony_sequence(void);
void begin_losing_ceremony_sequence(void);
void audio_game_loop_tick(void);
void eu_audio_cmd_flush(void);

// This is some from other file, its definitely not part of audio's data/bss
extern s8 D_801657E5;

// Based on SM64, this should be part of data.c's BSS section. Somehow.
extern s32 gAudioErrorFlags;

extern s8 D_8018EF10;
extern UnkStruct8018EF18 gSoundSourceStates[16];
extern struct Unk_8018EFD8 gSoundSources[];
// These are indexes for gSoundSources, but their purpose is unknown
extern u8 gSoundSourceHead;
extern u8 gSoundSourceTail;
extern Camera* gCopyCamera[4];
extern Vec3f gVelocityCamera[4];
extern Vec3f gCameraLastPos[4];
extern u8 D_8018FC08;
extern s16 D_8018FC10[4][2];

extern struct SoundCharacteristics sSoundBanks[SOUND_BANK_COUNT][20];
extern u8 sSoundBankUsedListBack[SOUND_BANK_COUNT];
extern u8 sSoundBankFreeListFront[SOUND_BANK_COUNT];
extern u8 sNumSoundsInBank[SOUND_BANK_COUNT];
extern u8 gActiveSfx[SOUND_BANK_COUNT][8][8];
extern u8 gSfxChannelIndex;
extern u8 sSoundBankDisabled[SOUND_BANK_COUNT];
extern struct ChannelVolumeScaleFade gChannelVolumeScaleFade[SOUND_BANK_COUNT];
extern SequenceQueueItem gSequenceQueue[3][5];
extern u8 gSequenceQueueSize[3];
extern u32 gAudioCmdBuffer[256];
extern struct_D_801930D0_entry gSequenceState[3];
extern u8 sNumProcessedSoundRequests;
extern u8 sSoundRequestCount;
extern struct Sound sSoundRequests[0x100];

// Data entries
extern u8 gHasAudioInitialized;
extern s32 D_800E9DB4[];
extern f32 D_800E9DC4[4]; // = { 1.0f, 1.0f, 1.0f, 1.0f };
extern f32 D_800E9DD4[4]; // = { 0.0f, 0.0f, 0.0f, 0.0f };
extern f32 D_800E9DE4[4]; // = { 0.0f, 0.0f, 0.0f, 0.0f };
extern f32 D_800E9DF4[8]; // = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
extern s32 D_800E9E14[4]; // = { 0, 0, 0, 0 };
extern s32 D_800E9E24[4]; // = { 0, 0, 0, 0 };
extern s32 D_800E9E34[8];
extern f32 D_800E9E54[4]; // = { 0.0f, 0.0f, 0.0f, 0.0f }; /* const */
extern f32 D_800E9E64[4]; // = { 0.0f, 0.0f, 0.0f, 0.0f };
extern s32 D_800E9E74[4]; // = { 0, 0, 0, 0 };          /* const */
extern s32 D_800E9E84[4];
extern u32 D_800E9E94[4];
extern s32 D_800E9EA4[4]; // = { 0, 0, 0, 0 };
extern f32 D_800E9EB4[4]; // = { 0.0f, 0.0f, 0.0f, 0.0f };
extern f32 D_800E9EC4[4]; // = { 0.0f, 0.0f, 0.0f, 0.0f };
extern f32 D_800E9ED4[4]; // = { 0.0f, 0.0f, 0.0f, 0.0f };
extern f32 D_800E9EE4[4]; // = { 0.0f, 0.0f, 0.0f, 0.0f };
extern f32 D_800E9EF4[4];
extern f32 D_800E9F04[4]; // = { 1.0f, 1.0f, 1.0f, 1.0f };
extern f32 D_800E9F14[4]; // = { 1.0f, 1.0f, 1.0f, 1.0f }; /* const */
extern u8 D_800E9F24[8];  // = { 0, 0, 0, 0, 0, 0, 0, 0 };
extern u8 D_800E9F2C[8];  // = { 0, 0, 0, 0, 0, 0, 0, 0 };
extern f32 D_800E9F34[8]; // = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }; /* const */
extern f32 D_800E9F54[8]; // = { 1.0f, 1.0f, 1.0f, 1.0f }; /* const */
extern u8 D_800E9F74[4];
extern u8 D_800E9F78[4];
extern struct AudioCharacterState gAudioCharacterStates[4];
extern u8 D_800E9F90[];
extern struct AudioCameraState gAudioCameraStates[8];
extern u8 D_800EA0EC[];
extern u8 D_800EA0F0; // = 0;
extern u8 D_800EA0F4;
extern u8 D_800EA104;
extern u8 D_800EA108; // = 0;
extern u8 D_800EA10C[];
extern f32 D_800EA110[4]; // = { 0.0f, 0.0f, 0.0f, 0.0f };
extern f32 D_800EA120[4];
extern f32 D_800EA130[8];
extern f32 D_800EA150; // = 1.4f;
extern u8 D_800EA154[];
extern u16 D_800EA15C;
extern u16 D_800EA160;
extern u8 D_800EA164;
extern s8 D_800EA168;
extern u8 D_800EA170[];
extern u16 D_800EA174; // = 0;
extern f32 D_800EA178;
extern f32 D_800EA17C;
extern u16 D_800EA180; // = 0;                          /* const */
extern u16 D_800EA184;
extern u8 gAudioNumChannelsPerBank[][6];
extern u8 D_800EA1A0[][6];
extern u8 gAudioNumCameras; // = 0;
extern u16 D_800EA1C4;
// Most similar to gGlobalSoundSource from SM64, but I don't know if its really
// a sound source, its usage makes it look like a 0'd Vec3f for general usage
extern Vec3f gAudioDefaultPos; // = {0.0f, 0.0f, 0.0f}
extern f32 gAudioOneFloat;
extern s8 gAudioZeroS8; // = 0;
extern u8 gAudioCmdWritePos;
extern u8 gAudioCmdReadPos;
extern u8 gAudioMuteMusic;
extern u8 gSoundModes[];
extern u8 gAudioActiveSequence[];
extern u8 D_800EA244;

extern s8 D_800EA16C;

extern OSMesgQueue* gAudioResetQueuePtr;
extern OSMesgQueue* gAudioResetQueue2Ptr;

/** @endcond */

#endif
