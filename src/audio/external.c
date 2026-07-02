#include <ultra64.h>
#include <macros.h>
#include <defines.h>
#include <mk64.h>
#include <course.h>

#include "camera.h"
#include "math_util_2.h"
#include <sounds.h>
#include "audio/external.h"
#include "audio/load.h"
#include "audio/data.h"
#include "audio/port_eu.h"
#include "code_800029B0.h"
#include "cpu_vehicles_camera_path.h"
#include "menu_items.h"
#include "seq_ids.h"

s8 D_8018EF10;
UnkStruct8018EF18 gSoundSourceStates[16];
// chained list
struct Unk_8018EFD8 gSoundSources[50];
u8 gSoundSourceHead;
u8 gSoundSourceTail;
Camera* gCopyCamera[4];
Vec3f gVelocityCamera[4];
Vec3f gCameraLastPos[4];
u8 D_8018FC08;
s16 D_8018FC10[4][2];
struct Sound sSoundRequests[0x100];
struct SoundCharacteristics sSoundBanks[SOUND_BANK_COUNT][20];
u8 sSoundBankUsedListBack[SOUND_BANK_COUNT];
u8 sSoundBankFreeListFront[SOUND_BANK_COUNT];
u8 sNumSoundsInBank[SOUND_BANK_COUNT];
u8 gActiveSfx[SOUND_BANK_COUNT][8][8];
u8 gSfxChannelIndex;
ubool8 sSoundBankDisabled[SOUND_BANK_COUNT];
struct ChannelVolumeScaleFade gChannelVolumeScaleFade[SOUND_BANK_COUNT];
SequenceQueueItem gSequenceQueue[3][5];
u8 gSequenceQueueSize[3];
u32 gAudioCmdBuffer[256];
struct_D_801930D0_entry gSequenceState[3];

u8 gHasAudioInitialized = 0;
UNUSED s32 D_800E9DA4[] = { 0, 0, 0, 0 };
s32 D_800E9DB4[] = { 0, 0, 0, 0 };
f32 D_800E9DC4[] = { 1.0f, 1.0f, 1.0f, 1.0f };
f32 D_800E9DD4[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 D_800E9DE4[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 D_800E9DF4[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
s32 D_800E9E14[] = { 0, 0, 0, 0 };
s32 D_800E9E24[] = { 0, 0, 0, 0 };
s32 D_800E9E34[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
f32 D_800E9E54[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 D_800E9E64[] = { 0.0f, 0.0f, 0.0f, 0.0f };
s32 D_800E9E74[] = { 0, 0, 0, 0 };
s32 D_800E9E84[] = { 0, 0, 0, 0 };
u32 D_800E9E94[] = { 0, 0, 0, 0 };
s32 D_800E9EA4[] = { 0, 0, 0, 0 };
f32 D_800E9EB4[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 D_800E9EC4[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 D_800E9ED4[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 D_800E9EE4[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 D_800E9EF4[] = { 1.0f, 1.0f, 1.0f, 1.0f };
f32 D_800E9F04[] = { 1.0f, 1.0f, 1.0f, 1.0f };
f32 D_800E9F14[] = { 1.0f, 1.0f, 1.0f, 1.0f };
u8 D_800E9F24[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
u8 D_800E9F2C[NUM_PLAYERS] = { 0, 0, 0, 0, 0, 0, 0, 0 };
f32 D_800E9F34[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
f32 D_800E9F54[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
u8 D_800E9F74[] = { 0, 0, 0, 0 };
u8 D_800E9F78[] = { 0, 0, 0, 0 };
struct AudioCharacterState gAudioCharacterStates[] = {
    { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, 3800.0f, 3.4f, 0.4f, -1.0f, 0.4f, 1100.0f, 630.0f, 3600.0f, 1.0f },
    { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, 3800.0f, 3.4f, 0.4f, -1.0f, 0.4f, 1100.0f, 630.0f, 3600.0f, 1.0f },
    { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, 3800.0f, 3.4f, 0.4f, -1.0f, 0.4f, 1100.0f, 630.0f, 3600.0f, 1.0f },
    { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, 3800.0f, 3.4f, 0.4f, -1.0f, 0.4f, 1100.0f, 630.0f, 3600.0f, 1.0f }
};
struct AudioCameraState gAudioCameraStates[] = { { { 0.0f, 1.0f, 1.0f }, 0 }, { { 0.0f, 1.0f, 1.0f }, 0 },
                                     { { 0.0f, 1.0f, 1.0f }, 0 }, { { 0.0f, 1.0f, 1.0f }, 0 },
                                     { { 0.0f, 1.0f, 1.0f }, 0 }, { { 0.0f, 1.0f, 1.0f }, 0 },
                                     { { 0.0f, 1.0f, 1.0f }, 0 }, { { 0.0f, 1.0f, 1.0f }, 0 } };
u8 D_800EA0EC[] = { 0, 0, 0, 0 };
u8 D_800EA0F0 = 0;
u8 D_800EA0F4 = 0;
UNUSED Vec3f D_800EA0F8 = { 0.0f, 0.0f, 1.0f };
u8 D_800EA104 = 0;
u8 D_800EA108 = 0;
u8 D_800EA10C[] = { 0, 0, 0, 0 };
f32 D_800EA110[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 D_800EA120[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 D_800EA130[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
f32 D_800EA150 = 1.4f;
u8 D_800EA154[] = { 2, 2, 88, 90, 3, 48, 88, 48 };
u16 D_800EA15C = 0;
u16 D_800EA160 = 0;
u8 D_800EA164 = 0;
s8 D_800EA168 = 0;
s8 D_800EA16C = 0;
u8 D_800EA170[] = { 0, 0, 0, 0 };
u16 D_800EA174 = 0;
f32 D_800EA178 = 1.0f;
f32 D_800EA17C = 0.85f;
u16 D_800EA180 = 0;
u16 D_800EA184 = 0;
u8 gAudioNumChannelsPerBank[][6] = { { 4, 2, 2, 2, 2, 1 }, { 6, 2, 2, 2, 2, 1 }, { 8, 2, 2, 0, 1, 1 }, { 8, 2, 2, 0, 1, 1 } };
u8 D_800EA1A0[][6] = { { 4, 1, 1, 2, 2, 1 }, { 3, 1, 1, 2, 2, 1 }, { 3, 1, 1, 0, 1, 1 }, { 3, 1, 1, 0, 1, 1 } };
u8 sSoundRequestCount = 0;
u8 sNumProcessedSoundRequests = 0;
u8 gAudioNumCameras = 0;
u16 D_800EA1C4 = 0;
Vec3f gAudioDefaultPos = { 0.0f, 0.0f, 0.0f };
f32 gAudioOneFloat = 1.0f;
u32 external_unused_u32_0 = 0x00000000;
s8 gAudioZeroS8 = 0;
u32 external_unused_u32_1 = 0x00000000;
u8 gAudioCmdWritePos = 0;
u8 gAudioCmdReadPos = 0;
u8 gAudioMuteMusic = 0;
u8 gSoundModes[] = { 0, 1, 2, 3 };
u8 gAudioActiveSequence[] = { 0, 0, 0, 0 };

char external_unused_string00[] = "Error : Queue is not empty ( %x ) \n";
char external_unused_string01[] = "specchg error\n";
char external_unused_string02[] = "***** CAM MAX %d *****\n";
u8 D_800EA244 = 0;
char external_unused_string03[] = "entryout !!! %d\n";
char external_unused_string04[] = "AFTER GOAL VOICE FLAME %d\n";
char external_unused_string05[] = "*** Pause On ***\n";
char external_unused_string06[] = "*** Pause Off ***\n";
char external_unused_string07[] = "CALLED!! Na_ChangeSoundMode player %d\n";
char external_unused_string08[] = "CALLED!! Na_ChangeSoundMode spec   %d\n";
char external_unused_string09[] = "Interfaced Spec Change player %d\n";
char external_unused_string10[] = "Interfaced Spec Change spec   %d\n";
UNUSED u32 external_unused_u32s[] = { 0xff000000, 0xff000000, 0x00000000 };
char external_unused_string11[] = "FX MIX %d\n";
char external_unused_string12[] = "************** Seq Fadeout ***************\n";
char external_unused_string13[] = "SEQ FADE OUT TIME %d\n";
#ifdef VERSION_EU
char external_unused_string_eu_02[] = "************** SE Fadeout ***************\n";
char external_unused_string_eu_03[] = "SE FADE OUT TIME %d\n";
#endif

#ifdef VERSION_EU
#define AUDIO_LEFT_TYRE FRONT_LEFT
#define AUDIO_RIGHT_TYRE FRONT_RIGHT
#else
#define AUDIO_LEFT_TYRE BACK_LEFT
#define AUDIO_RIGHT_TYRE BACK_RIGHT
#endif

// Requires void in the argument list to match properly.
}

void audio_reset_session_eu(OSMesg presetId) {
    OSMesg mesg;
    osRecvMesg(gAudioResetQueue2Ptr, &mesg, 0);
    osSendMesg(gAudioResetQueuePtr, presetId, 0);
    osRecvMesg(gAudioResetQueue2Ptr, &mesg, 1);
    if (mesg != presetId) {
        osRecvMesg(gAudioResetQueue2Ptr, &mesg, 1);
    }
}

f32 audio_calculate_distance_volume(u8 bank, u8 soundId) {
    f32 temp_f0;
    f32 var_f2;
    s32 var_v0;
    struct SoundCharacteristics* temp_v0;

    temp_v0 = &sSoundBanks[bank][soundId];
    if (temp_v0->soundBits & 0x400000) {
        return 1.0f;
    }
    temp_f0 = temp_v0->distance;
    if (temp_f0 > 2000.0f) {
        var_f2 = 0.0f;
    } else {
        switch (temp_v0->soundBits & 0x30000) { /* irregular */
            case 0x10000:
                var_v0 = 0x1F4;
                break;
            case 0x20000:
                var_v0 = 0x29A;
                break;
            case 0x30000:
                var_v0 = 0x3E8;
                break;
            default:
                var_v0 = 0x190;
                break;
        }
        if (temp_f0 < var_v0) {
            var_f2 = (((var_v0 - temp_f0) / var_v0) * 0.5) + 0.5;
        } else {
            var_f2 = (1.0 - ((temp_f0 - var_v0) / (2000.0f - var_v0))) * 0.5;
        }
        var_f2 *= var_f2;
    }
    return var_f2;
}

s8 audio_calculate_doppler(u8 bank, u8 soundId, u8 channel) {
    s32 var_a0;
    s8 var_v0;
    s8 var_v1;

    var_v0 = 0;
    var_v1 = 0;
    if (!(sSoundBanks[bank][soundId].soundBits & 0x200000)) {
        if (sSoundBanks[bank][soundId].distance < 500.0f) {
            var_v0 = (sSoundBanks[bank][soundId].distance / 500.0f) * 10.0f;
        } else {
            var_v0 = 0x0A;
        }
    }
    if (IS_SEQUENCE_CHANNEL_VALID(gSequencePlayers[2].channels[channel])) {
        var_v1 = gSequencePlayers[2].channels[channel]->soundScriptIO[6];
    }
    if (var_v1 == -1) {
        var_v1 = 0;
    }
    var_a0 = *sSoundBanks[bank][soundId].unk18 + var_v0 + var_v1 + D_8018EF10;
    if (var_a0 >= 0x80) {
        var_a0 = 0x7F;
    }
    return var_a0;
}

s8 audio_calculate_pan(f32 arg0, f32 arg1, u8 cameraId) {
    f32 var_f0;
    f32 var_f14;
    f32 new_var;
    f32* new_var2;
    f32 var_f16;
    f32 var_f18;
    f32 var_f20;
    f32 var_f2;
    new_var2 = &var_f0;

    if (gAudioNumCameras == 0) {
        if (D_800EA0F4 != 0) {
            var_f2 = 10.0f;
            var_f14 = 20.0f;
            var_f16 = 10.0f;
            var_f18 = 2.5f;
        } else {
            var_f0 = 100.0f;
            var_f2 = *new_var2;
            var_f14 = 200.0f;
            var_f16 = 5.0f;
            var_f18 = 3.3333333f;
        }
        var_f20 = (arg0 < 0.0f) ? -arg0 : arg0;

        if (var_f2 < var_f20) {
            var_f20 = var_f2;
        }

        new_var = arg0;
        var_f0 = (arg1 < 0.0f) ? -arg1 : arg1;
        if (var_f2 < (var_f0 = *new_var2)) {
            var_f0 = var_f2;
        }
        if ((new_var == 0.0f) && (arg1 == 0.0f)) {
            var_f2 = 0.5f;
        } else if ((new_var >= 0.0f) && (var_f0 <= var_f20)) {
            var_f2 = 1.0f - ((var_f14 - var_f20) / (var_f16 * (var_f14 - var_f0)));
        } else if ((new_var < 0.0f) && (var_f0 <= var_f20)) {
            var_f2 = (var_f14 - var_f20) / (var_f16 * (var_f14 - var_f0));
        } else {
            var_f2 = (arg0 / (var_f18 * var_f0)) + 0.5f;
        }
        if (var_f2 > 1.0f) {
            var_f2 = 1.0f;
        }
        if (var_f2 < 0.0f) {
            var_f2 = 0.0f;
        }
        return (s8) (s32) ((var_f2 * 127.0f) + 0.5f);
    }
    return (cameraId & 1) * 0x7F;
}

f32 audio_calculate_pitch(u8 bank, u8 soundId) {
    f32 phi_f2;

    phi_f2 = 1.0f;
    if (sSoundBanks[bank][soundId].soundBits & 0x800000) {
        phi_f2 -= ((gAudioRandom & 0xF) / 192.0f);
    }
    return phi_f2;
}

void audio_update_sound_params(u8 arg0, u8 arg1, u8 arg2) {
    f32 sp3C;
    s8 sp3B;
    f32 sp34;
    s8 sp33;
    UnkStruct8018EF18* temp_s0_2;
    struct SoundCharacteristics* temp_s0;

    sp3B = 0;
    sp33 = 0x40;
    sp3C = 1.0f;
    sp34 = 1.0f;
    switch (arg0) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            temp_s0 = &sSoundBanks[arg0][arg1];
            temp_s0->distance = sqrtf(temp_s0->distance);
            sp3C = (audio_calculate_distance_volume(arg0, arg1) * *temp_s0->unk14) * gChannelVolumeScaleFade[arg0].current;
            sp3B = audio_calculate_doppler(arg0, arg1, arg2);
            sp34 = audio_calculate_pitch(arg0, arg1) * *temp_s0->unk10;
            sp33 = audio_calculate_pan(*temp_s0->unk00[0], *temp_s0->unk08, temp_s0->cameraId);
            break;
    }
    temp_s0_2 = &gSoundSourceStates[arg2];
    if (sp3C != temp_s0_2->unk0) {
        eu_audio_cmd_send_byte(((arg2 & 0xFF) << 8) | 0x06020000 | 3, (u8) (u32) (sp3C * 127.0f));
        temp_s0_2->unk0 = sp3C;
    }
    if (sp3B != (s8) temp_s0_2->unk8) {
        eu_audio_cmd_send_byte(((arg2 & 0xFF) << 8) | 0x05020000, sp3B);
        temp_s0_2->unk8 = (u8) sp3B;
    }
    if (sp34 != temp_s0_2->unk4) {
        eu_audio_cmd_send_f32(((arg2 & 0xFF) << 8) | 0x04020000, sp34);
        temp_s0_2->unk4 = sp34;
    }
    if (sp33 != (s8) temp_s0_2->unk9) {
        eu_audio_cmd_send_byte(((arg2 & 0xFF) << 8) | 0x03020000, sp33);
        temp_s0_2->unk9 = (u8) sp33;
    }
}

struct Unk_8018EFD8* audio_alloc_sound_source(u8 arg0, Vec3f position, f32* velocity, f32* arg3, u8 arg4, u32 soundBits) {
    struct Unk_8018EFD8* temp_a1;
    UNUSED struct Unk_8018EFD8* temp_v1;
    UNUSED u8 temp_t7;
    u8 why1;

    if (gSoundSources[gSoundSourceHead].next != 0xFF) {
        why1 = gSoundSourceHead;
        gSoundSources[why1].prev = gSoundSourceTail;
        temp_a1 = &gSoundSources[gSoundSourceHead];
        gSoundSources[gSoundSourceTail].next = why1;
        temp_t7 = temp_a1->next;
        gSoundSourceTail = why1;
        gSoundSourceHead = gSoundSources[gSoundSourceHead].next;
        gSoundSources[gSoundSourceHead].prev = 0xFF;
        gSoundSources[why1].posX = &position[0];
        gSoundSources[why1].posY = &position[1];
        gSoundSources[why1].posZ = &position[2];
        gSoundSources[why1].next = 0xFF;
        gSoundSources[why1].velX = &velocity[0];
        gSoundSources[why1].velY = &velocity[1];
        gSoundSources[why1].velZ = &velocity[2];
        gSoundSources[why1].unk18[1] = 0.0f;
        gSoundSources[why1].unk24 = arg3;
        gSoundSources[why1].cameraId = arg4;
        gSoundSources[why1].unk30 = arg0;
        gSoundSources[why1].soundBits = soundBits;
        return &gSoundSources[why1];
    }
    return NULL;
}

void audio_update_sound_pos(Camera* arg0, Vec3s rot, struct Unk_8018EFD8* arg2) {
    f32 x;
    f32 y;

    x = arg0->pos[0] - *arg2->posX;
    y = arg0->pos[2] - *arg2->posZ;
    arg2->unk18[0] = math_calc_x_rotated(x, y, rot[1]);
    arg2->unk18[2] = math_calc_z_rotated(x, y, rot[1]);
}

void audio_update_doppler_effect(Camera* camera, Vec3f velocity, struct Unk_8018EFD8* arg2) {
    f32 sp44;
    f32 temp_f6;
    f32 x;
    f32 y;
    f32 dist0;
    f32 dist1;
    f32 thing0;
    f32 thing1;
    f32 temp_f2;

    x = (*arg2->posX) - camera->pos[0];
    y = (*arg2->posZ) - camera->pos[2];

    sp44 = (*arg2->velX) - velocity[0];
    temp_f6 = (*arg2->velZ) - velocity[2];

    thing0 = x + sp44;
    thing1 = y + temp_f6;

    dist0 = sqrtf((x * x) + (y * y));
    dist1 = sqrtf((thing0 * thing0) + (thing1 * thing1));

    temp_f2 = 1.0f / (1.0f - ((dist0 - dist1) / arg2->unk34));

    if (temp_f2 > 0.1f) {
        arg2->unk2C = temp_f2;
    } else {
        arg2->unk2C = 0.1f;
    }

    if ((*arg2->unk24) != 0.0f) {
        arg2->unk2C *= (((*arg2->unk24) / gAudioCameraStates[arg2->unk30].unk00[1]) + gAudioCameraStates[arg2->unk30].unk00[0]) +
                       D_800E9F34[arg2->unk30];
    }
}

void audio_update_sound_source_cameras(void) {
    u8 var_s1;
    u8 var_a1;
    u8 cameraId;
    Camera** camera;

    var_a1 = gAudioNumCameras + 1;
    for (var_s1 = 0; var_s1 < var_a1; var_s1++) {
        gVelocityCamera[var_s1][0] = gCopyCamera[var_s1]->pos[0] - gCameraLastPos[var_s1][0];
        gVelocityCamera[var_s1][2] = gCopyCamera[var_s1]->pos[2] - gCameraLastPos[var_s1][2];
        gCameraLastPos[var_s1][0] = gCopyCamera[var_s1]->pos[0];
        gCameraLastPos[var_s1][2] = gCopyCamera[var_s1]->pos[2];
    }

    var_a1 = 0;
    var_s1 = gSoundSources[0].next;
    while (var_s1 != 0xFF) {
        if (gSoundSources[var_s1].unk18[1] == 100000.0f) {
            if (gSoundSourceTail == var_s1) {
                gSoundSourceTail = gSoundSources[var_s1].prev;
            } else {
                gSoundSources[gSoundSources[var_s1].next].prev = gSoundSources[var_s1].prev;
            }
            gSoundSources[gSoundSources[var_s1].prev].next = gSoundSources[var_s1].next;
            gSoundSources[var_s1].prev = 0xFF;
            gSoundSources[var_s1].next = gSoundSourceHead;
            gSoundSources[gSoundSourceHead].prev = var_s1;
            gSoundSourceHead = var_s1;
        } else {
            cameraId = gSoundSources[var_s1].cameraId;
            // Why? Why would you do it this way? For what possible reason?
            camera = &gCopyCamera[cameraId];
            audio_update_sound_pos(*camera, (*camera)->rot, &gSoundSources[var_s1]);
            if (gAudioDefaultPos != gSoundSources[var_s1].velX) {
                audio_update_doppler_effect(*camera, gVelocityCamera[0], &gSoundSources[var_s1]);
            }
            var_a1 = var_s1;
        }
        var_s1 = gSoundSources[var_a1].next;
        if ((var_s1 != 0xFF) && (D_800EA244 < var_s1)) {
            D_800EA244 = var_s1;
        }
    }
}

Vec3f* audio_get_sound_source_pos(Vec3f pos, u32 soundBits) {
    u8 it; // iterator
    Vec3f* ret;
    // Only here to force a match
    UNUSED f32* thing = pos;
    struct Unk_8018EFD8* temp_a1;

    ret = 0;
    it = gSoundSources[0].next;
    while (it != 0xFF) {
        temp_a1 = &gSoundSources[it];
        // It doesn't matter what you set var_v0 to here actually
        it = gSoundSources[0].next;
        if ((pos == temp_a1->posX) && (soundBits == temp_a1->soundBits)) {
            // I suspect all this weirdness here is a result of someone not knowing the 'break' keyword
            it = 0xFF;
            if (temp_a1->unk18[1] != 100000.0f) {
                ret = &temp_a1->unk18;
            } else {
                goto test;
            }
        } else {
        test:
            it = temp_a1->next;
        }
    }
    return ret;
}

void audio_process_sfx_script(u8 player) {
    s16 sp46;
    s16 var_s1;
    s16 sp42;
    u8 var_s0;
    u8 temp_s0;
    u8 why = 0xFF;
    s32 var_a2;

    var_a2 = 0xF;
    if (gSequencePlayers[player].enabled != 0) {
        switch (gScreenModeSelection) { /* irregular */
            case 0:
                break;
            case 1:
                var_a2 = 0xE;
                break;
            case 3:
                if (gPlayerCountSelection1 == 3) {
                    var_a2 = 0xD;
                } else {
                    var_a2 = 0xC;
                }
                break;
        }
        temp_s0 = gSequencePlayers[player].channels[var_a2]->soundScriptIO[0];
        if (temp_s0 != why) {
            sp46 = gSequencePlayers[player].channels[var_a2]->soundScriptIO[1] % 4u;
            var_s1 = gSequencePlayers[player].channels[var_a2]->soundScriptIO[2] % 16u;
            if (var_s1 >= 0xA) {
                var_s1 = 9;
            }
            sp42 = gSequencePlayers[player].channels[var_a2]->soundScriptIO[3] % 8u;
            eu_audio_cmd_send_byte(((player & 0xFF) << 0x10) | 0x06000000 | ((var_a2 & 0xFF) << 8), -1);
        }
        switch (temp_s0) { /* switch 1; irregular */
            case 1:        /* switch 1 */
                D_8018FC10[sp46][0] = var_s1;
                D_8018FC10[sp46][1] = sp42;
                for (var_s0 = 0; var_s0 < 4; var_s0++) {
                    if (D_8018FC10[var_s0][0] != why) {
                        init_camera_path_audio(var_s0, D_8018FC10[var_s0][0], D_8018FC10[var_s0][1]);
                        D_8018FC10[var_s0][0] = why;
                    }
                }
                break;
            case 2: /* switch 1 */
                D_8018FC10[sp46][0] = var_s1;
                D_8018FC10[sp46][1] = sp42;
                break;
        }
    }
}

void audio_init_cameras_and_state(void) {
    u8 var_v0;

    D_8018EF10 = 0;
    gCopyCamera[0] = camera1;
    gCopyCamera[1] = camera2;
    gCopyCamera[2] = camera3;
    gCopyCamera[3] = camera4;
    gSoundSourceTail = 0;
    gSoundSourceHead = 1;
    D_800EA0F4 = 0;
    D_8018FC08 = 0;
    D_800EA104 = 0;
    D_800EA108 = 0;
    D_800EA0F0 = 0;
    D_800EA16C = 0;
    eu_audio_cmd_send_u32(0xF2000000U, 0);
    D_800EA16C = 0;
    D_800EA15C = 0;
    D_800EA160 = 0;
    D_800EA164 = 0;
    D_800EA178 = 1.0f;
    D_800EA17C = 0.85f;
    D_800EA180 = 0;
    D_800EA184 = 0;
    for (var_v0 = 0; var_v0 < 4; var_v0++) {
        D_800E9DB4[var_v0] = 0;
        D_800E9DF4[var_v0] = 0; // This is an f32 FYI, but 0.0f doesn't match right :)
        gVelocityCamera[var_v0][0] = 0.0f;
        gVelocityCamera[var_v0][1] = 0.0f;
        gVelocityCamera[var_v0][2] = 0.0f;
        gCameraLastPos[var_v0][0] = 0.0f;
        gCameraLastPos[var_v0][1] = 0.0f;
        gCameraLastPos[var_v0][2] = 0.0f;
        D_800EA0EC[var_v0] = 0;
        D_800E9EA4[var_v0] = 0;
        gAudioCharacterStates[var_v0].unk_14 = 0;
        D_800E9E74[var_v0] = 0;
        D_800E9E84[var_v0] = 0;
        D_800E9E94[var_v0] = 0;
        gPlayers[var_v0].tyres[AUDIO_LEFT_TYRE].surfaceType = 0;
        gPlayers[var_v0].tyres[AUDIO_RIGHT_TYRE].surfaceType = 0;
        gPlayers[var_v0].effects = 0;
        gPlayers[var_v0].unk_20C = 0.0f;
        gPlayers[var_v0].unk_0C0 = 0;
        gPlayers[var_v0].unk_098 = 0.0f;
        gPlayers[var_v0].oobProps = 0;
        D_8018FC10[var_v0][0] = 0x00FF;
        D_8018FC10[var_v0][1] = 0;
        D_800EA10C[var_v0] = 0;
        D_800E9F74[var_v0] = 0;
        D_800E9F78[var_v0] = 0;
    }
    for (var_v0 = 0; var_v0 < NUM_PLAYERS; var_v0++) {
        D_800E9F24[var_v0] = 0;
        D_800E9F2C[var_v0] = 0;
        D_800E9F34[var_v0] = 0.0f;
        D_800E9F54[var_v0] = 0.0f;
        D_800EA130[var_v0] = 0.0f;
        gAudioCameraStates[var_v0].unk0C = 0;
        gPlayers[var_v0].effects = 0;
    }
    for (var_v0 = 0; var_v0 < 16; var_v0++) {
        gSoundSourceStates[var_v0].unk0 = 1.0f;
        gSoundSourceStates[var_v0].unk4 = 1.0f;
        gSoundSourceStates[var_v0].unk8 = 0;
        gSoundSourceStates[var_v0].unk9 = 0x40;
    }
    gSoundSources[0].prev = 0xFF;
    gSoundSources[0].next = 0xFF;
    for (var_v0 = 1; var_v0 < 49; var_v0++) {
        gSoundSources[var_v0].prev = var_v0 - 1;
        gSoundSources[var_v0].next = var_v0 + 1;
    }
    gSoundSources[var_v0].prev = var_v0 - 1;
    gSoundSources[var_v0].next = 0xFF;
}

void audio_cmd_play_sequence(u8 arg0, u8 arg1, u8 arg2, u16 arg3) {
    u8 var_v1;
    UNUSED s32 pad;

    if ((gAudioMuteMusic != 0) && (arg0 != 2)) {
        return;
    }

    eu_audio_cmd_send_u32(0x82000000 | (((u32) arg0 & 0xFF) << 0x10) | (((u32) arg1 & 0xFF) << 8), arg3);
    gSequenceState[arg0].unk_248 = arg1 | (arg2 << 8);
    if (gSequenceState[arg0].unk_000 != 1.0f) {
        eu_audio_cmd_send_f32(0x41000000 | (((u32) arg0 & 0xFF) << 0x10), gSequenceState[arg0].unk_000);
    }
    gSequenceState[arg0].unk_028 = 0;
    gSequenceState[arg0].unk_018 = 0;
    gSequenceState[arg0].unk_014 = 0;

    for (var_v1 = 0; var_v1 < 16; var_v1++) {
        gSequenceState[arg0].unk_044[var_v1].unk_00 = 1.0f;
        gSequenceState[arg0].unk_044[var_v1].unk_0C = 0;
        gSequenceState[arg0].unk_044[var_v1].unk_10 = 1.0f;
        gSequenceState[arg0].unk_044[var_v1].unk_1C = 0;
    }

    gSequenceState[arg0].unk_244 = 0;
    gSequenceState[arg0].unk_246 = 0;
}

void audio_cmd_stop_sequence(u8 arg0, u16 arg1) {
    eu_audio_cmd_send_u32(((arg0 & 0xFF) << 0x10) | 0x83000000, arg1);
    gSequenceState[arg0].unk_248 = 0xFFFF;
}

void audio_execute_cmd(u32 cmd) {
    f32 freqScaleTarget;
    u16 channelMaskDisable;
    u16 val;
    u16 fadeTimer;
    u8 priority;
    u8 ioPort;
    u8 i;
    u8 duration;
    u8 channelIndex;
    u8 found;
    u8 seqId;
    u8 subArgs;
    u8 op;
    u8 seqPlayerIndex;

    op = cmd >> 28;
    seqPlayerIndex = (cmd & 0xF000000) >> 24;

    switch (op) {
        case 0:
            seqId = cmd & 0xFF;
            subArgs = (cmd & 0xFF00) >> 8;
            fadeTimer = (cmd & 0xFF0000) >> 13;
            audio_cmd_play_sequence(seqPlayerIndex, seqId, subArgs, fadeTimer);
            break;

        case 1:
            fadeTimer = (cmd & 0xFF0000) >> 13;
            audio_cmd_stop_sequence(seqPlayerIndex, fadeTimer);
            break;

        case 2:
            seqId = cmd & 0xFF;
            subArgs = (cmd & 0xFF00) >> 8;
            fadeTimer = (cmd & 0xFF0000) >> 13;
            priority = subArgs;

            for (i = 0; i < gSequenceQueueSize[seqPlayerIndex]; i++) {
                if (gSequenceQueue[seqPlayerIndex][i].thing0 == seqId) {
                    if (i == 0) {
                        audio_cmd_play_sequence(seqPlayerIndex, seqId, subArgs, fadeTimer);
                    }
                    return;
                }
            }

            found = gSequenceQueueSize[seqPlayerIndex];
            for (i = 0; i < gSequenceQueueSize[seqPlayerIndex]; i++) {
                if (priority >= gSequenceQueue[seqPlayerIndex][i].thing1) {
                    found = i;
                    i = gSequenceQueueSize[seqPlayerIndex];
                }
            }

            if ((found != gSequenceQueueSize[seqPlayerIndex]) || (found == 0)) {
                if (gSequenceQueueSize[seqPlayerIndex] < 5) {
                    gSequenceQueueSize[seqPlayerIndex]++;
                }
                for (i = gSequenceQueueSize[seqPlayerIndex] - 1; i != found; i--) {
                    gSequenceQueue[seqPlayerIndex][i].thing1 = gSequenceQueue[seqPlayerIndex][i - 1].thing1;
                    gSequenceQueue[seqPlayerIndex][i].thing0 = gSequenceQueue[seqPlayerIndex][i - 1].thing0;
                }

                gSequenceQueue[seqPlayerIndex][found].thing1 = subArgs;
                gSequenceQueue[seqPlayerIndex][found].thing0 = seqId;
            }
            if (found == 0) {
                audio_cmd_play_sequence(seqPlayerIndex, seqId, subArgs, fadeTimer);
            }
            break;

        case 3:
            fadeTimer = (cmd & 0xFF0000) >> 13;

            found = gSequenceQueueSize[seqPlayerIndex];
            for (i = 0; i < gSequenceQueueSize[seqPlayerIndex]; i++) {
                seqId = cmd & 0xFF;
                if (gSequenceQueue[seqPlayerIndex][i].thing0 == seqId) {
                    found = i;
                    i = gSequenceQueueSize[seqPlayerIndex];
                }
            }

            if (found != gSequenceQueueSize[seqPlayerIndex]) {
                for (i = found; i < (gSequenceQueueSize[seqPlayerIndex] - 1); i++) {
                    gSequenceQueue[seqPlayerIndex][i].thing1 = gSequenceQueue[seqPlayerIndex][i + 1].thing1;
                    gSequenceQueue[seqPlayerIndex][i].thing0 = gSequenceQueue[seqPlayerIndex][i + 1].thing0;
                }

                gSequenceQueueSize[seqPlayerIndex]--;
            }
            if (found == 0) {
                audio_cmd_stop_sequence(seqPlayerIndex, fadeTimer);
                if (gSequenceQueueSize[seqPlayerIndex] != 0) {
                    audio_cmd_play_sequence(seqPlayerIndex, gSequenceQueue[seqPlayerIndex][0].thing0,
                                  gSequenceQueue[seqPlayerIndex][0].thing1, fadeTimer);
                }
            }
            break;

        case 4:
            duration = (cmd & 0xFF0000) >> 15;
            val = cmd & 0xFF;

            if (duration == 0) {
                duration++;
            }

            gSequenceState[seqPlayerIndex].unk_004 = val / 127.0f;
            if (gSequenceState[seqPlayerIndex].unk_000 != gSequenceState[seqPlayerIndex].unk_004) {
                gSequenceState[seqPlayerIndex].unk_008 =
                    (gSequenceState[seqPlayerIndex].unk_000 - gSequenceState[seqPlayerIndex].unk_004) / duration;
                gSequenceState[seqPlayerIndex].unk_00C = duration;
            }
            break;

        case 5:
            duration = (cmd & 0xFF0000) >> 15;
            val = cmd & 0xFFFF;

            if (duration == 0) {
                duration++;
            }
            freqScaleTarget = (f32) val / 1000.0f;
            for (i = 0; i < 0x10; i++) {
                gSequenceState[seqPlayerIndex].unk_044[i].unk_14 = freqScaleTarget;
                gSequenceState[seqPlayerIndex].unk_044[i].unk_1C = duration;
                gSequenceState[seqPlayerIndex].unk_044[i].unk_18 =
                    (gSequenceState[seqPlayerIndex].unk_044[i].unk_10 - freqScaleTarget) / duration;
            }

            gSequenceState[seqPlayerIndex].unk_244 = 0xFFFF;
            break;

        case 6:
            duration = (cmd & 0xFF0000) >> 15;
            channelIndex = (cmd & 0xF00) >> 8;
            val = cmd & 0xFF;

            if (duration == 0) {
                duration++;
            }

            gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_04 = val / 127.0f;
            if (gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_00 !=
                gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_04) {
                gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_08 =
                    (gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_00 -
                     gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_04) /
                    duration;
                gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_0C = duration;
                gSequenceState[seqPlayerIndex].unk_244 |= 1 << channelIndex;
            }
            break;

        case 7:
            ioPort = (cmd & 0xFF0000) >> 16;
            val = cmd & 0xFF;
            eu_audio_cmd_send_byte((0x46000000 | ((seqPlayerIndex & 0xFF) << 0x10)) | ((ioPort & 0xFF) << 8), val);
            break;

        case 8:
            channelIndex = (cmd & 0xF00) >> 8;
            ioPort = (cmd & 0xFF0000) >> 16;
            val = cmd & 0xFF;
            if (!(gSequenceState[seqPlayerIndex].unk_24A & (1 << channelIndex))) {
                eu_audio_cmd_send_byte(((0x06000000 | ((seqPlayerIndex & 0xFF) << 0x10)) | (((u32) channelIndex & 0xFF) << 8)) |
                                  (ioPort & 0xFF),
                              val);
            }
            break;

        case 9:
            gSequenceState[seqPlayerIndex].unk_24A = cmd & 0xFFFF;
            break;

        case 10:
            val = 1;
            channelMaskDisable = cmd & 0xFFFF;
            for (i = 0; i < 0x10; i++) {
                eu_audio_cmd_send_byte(0x08000000 | ((seqPlayerIndex & 0xFF) << 0x10) | (((u32) i & 0xFF) << 8),
                              (channelMaskDisable & val) ? 1 : 0);
                val <<= 1;
            }

            break;

        case 11:
            gSequenceState[seqPlayerIndex].unk_014 = cmd;
            break;

        case 12:
            subArgs = (cmd & 0xF00000) >> 20;
            if (subArgs != 0xF) {
                found = gSequenceState[seqPlayerIndex].unk_041++;
                if (found < 5) {
                    gSequenceState[seqPlayerIndex].unk_02C[found] = cmd;
                    gSequenceState[seqPlayerIndex].unk_040 = 2;
                }
            } else {
                gSequenceState[seqPlayerIndex].unk_041 = 0;
            }
            break;

        case 14:
            subArgs = (cmd & 0xF00) >> 8;
            val = cmd & 0xFF;
            switch (subArgs) {
                case 0:
                    eu_audio_cmd_send_u32(0xF0000000, gSoundModes[val]);
                    break;

                case 1:
                    gAudioMuteMusic = val & 1;
                    break;
            }

            break;

        case 15:
            seqId = cmd & 0xFF;
            subArgs = (cmd & 0xFF00) >> 8;
            gAudioNumCameras = subArgs;
            audio_reset_session_eu((void*) seqId);
            gAudioActiveSequence[0] = seqId;
            eu_audio_cmd_send_byte(0x46020000, subArgs);
            audio_reset_session();
            break;

        default:
            break;
    }
}

void audio_push_cmd(u32 arg0) {
    gAudioCmdBuffer[gAudioCmdWritePos] = arg0;
    gAudioCmdWritePos += 1;
}

void audio_process_cmd_buffer(void) {
    for (gAudioCmdReadPos; gAudioCmdWritePos != gAudioCmdReadPos;) {
        audio_execute_cmd(gAudioCmdBuffer[gAudioCmdReadPos++]);
    }
}

u16 audio_get_sequence_id(u8 player) {
    if (!gSequencePlayers[player].enabled) {
        return -1;
    }
    return gSequenceState[player].unk_248;
}

u8 audio_is_cmd_not_in_queue(s32 arg0) {
    u8 var_v1;
    u8 i;

    i = gAudioCmdReadPos;
    var_v1 = true;
    for (i = gAudioCmdReadPos; i < (s32) gAudioCmdWritePos; i++) {
        if ((u32) arg0 == gAudioCmdBuffer[i]) {
            var_v1 = false;
            i = gAudioCmdWritePos;
        }
    }
    return var_v1;
}

#ifdef VERSION_EU
u8 audio_is_cmd_not_in_queue_eu(s32 arg0, s32 arg1) {
    u8 var_v1;
    u8 i;

    i = gAudioCmdReadPos;
    var_v1 = 1;
    for (i = gAudioCmdReadPos; i < (s32) gAudioCmdWritePos; i++) {
        if (arg0 == (gAudioCmdBuffer[i] & arg1)) {
            var_v1 = 0;
            i = gAudioCmdWritePos;
        }
    }
    return var_v1;
}
#endif

void audio_clear_sequence_timer(u8 arg0) {
    gSequenceQueueSize[arg0] = 0;
}

void audio_clear_sequence_mask(u8 arg0, u8 arg1) {
    u8 var_v0;
    u8 thing;

    for (var_v0 = 0; var_v0 < gSequenceState[arg0].unk_041; var_v0++) {
        thing = (gSequenceState[arg0].unk_02C[var_v0] & 0xF00000) >> 0x14;
        if (thing == arg1) {
            gSequenceState[arg0].unk_02C[var_v0] = 0xFF000000;
        }
    }
}

void audio_set_sequence_volume(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    gSequenceState[arg0].unk_00E[arg1] = arg2;
    gSequenceState[arg0].unk_011 = arg3;
    gSequenceState[arg0].unk_012 = 1;
}

void audio_update_sequences(void) {
    u8 seqPlayerIndex;
    f32 volume;
    u8 tempoOp;
    u16 tempoTarget;
    u8 channelIndex;
    u8 j;
    u32 tempoCmd;
    u16 tempoPrev;
    u8 tempoTimer;
    u8 setupOp;
    u8 targetSeqPlayerIndex;
    u8 setupVal1;
    u8 setupVal2;
    u16 seqId;

    for (seqPlayerIndex = 0; seqPlayerIndex < 3; seqPlayerIndex++) {
        if (gSequenceState[seqPlayerIndex].unk_012) {
            volume = 1.0f;
            for (j = 0; j < 3; j++) {
                volume *= gSequenceState[seqPlayerIndex].unk_00E[j] / 127.0f;
            }

            audio_push_cmd(0x40000000 | (((u8) seqPlayerIndex) << 0x18) |
                          (((u8) gSequenceState[seqPlayerIndex].unk_011) << 0x10) | ((u16) (u8) (volume * 127.0f)));

            gSequenceState[seqPlayerIndex].unk_012 = 0;
        }
        if (gSequenceState[seqPlayerIndex].unk_00C != 0) {
            gSequenceState[seqPlayerIndex].unk_00C--;
            if (gSequenceState[seqPlayerIndex].unk_00C) {
                gSequenceState[seqPlayerIndex].unk_000 -= gSequenceState[seqPlayerIndex].unk_008;
            } else {
                gSequenceState[seqPlayerIndex].unk_000 = gSequenceState[seqPlayerIndex].unk_004;
            }
            eu_audio_cmd_send_f32(0x41000000 | (((u32) seqPlayerIndex & 0xFF) << 0x10), gSequenceState[seqPlayerIndex].unk_000);
        }
        if (gSequenceState[seqPlayerIndex].unk_014 != 0) {
            tempoCmd = gSequenceState[seqPlayerIndex].unk_014;
            tempoTimer = (tempoCmd & 0xFF0000) >> 0xF;
            tempoTarget = tempoCmd & 0xFFF;
            if (tempoTimer == 0) {
                tempoTimer++;
            }
            if (gSequencePlayers[seqPlayerIndex].enabled != 0) {
                tempoPrev = gSequencePlayers[seqPlayerIndex].tempo / 48;
                tempoOp = (tempoCmd & 0xF000) >> 0xC;
                switch (tempoOp) {
                    case 1:
                        tempoTarget += tempoPrev;
                        break;

                    case 2:
                        if (tempoTarget < tempoPrev) {
                            tempoTarget = tempoPrev - tempoTarget;
                        }
                        break;

                    case 3:
                        tempoTarget = tempoPrev * (tempoTarget / 100.0f);
                        break;

                    case 4:
                        tempoTarget =
                            (gSequenceState[seqPlayerIndex].unk_018 != 0) ? gSequenceState[seqPlayerIndex].unk_018 : tempoPrev;
                        break;
                    default:
                        break;
                }

                if (tempoTarget > 300) {
                    tempoTarget = 300;
                }
                if (gSequenceState[seqPlayerIndex].unk_018 == 0) {
                    gSequenceState[seqPlayerIndex].unk_018 = tempoPrev;
                }
                gSequenceState[seqPlayerIndex].unk_020 = tempoTarget;
                gSequenceState[seqPlayerIndex].unk_01C = gSequencePlayers[seqPlayerIndex].tempo / 48;
                gSequenceState[seqPlayerIndex].unk_024 =
                    (gSequenceState[seqPlayerIndex].unk_01C - gSequenceState[seqPlayerIndex].unk_020) / tempoTimer;
                gSequenceState[seqPlayerIndex].unk_028 = tempoTimer;
            }
            gSequenceState[seqPlayerIndex].unk_014 = 0;
        }
        if (gSequenceState[seqPlayerIndex].unk_028 != 0) {
            gSequenceState[seqPlayerIndex].unk_028--;
            if (gSequenceState[seqPlayerIndex].unk_028) {
                gSequenceState[seqPlayerIndex].unk_01C -= gSequenceState[seqPlayerIndex].unk_024;
            } else {
                gSequenceState[seqPlayerIndex].unk_01C = gSequenceState[seqPlayerIndex].unk_020;
            }
            eu_audio_cmd_send_u32(0x47000000 | (((u32) seqPlayerIndex & 0xFF) << 0x10),
                          (s32) gSequenceState[seqPlayerIndex].unk_01C);
        }

        if (gSequenceState[seqPlayerIndex].unk_246 != 0) {
            for (channelIndex = 0; channelIndex < 0x10; channelIndex++) {
                if (gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_0C != 0) {
                    gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_0C--;
                    if (gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_0C) {
                        gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_00 -=
                            gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_08;
                    } else {
                        gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_00 =
                            gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_04;
                        gSequenceState[seqPlayerIndex].unk_246 ^= 1 << channelIndex;
                    }
                    eu_audio_cmd_send_f32(0x01000000 | ((seqPlayerIndex & 0xFF) << 0x10) | (((u32) channelIndex & 0xFF) << 8),
                                  gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_00);
                }
            }
        }
        if (gSequenceState[seqPlayerIndex].unk_244 != 0) {
            for (channelIndex = 0; channelIndex < 0x10; channelIndex++) {
                if (gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_1C != 0) {
                    gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_1C--;
                    if (gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_1C) {
                        gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_10 -=
                            gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_18;
                    } else {
                        gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_10 =
                            gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_14;
                        gSequenceState[seqPlayerIndex].unk_244 ^= 1 << channelIndex;
                    }
                    eu_audio_cmd_send_f32(0x04000000 | ((seqPlayerIndex & 0xFF) << 0x10) | (((u32) channelIndex & 0xFF) << 8),
                                  gSequenceState[seqPlayerIndex].unk_044[channelIndex].unk_10);
                }
            }
        }
        if (gSequenceState[seqPlayerIndex].unk_041) {
#ifdef VERSION_EU
            if (audio_is_cmd_not_in_queue_eu(-0x10000000, -0x10000000) == 0) {
                gSequenceState[seqPlayerIndex].unk_041 = 0;
                return;
            }
#endif
            if (gSequenceState[seqPlayerIndex].unk_040 != 0) {
                gSequenceState[seqPlayerIndex].unk_040--;
                continue;
            }

            if (gSequencePlayers[seqPlayerIndex].enabled != 0) {
                continue;
            }

            for (j = 0; j < gSequenceState[seqPlayerIndex].unk_041; j++) {
                setupOp = (gSequenceState[seqPlayerIndex].unk_02C[j] & 0xF00000) >> 0x14;
                targetSeqPlayerIndex = (gSequenceState[seqPlayerIndex].unk_02C[j] & 0xF0000) >> 0x10;
                setupVal2 = (gSequenceState[seqPlayerIndex].unk_02C[j] & 0xFF00) >> 8;
                setupVal1 = gSequenceState[seqPlayerIndex].unk_02C[j] & 0xFF;
                switch (setupOp) {
                    case 0:
                        gSequenceState[targetSeqPlayerIndex].unk_012 = 1;
                        gSequenceState[targetSeqPlayerIndex].unk_00E[1] = 0x7F;
                        break;

                    case 1:
                        audio_push_cmd(0x30000000 | ((u8) seqPlayerIndex) << 0x18 |
                                      (gSequenceState[seqPlayerIndex].unk_248));
                        break;

                    case 2:
                        audio_push_cmd((((u8) targetSeqPlayerIndex) << 0x18) | 0x10000 |
                                      (u16) (gSequenceState[targetSeqPlayerIndex].unk_248));
                        gSequenceState[targetSeqPlayerIndex].unk_012 = 1;
                        gSequenceState[targetSeqPlayerIndex].unk_00E[1] = 0x7F;
                        break;

                    case 3:
                        audio_push_cmd(0xB0003000 | (((u8) targetSeqPlayerIndex) << 0x18) | (((u8) setupVal2) << 0x10) |
                                      (u16) setupVal1);
                        break;

                    case 4:
                        audio_push_cmd(0xB0004000 | (((u8) targetSeqPlayerIndex) << 0x18) | (((u8) setupVal1) << 0x10));
                        break;

                    case 5:
                        seqId = gSequenceState[seqPlayerIndex].unk_02C[j] & 0xFFFF;
                        audio_push_cmd((((u8) targetSeqPlayerIndex) << 0x18) |
                                      (((u8) gSequenceState[targetSeqPlayerIndex].unk_042) << 0x10) | ((u16) seqId));

                        audio_set_sequence_volume(targetSeqPlayerIndex, 1, 0x7F, 0);
                        gSequenceState[targetSeqPlayerIndex].unk_042 = 0;
                        break;

                    case 6:
                        gSequenceState[seqPlayerIndex].unk_042 = setupVal2;
                        break;
                }
            }

            gSequenceState[seqPlayerIndex].unk_041 = 0;
        }
    }
}

void audio_reset_sequence_data(void) {
    u8 var_v0;

    for (var_v0 = 0; var_v0 < 3; var_v0++) {
        gSequenceQueueSize[var_v0] = 0;
        gSequenceState[var_v0].unk_248 = 0xFFFF;
        gSequenceState[var_v0].unk_000 = 1.0f;
        gSequenceState[var_v0].unk_00C = 0;
        gSequenceState[var_v0].unk_028 = 0;
        gSequenceState[var_v0].unk_018 = 0;
        gSequenceState[var_v0].unk_014 = 0;
        gSequenceState[var_v0].unk_24A = 0;
        gSequenceState[var_v0].unk_041 = 0;
        gSequenceState[var_v0].unk_042 = 0;
        gSequenceState[var_v0].unk_012 = 0;
        gSequenceState[var_v0].unk_00E[0] = 0x7F;
        gSequenceState[var_v0].unk_00E[1] = 0x7F;
        gSequenceState[var_v0].unk_00E[2] = 0x7F;
        gSequenceState[var_v0].unk_244 = 0;
        gSequenceState[var_v0].unk_246 = 0;
    }
}

void audio_reset_sequence_data_partial(void) {
    u8 var_v0;

    for (var_v0 = 0; var_v0 < 3; var_v0++) {
        gSequenceQueueSize[var_v0] = 0;
        gSequenceState[var_v0].unk_248 = 0xFFFF;
        gSequenceState[var_v0].unk_028 = 0;
        gSequenceState[var_v0].unk_018 = 0;
        gSequenceState[var_v0].unk_014 = 0;
        gSequenceState[var_v0].unk_24A = 0;
        gSequenceState[var_v0].unk_041 = 0;
        gSequenceState[var_v0].unk_042 = 0;
        gSequenceState[var_v0].unk_244 = 0;
        gSequenceState[var_v0].unk_246 = 0;
    }
}

// Appears to be an unused combo of sound_banks_enable and sound_banks_disable
void audio_set_bank_disabled_mask(u16 bankMask) {
    u8 bank;

    for (bank = 0; bank < SOUND_BANK_COUNT; bank++) {
        if (bankMask & 1) {
            sSoundBankDisabled[bank] = true;
        } else {
            sSoundBankDisabled[bank] = false;
        }
        bankMask = bankMask >> 1;
    }
}

void audio_clear_sequence_mask_bit(u8 arg0) {
    D_800EA1C4 &= ((1 << (arg0)) ^ (u16) -1);
    if (!D_800EA1C4) {
        gSequenceState[0].unk_012 = 1;
        gSequenceState[0].unk_00E[2] = 0x7F;
    }
}

void play_sound(u32 soundBits, Vec3f* position, u8 cameraId, f32* arg3, f32* arg4, s8* arg5) {
    u8 bank;
    struct Sound* temp_v0;

    bank = soundBits >> 0x1C;
    if (sSoundBankDisabled[bank] == false) {
        temp_v0 = &sSoundRequests[sSoundRequestCount];
        temp_v0->soundBits = soundBits;
        temp_v0->position = position;
        temp_v0->cameraId = cameraId;
        temp_v0->unk0C = arg3;
        temp_v0->unk10 = arg4;
        temp_v0->unk14 = arg5;
        sSoundRequestCount += 1;
    }
}

void audio_cancel_sound_requests(u8 arg0, struct SoundCharacteristics* arg1) {
    s32 found;
    u8 soundId;
    struct Sound* sound;

    for (soundId = sNumProcessedSoundRequests; soundId != sSoundRequestCount; soundId++) {
        found = false;
        sound = &sSoundRequests[soundId];
        switch (arg0) {
            case 0:
                if ((sound->soundBits & 0xF0000000) == (arg1->soundBits & 0xF0000000)) {
                    found = true;
                }
                break;
            case 1:
                if (((sound->soundBits & 0xF0000000) == (arg1->soundBits & 0xF0000000)) &&
                    (sound->position == arg1->unk00)) {
                    found = true;
                }
                break;
            case 2:
                if (sound->position == arg1->unk00) {
                    found = true;
                }
                break;
            case 3:
                if ((sound->position == arg1->unk00) && (sound->soundBits == arg1->soundBits)) {
                    found = true;
                }
                break;
            case 4:
                if ((sound->cameraId == arg1->cameraId) && (sound->soundBits == arg1->soundBits)) {
                    found = true;
                }
                break;
            case 5:
                if (sound->soundBits == arg1->soundBits) {
                    found = true;
                }
                break;
        }
        if (found) {
            sound->soundBits = 0;
            if (*sound->position != gAudioDefaultPos) {
                (*sound->position)[1] = 100000.0f;
            }
        }
    }
}

void audio_process_sound_requests(void) {
    u8 bank;
    u8 soundIndex;
    u8 var_a3;
    struct Sound* var_a2;
    UNUSED s32 pad;
    u8 var_t2;
    u32 var_t3;

    var_a2 = &sSoundRequests[sNumProcessedSoundRequests];
    if (var_a2->soundBits == 0) {
        return;
    }

    bank = ((u32) (var_a2->soundBits & 0xF0000000) >> 0x1C);
    soundIndex = sSoundBanks[bank][0].next;
    var_a3 = 0;
    while ((soundIndex != 0xFF) && (soundIndex != 0)) {
        if (var_a2->position == sSoundBanks[bank][soundIndex].unk00) {
            if (var_a2->soundBits == sSoundBanks[bank][soundIndex].soundBits) {
                var_a3 = D_800EA1A0[gAudioNumCameras][bank];
            } else {
                if (var_a3 == 0) {
                    var_t2 = soundIndex;
                    var_t3 = sSoundBanks[bank][soundIndex].soundBits;
                } else if ((u32) (sSoundBanks[bank][soundIndex].soundBits & 0xFF00) < (u32) (var_t3 & 0xFF00)) {
                    var_t2 = soundIndex;
                    var_t3 = sSoundBanks[bank][soundIndex].soundBits;
                }
                var_a3++;
                if (var_a3 == D_800EA1A0[gAudioNumCameras][bank]) {
                    if ((u32) (var_a2->soundBits & 0xFF00) >= (u32) (var_t3 & 0xFF00)) {
                        soundIndex = var_t2;
                    } else {
                        soundIndex = 0;
                    }
                }
            }
            if (var_a3 == D_800EA1A0[gAudioNumCameras][bank]) {
                if ((var_a2->soundBits & 0x08000000) || (var_a2->soundBits & 0x40000) || (soundIndex == var_t2)) {
                    if ((sSoundBanks[bank][soundIndex].soundBits & 0x80000) &&
                        (sSoundBanks[bank][soundIndex].soundStatus != 1)) {
                        audio_clear_sequence_mask_bit(sSoundBanks[bank][soundIndex].unk2C);
                    }
                    sSoundBanks[bank][soundIndex].cameraId = var_a2->cameraId;
                    sSoundBanks[bank][soundIndex].soundBits = var_a2->soundBits;
                    sSoundBanks[bank][soundIndex].soundStatus = ((var_a2->soundBits & 0x01000000) >> 0x18);
                    sSoundBanks[bank][soundIndex].freshness = 2;
                    sSoundBanks[bank][soundIndex].unk10 = var_a2->unk0C;
                    sSoundBanks[bank][soundIndex].unk14 = var_a2->unk10;
                    sSoundBanks[bank][soundIndex].unk18 = var_a2->unk14;
                }
                soundIndex = 0;
            }
        }
        if (soundIndex != 0) {
            soundIndex = sSoundBanks[bank][soundIndex].next;
        }
    }
    if ((sSoundBanks[bank][sSoundBankFreeListFront[bank]].next != 0xFF) && (soundIndex != 0)) {
        var_t2 = soundIndex = sSoundBankFreeListFront[bank];
        sSoundBanks[bank][soundIndex].unk00 = (Vec3f*) &(*var_a2->position)[0];
        sSoundBanks[bank][soundIndex].unk04 = &(*var_a2->position)[1];
        sSoundBanks[bank][soundIndex].unk08 = &(*var_a2->position)[2];
        sSoundBanks[bank][soundIndex].cameraId = var_a2->cameraId;
        sSoundBanks[bank][soundIndex].unk10 = var_a2->unk0C;
        sSoundBanks[bank][soundIndex].unk14 = var_a2->unk10;
        sSoundBanks[bank][soundIndex].unk18 = var_a2->unk14;
        sSoundBanks[bank][soundIndex].soundBits = var_a2->soundBits;
        sSoundBanks[bank][soundIndex].soundStatus = (u8) ((u32) (var_a2->soundBits & 0x01000000) >> 0x18);
        sSoundBanks[bank][soundIndex].freshness = 2;
        sSoundBanks[bank][soundIndex].prev = sSoundBankUsedListBack[bank];
        sSoundBanks[bank][sSoundBankUsedListBack[bank]].next = sSoundBankFreeListFront[bank];
        sSoundBankUsedListBack[bank] = sSoundBankFreeListFront[bank];
        sSoundBankFreeListFront[bank] = sSoundBanks[bank][sSoundBankFreeListFront[bank]].next;
        sSoundBanks[bank][sSoundBankFreeListFront[bank]].prev = 0xFF;
        sSoundBanks[bank][var_t2].next = 0xFF;
    } else if (sSoundBanks[bank][sSoundBankFreeListFront[bank]].next == 0xFF) {
        if (gAudioDefaultPos != *var_a2->position) {
            (*var_a2->position)[1] = 100000.0f;
        }
    }
}

void delete_sound_from_bank(u8 bankId, u8 soundId) {
    UNUSED s32 stackPadding;
    struct SoundCharacteristics* temp = &sSoundBanks[bankId][soundId];
    if (*temp->unk00 != gAudioDefaultPos) {
        *temp->unk04 = 100000.0f;
    }
    if (temp->soundBits & 0x80000) {
        audio_clear_sequence_mask_bit(temp->unk2C);
    }
    if (soundId == sSoundBankUsedListBack[bankId]) {
        sSoundBankUsedListBack[bankId] = temp->prev;
    } else {
        sSoundBanks[bankId][temp->next].prev = temp->prev;
    }
    sSoundBanks[bankId][temp->prev].next = temp->next;
    temp->next = sSoundBankFreeListFront[bankId];
    temp->prev = 0xFF;
    sSoundBanks[bankId][sSoundBankFreeListFront[bankId]].prev = soundId;
    sSoundBankFreeListFront[bankId] = soundId;
    temp->soundStatus = 0;
}

struct ActiveSfx {
    u32 priority;
    u8 soundIndex;
};
#define AUDIO_MK_CMD(b0, b1, b2, b3) \
    ((((b0) & 0xFF) << 0x18) | (((b1) & 0xFF) << 0x10) | (((b2) & 0xFF) << 0x8) | (((b3) & 0xFF) << 0))
void audio_process_sound_requests_for_bank(u8 bankId) {
    u8 j;
    u8 numChannels;
    u8 chosenEntryIndex;
    u8 i;
    u8 k;
    u8 numChosenSfx;
    u8 needNewSfx;
    u8 soundIndex;
    u8 requestedPriority;
    u8 temp_t8;
    f32 var_f0;
    struct ActiveSfx* activeSfx;
    struct ActiveSfx chosenSfx[8];
    struct SoundCharacteristics* entry;

    numChosenSfx = 0;
    for (i = 0; i < 8; i++) {
        chosenSfx[i].priority = 0x7FFFFFFF;
        chosenSfx[i].soundIndex = 0xFF;
    }

    soundIndex = sSoundBanks[bankId][0].next;
    k = 0;
    while (soundIndex != 0xFF) {
        if ((sSoundBanks[bankId][soundIndex].soundStatus == 1) &&
            ((sSoundBanks[bankId][soundIndex].soundBits & 0x08000000) == 0x08000000)) {
            sSoundBanks[bankId][soundIndex].freshness -= 1;
        }

        if (sSoundBanks[bankId][soundIndex].freshness == 0) {
            delete_sound_from_bank(bankId, soundIndex);
        } else if (sSoundBanks[bankId][soundIndex].soundStatus != 0) {
            entry = &sSoundBanks[bankId][soundIndex];

            if (&gAudioDefaultPos == entry[0].unk00) {
                entry->distance = 0.0f;
            } else {
                entry->distance = (*entry->unk00[0] * *entry->unk00[0]) + (*entry->unk08 * *entry->unk08);
            }
            requestedPriority = (((u32) (entry->soundBits & 0xFF00)) >> 8);
            if (entry->soundBits & 0x100000) {
                entry->priority = ((0xFF - requestedPriority) * (0xFF - requestedPriority)) * (38 * 38);
            } else {
                entry->priority =
                    ((u32) entry->distance) + (((0xFF - requestedPriority) * (0xFF - requestedPriority)) * (38 * 38));

                if ((*entry->unk08) > 0.0f) {
                    entry->priority += (s32) ((*entry->unk08) * 6.0f);
                }
            }
            temp_t8 = (((u32) (entry->soundBits & 0x30000)) >> 0x10);
            if (temp_t8) {
                var_f0 = (2000.0f * 2000.0f) / ((f32) (temp_t8 * temp_t8));
            } else {
                var_f0 = 1e5f * 1e5f;
            }
            if (var_f0 < entry->distance) {
                if (entry->soundStatus == 4) {
                    eu_audio_cmd_send_byte(AUDIO_MK_CMD(0x06, 2, entry->unk2C, 0), 0);
                    if (entry->soundBits & 0x08000000) {
                        delete_sound_from_bank(bankId, soundIndex);
                        soundIndex = k;
                    }
                }
            } else {
                numChannels = gAudioNumChannelsPerBank[gAudioNumCameras][bankId];
                for (i = 0; i < numChannels; i++) {
                    if (chosenSfx[i].priority >= entry->priority) {
                        if (numChosenSfx < gAudioNumChannelsPerBank[gAudioNumCameras][bankId]) {
                            numChosenSfx++;
                        }
                        for (j = numChannels - 1; j > i; j--) {
                            chosenSfx[j].priority = chosenSfx[j - 1].priority;
                            chosenSfx[j].soundIndex = chosenSfx[j - 1].soundIndex;
                        }

                        chosenSfx[i].priority = entry->priority;
                        chosenSfx[i].soundIndex = soundIndex;
                        i = numChannels;
                    }
                }
            }
            k = soundIndex;
        }
        soundIndex = sSoundBanks[bankId][k].next;
    }

    numChannels = gAudioNumChannelsPerBank[gAudioNumCameras][bankId];
    for (i = 0; i < numChosenSfx; i++) {
        if (sSoundBanks[bankId][chosenSfx[i].soundIndex].soundStatus == 1) {
            sSoundBanks[bankId][chosenSfx[i].soundIndex].soundStatus = 2;
        } else if (sSoundBanks[bankId][chosenSfx[i].soundIndex].soundStatus == 4) {
            sSoundBanks[bankId][chosenSfx[i].soundIndex].soundStatus = 3;
        }
    }

    for (i = 0; i < numChannels; i++) {
        needNewSfx = false;
        activeSfx = (struct ActiveSfx*) &gActiveSfx[bankId][i];

        if (activeSfx->soundIndex == 0xFF) {
            needNewSfx = true;
        } else {
            entry = &sSoundBanks[bankId][activeSfx->soundIndex];
            if (entry->soundStatus == 4) {
                if (entry->soundBits & 0x08000000) {
                    delete_sound_from_bank(bankId, activeSfx->soundIndex);
                } else {
                    entry->soundStatus = 1;
                }
                needNewSfx = true;
            } else if (entry->soundStatus == 0) {
                activeSfx->soundIndex = 0xFF;
                needNewSfx = true;
            } else {
                for (j = 0; j < numChannels; j++) {
                    if (activeSfx->soundIndex == chosenSfx[j].soundIndex) {
                        chosenSfx[j].soundIndex = 0xFF;
                        j = numChannels;
                    }
                }
                numChosenSfx--;
            }
        }

        if (needNewSfx == true) {
            for (j = 0; j < numChannels; j++) {
                chosenEntryIndex = chosenSfx[j].soundIndex;
                if ((chosenEntryIndex != 0xFF) && (sSoundBanks[bankId][chosenEntryIndex].soundStatus != 3)) {
                    for (k = 0; k < numChannels; k++) {
                        if (chosenEntryIndex == ((struct ActiveSfx*) (gActiveSfx[bankId]))[k].soundIndex) {
                            needNewSfx = false;
                            k = numChannels;
                        }
                    }

                    if (needNewSfx == true) {
                        activeSfx->soundIndex = chosenEntryIndex;
                        chosenSfx[j].soundIndex = 0xFF;
                        j = numChannels + 1;
                        numChosenSfx--;
                    }
                }
            }

            if (j == numChannels) {
                activeSfx->soundIndex = 0xFF;
            }
        }
    }
}

void audio_play_sound_requests(u8 bankId) {
    u8 soundId;
    u8 var_s4;
    UNUSED u32 cmd;
    struct SoundCharacteristics* temp_s0;
    struct SequenceChannel* thing;

    for (var_s4 = 0; var_s4 < gAudioNumChannelsPerBank[gAudioNumCameras][bankId]; var_s4++) {
        soundId = gActiveSfx[bankId][var_s4][4];
        if (soundId != 0xFF) {
            temp_s0 = &sSoundBanks[bankId][soundId];
            thing = gSequencePlayers[2].channels[gSfxChannelIndex];
            if (temp_s0->soundStatus == 2) {
                temp_s0->unk2C = gSfxChannelIndex;
                if (temp_s0->soundBits & 0x80000) {
                    D_800EA1C4 |= 1 << gSfxChannelIndex;
                    gSequenceState->unk_012 = 1;
                    gSequenceState->unk_00E[2] = 0x28;
                }
                audio_update_sound_params(bankId, soundId, gSfxChannelIndex);
                eu_audio_cmd_send_byte(((gSfxChannelIndex & 0xFF) << 8) | 0x06020000, 1);
                eu_audio_cmd_send_byte(((gSfxChannelIndex & 0xFF) << 8) | 0x06020000 | 4, (u8) (temp_s0->soundBits & 0xFF));
                temp_s0->soundStatus = 4U;
            } else if (((u8) thing->soundScriptIO[7]) == 0x80) {
                eu_audio_cmd_send_byte(((gSfxChannelIndex & 0xFF) << 8) | 0x06020000 | 7, 0);
                delete_sound_from_bank(bankId, soundId);
            } else if (temp_s0->soundStatus == 3) {
                audio_update_sound_params(bankId, soundId, gSfxChannelIndex);
                temp_s0->soundStatus = 4U;
            }
        }
        gSfxChannelIndex += 1;
    }
}

// Seems somewhat similar to certain parts of `select_current_sounds` from SM64
void audio_stop_all_sounds_in_bank(u8 bankId) {
    UNUSED s32 stackPadding0;
    u8 soundId;
    struct SoundCharacteristics sp60;

    soundId = sSoundBanks[bankId][0].next;
    while (soundId != 0xFF) {
        if (sSoundBanks[bankId][soundId].soundStatus >= 3) {
            eu_audio_cmd_send_byte(((sSoundBanks[bankId][soundId].unk2C & 0xff) << 8) | 0x06020000, 0);
        }
        if (sSoundBanks[bankId][soundId].soundStatus != 0) {
            delete_sound_from_bank(bankId, soundId);
        }
        // This feels wrong, I think it only works because `delete_sound_from_bank`
        // modifies `sSoundBanks[bankId][0].next`, which allows us to eventually(?)
        // break out of the loop
        soundId = sSoundBanks[bankId][0].next;
    }
    sp60.soundBits = bankId << 0x1C;
    audio_cancel_sound_requests(0, &sp60);
}

void audio_stop_sounds_in_bank_by_pos(u8 arg0, Vec3f* arg1) {
    u8 curr;
    u8 next;

    curr = 0;
    next = sSoundBanks[arg0][0].next;

    while (next != 0xff) {
        if (*arg1 == *sSoundBanks[arg0][next].unk00) {
            if (sSoundBanks[arg0][next].soundStatus >= 3) {
                eu_audio_cmd_send_byte((0x06020000 | ((sSoundBanks[arg0][next].unk2C & 0xff) << 8)), 0);
            }

            if (sSoundBanks[arg0][next].soundStatus != 0) {
                delete_sound_from_bank(arg0, next);
            }
        } else {
            curr = next;
        }

        next = sSoundBanks[arg0][curr].next;
    }
}

void audio_stop_sounds_and_requests_in_bank_by_pos(u8 arg0, Vec3f* arg1) {
    struct SoundCharacteristics unk;
    audio_stop_sounds_in_bank_by_pos(arg0, arg1);
    unk.soundBits = arg0 << 0x1C;
    unk.unk00 = arg1;
    audio_cancel_sound_requests(1, &unk);
}

void audio_stop_all_sounds_and_requests_by_pos(Vec3f* arg0) {
    u8 i;
    struct SoundCharacteristics sp3C;

    for (i = 0; i < 6; i++) {
        audio_stop_sounds_in_bank_by_pos(i, arg0);
    }

    sp3C.unk00 = arg0;
    audio_cancel_sound_requests(2, &sp3C);
}

void audio_stop_sound_and_request_by_pos_and_id(Vec3f* arg0, u32 soundBits) {
    UNUSED s32 stackPadding0;
    u8 bankId;
    u8 next;
    u8 curr;
    struct SoundCharacteristics sp60;

    bankId = (soundBits & 0xF0000000) >> 0x1C;
    next = sSoundBanks[bankId][0].next;
    curr = 0;
    while (next != 0xFF) {
        if ((arg0 == sSoundBanks[bankId][next].unk00) && (soundBits == sSoundBanks[bankId][next].soundBits)) {
            if (sSoundBanks[bankId][next].soundStatus >= 3) {
                eu_audio_cmd_send_byte(((sSoundBanks[bankId][next].unk2C & 0xff) << 8) | 0x06020000, 0);
            }
            if (sSoundBanks[bankId][next].soundStatus != 0) {
                delete_sound_from_bank(bankId, next);
            }
            next = 0xFF;
        } else {
            curr = next;
        }
        if (next != 0xFF) {
            next = sSoundBanks[bankId][curr].next;
        }
    }
    sp60.unk00 = arg0;
    sp60.soundBits = soundBits;
    audio_cancel_sound_requests(3, &sp60);
}

void audio_stop_sound_and_request_by_id(u32 soundBits) {
    UNUSED s32 stackPadding0;
    u8 bankId;
    u8 next;
    u8 curr;
    struct SoundCharacteristics sp68;

    bankId = (soundBits & 0xF0000000) >> 0x1C;
    next = sSoundBanks[bankId][0].next;
    curr = 0;
    while (next != 0xFF) {
        if (soundBits == sSoundBanks[bankId][next].soundBits) {
            if (sSoundBanks[bankId][next].soundStatus >= 3) {
                eu_audio_cmd_send_byte(((sSoundBanks[bankId][next].unk2C & 0xff) << 8) | 0x06020000, 0);
            }
            if (sSoundBanks[bankId][next].soundStatus != 0) {
                delete_sound_from_bank(bankId, next);
            }
        } else {
            curr = next;
        }
        next = sSoundBanks[bankId][curr].next;
    }
    sp68.soundBits = soundBits;
    audio_cancel_sound_requests(5, &sp68);
}

// Might be process_all_sound_requests
void audio_process_all_sound_requests(void) {
    while (sSoundRequestCount != sNumProcessedSoundRequests) {
        audio_process_sound_requests();
        sNumProcessedSoundRequests++;
    }
}

// EXTREMELY similar to `fade_channel_volume_scale` from SM64
void fade_channel_volume_scale(u8 player, u8 targetScale, u16 fadeDuration) {
    struct ChannelVolumeScaleFade* temp_v0;

    if (fadeDuration == 0) {
        fadeDuration++;
    }
    temp_v0 = &gChannelVolumeScaleFade[player];
    temp_v0->target = targetScale / US_FLOAT(127.0);
    temp_v0->remainingFrames = fadeDuration;
    temp_v0->velocity = (temp_v0->current - temp_v0->target) / fadeDuration;
}

void audio_process_channel_volume_fade(u8 arg0) {
    struct ChannelVolumeScaleFade* temp_v0;

    temp_v0 = &gChannelVolumeScaleFade[arg0];
    if (temp_v0->remainingFrames != 0) {
        temp_v0->remainingFrames--;
        if (temp_v0->remainingFrames != 0) {
            temp_v0->current -= temp_v0->velocity;
        } else {
            temp_v0->current = temp_v0->target;
        }
    }
}

void audio_process_sound_banks(void) {
    u8 i;

    if (gSequencePlayers[2].channels[0] != &gSequenceChannelNone) {
        gSfxChannelIndex = 0;
        for (i = 0; i < 6; i++) {
            audio_process_sound_requests_for_bank(i);
            audio_play_sound_requests(i);
            audio_process_channel_volume_fade(i);
        }
    }
}

// Looks EXTEREMELY similar to sound_init from SM64
void sound_init(void) {
    u8 var_v0;
    u8 var_v1;

    sSoundRequestCount = 0;
    sNumProcessedSoundRequests = 0;
    D_800EA1C4 = 0;
    for (var_v0 = 0; var_v0 < SOUND_BANK_COUNT; var_v0++) {
        sSoundBankUsedListBack[var_v0] = 0;
        sSoundBankFreeListFront[var_v0] = 1;
        sNumSoundsInBank[var_v0] = 0;
        sSoundBankDisabled[var_v0] = false;
        gChannelVolumeScaleFade[var_v0].current = 1.0f;
        gChannelVolumeScaleFade[var_v0].remainingFrames = 0;
    }
    for (var_v0 = 0; var_v0 < 6; var_v0++) {
        for (var_v1 = 0; var_v1 < 8; var_v1++) {
            gActiveSfx[var_v0][var_v1][4] = 0xFF;
        }
    }
    for (var_v0 = 0; var_v0 < 6; var_v0++) {
        sSoundBanks[var_v0][0].prev = 0xFF;
        sSoundBanks[var_v0][0].next = 0xFF;
        for (var_v1 = 1; var_v1 < 19; var_v1++) {
            sSoundBanks[var_v0][var_v1].prev = var_v1 - 1;
            sSoundBanks[var_v0][var_v1].next = var_v1 + 1;
        }
        sSoundBanks[var_v0][var_v1].prev = var_v1 - 1;
        sSoundBanks[var_v0][var_v1].next = 0xFF;
    }
}

void audio_send_character_voice_cmd(void) {
    if (gAudioNumCameras == 0) {
        eu_audio_cmd_send_byte(((D_800EA154[gPlayers[0].characterId] & 0xFFFF) << 8) | 0xF3000000, 0);
    } else {
        eu_audio_cmd_send_byte(0xF3004D00, 0);
    }
}

void audio_reset_session(void) {
    audio_init_cameras_and_state();
    if (gHasAudioInitialized != 0) {
        audio_reset_sequence_data_partial();
    } else {
        gHasAudioInitialized++;
        audio_reset_sequence_data();
    }
    sound_init();
    audio_cmd_play_sequence(2, 0, 0xFF, 1);
    audio_send_character_voice_cmd();
}

// game_audio_init?
void audio_init(void) {
    audio_init_cameras_and_state();
    audio_reset_sequence_data();
    sound_init();
    audio_cmd_play_sequence(2, 0, 0xFF, 1);
}

void audio_update_throttle_state(u8 playerId) {
    if ((gPlayers[playerId].kartProps & THROTTLE) == THROTTLE) {
        D_800E9E34[playerId] = 0;
        if (D_800E9E24[playerId] < 0x4E20) {
            if ((u8) D_800EA16C == 0) {
                D_800E9E24[playerId]++;
            }
        }
        if (D_800E9E24[playerId] == 1) {
            switch (D_800EA0EC[playerId]) {
                case 2:
                    D_800EA0EC[playerId] = 1;
                case 0:
                    audio_stop_character_sounds(playerId);
                    audio_play_character_engine_sound(playerId);
                    break;
                default:
                    break;
            }
        }
    } else {
        D_800E9E24[playerId] = 0;
        if ((D_800E9E34[playerId] < 0x4E20) && ((u8) D_800EA16C == 0)) {
            D_800E9E34[playerId]++;
        }
    }
}

void audio_update_throttle_sound_state(u8 playerId) {
    if (D_800EA108 == 0) {
        if (((gPlayers[playerId].kartProps & THROTTLE) != THROTTLE) && (gPlayers[playerId].unk_098 > 400.0f)) {
            D_800E9E14[playerId] = 1;
            if (D_800EA0EC[playerId] == 0) {
                gAudioCharacterStates[playerId].unk_10 = 0.6f - D_800E9F54[playerId];
            }
            D_800E9DC4[playerId] = gAudioCharacterStates[playerId].unk_30;
            D_800E9DD4[playerId] = gAudioCharacterStates[playerId].unk_24;
            if ((D_800E9E34[playerId] == 1) && ((u8) D_800EA16C == 0)) {
                switch (D_800EA0EC[playerId]) {
                    case 2:
                        D_800EA0EC[playerId] = 1;
                    case 0:
                        if ((D_800E9F74[playerId] == 0) && (gPlayers[playerId].characterId != 3)) {
                            if ((s32) gAudioNumCameras < 2) {
                                play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF9, 0x26), &gAudioCharacterStates[playerId].pos, playerId,
                                           &gAudioCharacterStates[playerId].unk_38, &D_800E9F04[playerId],
                                           (s8*) &gAudioCharacterStates[playerId].unk_14);
                            } else {
                                play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0x80, 0x26), &gAudioCharacterStates[playerId].pos, playerId,
                                           &gAudioCharacterStates[playerId].unk_38, &D_800E9F04[playerId],
                                           (s8*) &gAudioCharacterStates[playerId].unk_14);
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        } else {
            if (D_800E9E24[playerId] == 0x0000000A) {
                if ((s32) gAudioNumCameras < 2) {
                    audio_stop_player_sound(playerId, SOUND_ARG_LOAD(0x01, 0x00, 0xF9, 0x26));
                } else {
                    audio_stop_player_sound(playerId, SOUND_ARG_LOAD(0x01, 0x00, 0x80, 0x26));
                }
            }
            D_800E9E14[playerId] = 0;
            gAudioCharacterStates[playerId].unk_10 = (1.0f - D_800E9F54[playerId]) - D_800EA130[playerId];
            if ((1.0f - D_800E9F54[playerId]) < D_800EA130[playerId]) {
                gAudioCharacterStates[playerId].unk_10 = 0.0f;
            }
            D_800E9DC4[playerId] = gAudioCharacterStates[playerId].unk_2C;
            D_800E9DD4[playerId] = gAudioCharacterStates[playerId].unk_20;
        }
    }
}

void audio_update_throttle_sound_pitch(u8 playerId) {
    Player* player;

    player = &gPlayers[playerId];
    D_800E9E64[playerId] = (player->unk_098 / D_800E9DC4[playerId]) + D_800E9DD4[playerId];
    if ((player->unk_098 < 1800.0f) && ((player->kartProps & THROTTLE) != THROTTLE)) {
        D_800E9E64[playerId] = (player->unk_098 / gAudioCharacterStates[playerId].unk_34) + gAudioCharacterStates[playerId].unk_28;
        if (D_800E9EC4) {} // ?
    }
    if (player->speed > 4.75f) {
        if (D_800E9EB4[playerId] < (gAudioCharacterStates[playerId].unk_18 + 0.4f)) {
            D_800E9DE4[playerId] += 0.005f;
        }
    } else {
        D_800E9DE4[playerId] = 0.0f;
    }
    if (gPlayers[playerId].unk_0C0 > 0) {
        D_800E9E54[playerId] = (f32) player->unk_0C0;
    } else {
        D_800E9E54[playerId] = (f32) -player->unk_0C0;
    }
    if ((player->effects & DRIFTING_EFFECT) == DRIFTING_EFFECT) {
        D_800E9EB4[playerId] = D_800E9E64[playerId] + D_800E9DE4[playerId];
    } else {
        D_800E9EB4[playerId] = D_800E9E64[playerId] + D_800E9DE4[playerId] - (D_800E9E54[playerId] / 12000.0f);
        if (D_800E9EB4[playerId] < 0.01f) {
            D_800E9EB4[playerId] = 0.01f;
        }
    }
    if ((D_800E9F74[playerId]) || (D_800E9F78[playerId])) {
        if (D_800E9F74[playerId]) {
            if (D_800E9F78[playerId] < 0xF) {
                D_800E9F78[playerId]++;
                D_800E9DF4[playerId] += 0.03f;
            }
        } else if (D_800E9F78[playerId]) {
            D_800E9F78[playerId]--;
            D_800E9DF4[playerId] -= 0.03f;
        }
        D_800E9EB4[playerId] -= D_800E9DF4[playerId];
    }
    D_800E9EE4[playerId] = D_800E9EB4[playerId] - D_800E9EC4[playerId];
#ifdef VERSION_EU
    if ((D_800E9EE4[playerId] > 0.5f) || (D_800E9EE4[playerId] < -0.5f))
#else
    if ((D_800E9EE4[playerId] > 0.5f) || (D_800E9EE4[playerId] < 0.5f))
#endif
    {
        D_800E9ED4[playerId] = D_800E9EE4[playerId] * 0.25f;
        gAudioCharacterStates[playerId].unk_0C = D_800E9EC4[playerId] + D_800E9ED4[playerId] + D_800E9F34[playerId];
    } else {
        gAudioCharacterStates[playerId].unk_0C = D_800E9EB4[playerId] + D_800E9F34[playerId];
    }
#ifdef VERSION_EU
    if (gAudioCharacterStates[playerId].unk_0C < 0.0f) {
        gAudioCharacterStates[playerId].unk_0C = 0.0f;
    }
#endif
    if (gAudioCharacterStates[playerId].unk_0C > 4.0f) {
        gAudioCharacterStates[playerId].unk_0C = 4.0f;
    }
    D_800E9EC4[playerId] = gAudioCharacterStates[playerId].unk_0C;
    gAudioCharacterStates[playerId].unk_38 = (gAudioCharacterStates[playerId].unk_0C / 1.5f) + 0.4f;
}

void audio_update_throttle_sound_volume(u8 playerId) {
    switch (D_800E9E74[playerId]) {
        case 3:
            D_800E9EF4[playerId] = (gPlayers[playerId].speed / 5.0f) + 0.2f;
            break;
        case 1:
        case 13:
        case 14:
        case 17:
            D_800E9EF4[playerId] = ((D_800E9E54[playerId] - 3500.0f) / 3000.0f) + 0.4f;
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 22:
        case 23:
        case 24:
        case 29:
        case 30:
        case 31:
            D_800E9EF4[playerId] = (gPlayers[playerId].speed / 5.0f) + 0.2f;
            break;
        default:
            D_800E9EF4[playerId] = 1.0f;
            break;
    }
    if (D_800E9EF4[playerId] > 1.0f) {
        D_800E9EF4[playerId] = 1.0f;
    }
    if (D_800E9EF4[playerId] < 0.0f) {
        D_800E9EF4[playerId] = 0.0f;
    }
    if ((gPlayers[playerId].kartProps & THROTTLE) == THROTTLE) {
        D_800E9F04[playerId] = 0.56f - (D_800E9E24[playerId] * 0.06f);
    } else {
        D_800E9F04[playerId] = (D_800E9E34[playerId] / 50.0f) + 0.25f;
    }
    if (D_800E9F24[playerId] != 0) {
        D_800E9F04[playerId] = 0.0f;
    }
    if (D_800E9F04[playerId] > 0.9f) {
        D_800E9F04[playerId] = 0.9f;
    }
}

void audio_update_throttle_sound_speed(u8 playerId) {
    switch (D_800E9E74[playerId]) { /* irregular */
        case 3:
            D_800E9F14[playerId] = (gPlayers[playerId].speed / 9.0f) + 0.6f;
            break;
        case 2:
        case 13:
        case 17:
            D_800E9F14[playerId] = (D_800E9E54[playerId] / 13000.0f) + 0.95f;
            break;
        default:
            D_800E9F14[playerId] = 1.0f;
            break;
    }
}

void audio_update_throttle_sound_type(u8 cameraId) {
    if ((D_800EA108 == 0) && (D_800EA0EC[cameraId] == 0)) {
        if (D_800E9E74[cameraId] != D_800E9E84[cameraId]) {
            audio_stop_sound_and_request_by_pos_and_id(&gAudioCharacterStates[cameraId].pos, D_800E9E94[cameraId]);
            switch (D_800E9E74[cameraId]) {
                case 3:
                    play_sound(SOUND_ACTION_TYRE_SQUEAL, &gAudioCharacterStates[cameraId].pos, cameraId, &D_800E9F14[cameraId],
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ACTION_TYRE_SQUEAL;
                    break;
                case 18:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF8, 0x1D), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &gAudioOneFloat, (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF8, 0x1D);
                    break;
                case 19:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF8, 0x22), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &gAudioOneFloat, (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF8, 0x22);
                    break;
                case 1:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x09), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x09);
                    break;
                case 2:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF4, 0x0A), &gAudioCharacterStates[cameraId].pos, cameraId,
                               &D_800E9F14[cameraId], &gAudioOneFloat, (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF4, 0x0A);
                    break;
                case 17:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x1E), &gAudioCharacterStates[cameraId].pos, cameraId,
                               &D_800E9F14[cameraId], &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x1E);
                    break;
                case 15:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x1F), &gAudioCharacterStates[cameraId].pos, cameraId,
                               &D_800E9F14[cameraId], &gAudioOneFloat, (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x1F);
                    break;
                case 16:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x21), &gAudioCharacterStates[cameraId].pos, cameraId,
                               &D_800E9F14[cameraId], &gAudioOneFloat, (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x21);
                    break;
                case 20:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x27), &gAudioCharacterStates[cameraId].pos, cameraId,
                               &D_800E9F14[cameraId], &gAudioOneFloat, (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x27);
                    break;
                case 25:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x20), &gAudioCharacterStates[cameraId].pos, cameraId,
                               &D_800E9F14[cameraId], &gAudioOneFloat, (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x20);
                    break;
                case 26:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x23), &gAudioCharacterStates[cameraId].pos, cameraId,
                               &D_800E9F14[cameraId], &gAudioOneFloat, (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x23);
                    break;
                case 27:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0x80, 0x46), &gAudioCharacterStates[cameraId].pos, cameraId,
                               &D_800E9F14[cameraId], &gAudioOneFloat, (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0x80, 0x46);
                    break;
                case 28:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x25), &gAudioCharacterStates[cameraId].pos, cameraId,
                               &D_800E9F14[cameraId], &gAudioOneFloat, (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x25);
                    break;
                case 4:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x0B), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x0B);
                    break;
                case 5:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x0C), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x0C);
                    break;
                case 6:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x0D), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x0D);
                    break;
                case 7:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x0E), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x0E);
                    break;
                case 8:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x0F), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x0F);
                    break;
                case 9:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x10), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x10);
                    break;
                case 10:
                case 14:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x11), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x11);
                    break;
                case 11:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x12), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x12);
                    break;
                case 12:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x13), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x13);
                    break;
                case 29:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x48), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x48);
                    break;
                case 30:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x49), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x49);
                    break;
                case 31:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x4A), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x4A);
                    break;
                case 13:
                case 22:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x29), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x29);
                    break;
                case 23:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x2A), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x2A);
                    break;
                case 24:
                    play_sound(SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x2B), &gAudioCharacterStates[cameraId].pos, cameraId, &gAudioOneFloat,
                               &D_800E9EF4[cameraId], (s8*) &gAudioCharacterStates[cameraId].unk_14);
                    D_800E9E94[cameraId] = SOUND_ARG_LOAD(0x01, 0x00, 0xF0, 0x2B);
                    break;
                default:
                    audio_stop_sound_and_request_by_pos_and_id(&gAudioCharacterStates[cameraId].pos, D_800E9E94[cameraId]);
                    break;
            }
        }
        D_800E9E84[cameraId] = D_800E9E74[cameraId];
    }
}

void audio_update_surface_sound(u8 playerId) {
    if (D_800EA0EC[playerId] == 0) {
        D_800E9E74[playerId] = 0;
        if ((D_800E9E54[playerId] > 3500.0f) || ((gPlayers[playerId].effects & DRIFTING_EFFECT) == DRIFTING_EFFECT)) {
            D_800E9E74[playerId] = 1;
            switch (gPlayers[playerId].tyres[AUDIO_LEFT_TYRE].surfaceType) {
                case DIRT: /* switch 1 */
                    D_800E9E74[playerId] = 0x0000000D;
                    break;
                case SAND: /* switch 1 */
                    D_800E9E74[playerId] = 0x0000000E;
                    break;
                case BRIDGE: /* switch 1 */
                    D_800E9E74[playerId] = 0x00000011;
                    break;
                case STONE: /* switch 1 */
                    D_800E9E74[playerId] = 0x0000000F;
                    break;
                case SNOW: /* switch 1 */
                    D_800E9E74[playerId] = 0x00000010;
                    break;
                case ICE: /* switch 1 */
                    D_800E9E74[playerId] = 0x00000014;
                    break;
                case ROPE_BRIDGE: /* switch 1 */
                    D_800E9E74[playerId] = 0x00000019;
                    break;
                case WOOD_BRIDGE: /* switch 1 */
                    D_800E9E74[playerId] = 0x0000001A;
                    break;
                case TRAIN_TRACK: /* switch 1 */
                    D_800E9E74[playerId] = 0x0000001B;
                    break;
            }
        }
        if ((gPlayers[playerId].effects & DRIFTING_EFFECT) == DRIFTING_EFFECT) {
            D_800E9E74[playerId] = 2;
            switch (gPlayers[playerId].tyres[AUDIO_LEFT_TYRE].surfaceType) { /* switch 2 */
                case DIRT:                                                   /* switch 2 */
                    D_800E9E74[playerId] = 0x0000000D;
                    break;
                case SAND: /* switch 2 */
                    D_800E9E74[playerId] = 0x0000000E;
                    break;
                case BRIDGE: /* switch 2 */
                    D_800E9E74[playerId] = 0x00000011;
                    break;
                case STONE: /* switch 2 */
                    D_800E9E74[playerId] = 0x0000000F;
                    break;
                case SNOW: /* switch 2 */
                    D_800E9E74[playerId] = 0x00000010;
                    break;
                case ICE: /* switch 2 */
                    D_800E9E74[playerId] = 0x00000014;
                    break;
                case ROPE_BRIDGE: /* switch 2 */
                    D_800E9E74[playerId] = 0x00000019;
                    break;
                case WOOD_BRIDGE: /* switch 2 */
                    D_800E9E74[playerId] = 0x0000001A;
                    break;
                case TRAIN_TRACK: /* switch 2 */
                    D_800E9E74[playerId] = 0x0000001B;
                    break;
            }
        }
        switch (gPlayers[playerId].tyres[AUDIO_LEFT_TYRE].surfaceType) { /* switch 3 */
            case GRASS:                                                  /* switch 3 */
                if (D_800E9E74[playerId] == 6) {
                    D_800E9E74[playerId] = 4;
                } else if (gAudioNumCameras == 0) {
                    D_800E9E74[playerId] = 5;
                } else {
                    D_800E9E74[playerId] = 4;
                }
                break;
            case SAND_OFFROAD: /* switch 3 */
                if (D_800E9E74[playerId] == 0x0000000C) {
                    D_800E9E74[playerId] = 0x0000000A;
                } else if (gAudioNumCameras == 0) {
                    D_800E9E74[playerId] = 0x0000000B;
                } else {
                    D_800E9E74[playerId] = 0x0000000A;
                }
                break;
            case DIRT_OFFROAD: /* switch 3 */
                if (D_800E9E74[playerId] == 0x00000018) {
                    D_800E9E74[playerId] = 0x00000016;
                } else if (gAudioNumCameras == 0) {
                    D_800E9E74[playerId] = 0x00000017;
                } else {
                    D_800E9E74[playerId] = 0x00000016;
                }
                break;
            case SNOW_OFFROAD: /* switch 3 */
                if (D_800E9E74[playerId] == 0x0000001F) {
                    D_800E9E74[playerId] = 0x0000001D;
                } else if (gAudioNumCameras == 0) {
                    D_800E9E74[playerId] = 0x0000001E;
                } else {
                    D_800E9E74[playerId] = 0x0000001D;
                }
                break;
            case WET_SAND: /* switch 3 */
                if (D_800E9F74[playerId] == 0) {
                    if (D_800E9E74[playerId] == 9) {
                        D_800E9E74[playerId] = 7;
                    } else if (gAudioNumCameras == 0) {
                        D_800E9E74[playerId] = 8;
                    } else {
                        D_800E9E74[playerId] = 7;
                    }
                } else {
                    D_800E9E74[playerId] = 0x0000001C;
                }
                break;
            case ROPE_BRIDGE: /* switch 3 */
                D_800E9E74[playerId] = 0x00000019;
                break;
            case WOOD_BRIDGE: /* switch 3 */
                D_800E9E74[playerId] = 0x0000001A;
                break;
            case TRAIN_TRACK: /* switch 3 */
                D_800E9E74[playerId] = 0x0000001B;
                break;
        }
        switch (gPlayers[playerId].tyres[AUDIO_RIGHT_TYRE].surfaceType) { /* switch 4 */
            case GRASS:                                                   /* switch 4 */
                if (D_800E9E74[playerId] == 5) {
                    D_800E9E74[playerId] = 4;
                } else if (gAudioNumCameras == 0) {
                    D_800E9E74[playerId] = 6;
                } else {
                    D_800E9E74[playerId] = 4;
                }
                break;
            case SAND_OFFROAD: /* switch 4 */
                if (D_800E9E74[playerId] == 0x0000000B) {
                    D_800E9E74[playerId] = 0x0000000A;
                } else if (gAudioNumCameras == 0) {
                    D_800E9E74[playerId] = 0x0000000C;
                } else {
                    D_800E9E74[playerId] = 0x0000000A;
                }
                break;
            case DIRT_OFFROAD: /* switch 4 */
                if (D_800E9E74[playerId] == 0x00000017) {
                    D_800E9E74[playerId] = 0x00000016;
                } else if (gAudioNumCameras == 0) {
                    D_800E9E74[playerId] = 0x00000018;
                } else {
                    D_800E9E74[playerId] = 0x00000016;
                }
                break;
            case SNOW_OFFROAD: /* switch 4 */
                if (D_800E9E74[playerId] == 0x0000001E) {
                    D_800E9E74[playerId] = 0x0000001D;
                } else if (gAudioNumCameras == 0) {
                    D_800E9E74[playerId] = 0x0000001F;
                } else {
                    D_800E9E74[playerId] = 0x0000001D;
                }
                break;
            case WET_SAND: /* switch 4 */
                if (D_800E9F74[playerId] == 0) {
                    if (D_800E9E74[playerId] == 8) {
                        D_800E9E74[playerId] = 7;
                    } else if (gAudioNumCameras == 0) {
                        D_800E9E74[playerId] = 9;
                    } else {
                        D_800E9E74[playerId] = 7;
                    }
                } else {
                    D_800E9E74[playerId] = 0x0000001C;
                }
                break;
            case ROPE_BRIDGE: /* switch 4 */
                D_800E9E74[playerId] = 0x00000019;
                break;
            case WOOD_BRIDGE: /* switch 4 */
                D_800E9E74[playerId] = 0x0000001A;
                break;
            case TRAIN_TRACK: /* switch 4 */
                D_800E9E74[playerId] = 0x0000001B;
                break;
        }
        if (((gPlayers[playerId].speed < 0.5f) || ((gPlayers[playerId].effects & MIDAIR_EFFECT) == MIDAIR_EFFECT)) &&
            (D_800E9E74[playerId] != 0x0000001C)) {
            D_800E9E74[playerId] = 0;
        }
        if ((((gPlayers[playerId].effects & EARLY_START_SPINOUT_EFFECT) == EARLY_START_SPINOUT_EFFECT) &&
             ((gPlayers[playerId].type & PLAYER_START_SEQUENCE) != PLAYER_START_SEQUENCE)) ||
            ((gPlayers[playerId].effects & BANANA_NEAR_SPINOUT_EFFECT) == BANANA_NEAR_SPINOUT_EFFECT) ||
            ((gPlayers[playerId].effects & BANANA_SPINOUT_EFFECT) == BANANA_SPINOUT_EFFECT) ||
            ((gPlayers[playerId].effects & DRIVING_SPINOUT_EFFECT) == DRIVING_SPINOUT_EFFECT) ||
            ((gPlayers[playerId].kartProps & DRIVING_NEAR_SPINOUT) == DRIVING_NEAR_SPINOUT)) {
            D_800E9E74[playerId] = 0x00000012;
        }
        if ((((gPlayers[playerId].effects & AB_SPIN_EFFECT) == AB_SPIN_EFFECT) &&
             ((gPlayers[playerId].type & PLAYER_START_SEQUENCE) != PLAYER_START_SEQUENCE)) ||
            ((gPlayers[playerId].effects & BANANA_NEAR_SPINOUT_EFFECT) == BANANA_NEAR_SPINOUT_EFFECT)) {
            D_800E9E74[playerId] = 0x00000013;
        }
        if (gPlayers[playerId].unk_20C != 0.0f) {
            D_800E9E74[playerId] = 3;
        }
    }
}

/* 
   Routine to tell the game which "finish" music to play depending on which mode the player is in (Grand Prix, Time Trials, etc),
   whether the game is in multiplayer or not, and which position they ended up finishing in (1st, 2nd, 3rd, etc)

   Contains a LOT of inlined funcs. 
   Modify if you dare.
*/
void audio_handle_race_finish(u8 playerId) {
    if (D_800E9EA4[playerId] != 0) {
        if (D_800E9EA4[playerId] < 0x2BC) {
            D_800E9EA4[playerId]++;
        }
        if (D_800E9EA4[playerId] == 2) {
            audio_stop_player_sound(playerId, SOUND_ARG_LOAD(0x01, 0x00, 0xFA, 0x28));
            audio_stop_player_sound(playerId, SOUND_ARG_LOAD(0x01, 0x00, 0xFF, 0x2C));
            audio_stop_player_sound(playerId, SOUND_ARG_LOAD(0x01, 0x00, 0xFA, 0x4C));
            audio_stop_sound_and_request_by_pos_and_id(&gAudioCharacterStates[playerId].pos, D_800E9E94[playerId]);
            D_800E9E74[playerId] = 0;
            switch (gModeSelection) { /* irregular */
                case GRAND_PRIX:
                    D_800EA0EC[playerId] = 2;
                    audio_play_sound_by_player_id(playerId, SOUND_ARG_LOAD(0x19, 0x00, 0xF1, 0x03));
                    if (gAudioNumCameras == 0) {
                        audio_push_cmd(0x100100FF);
                        audio_push_cmd(0x110100FF);
                        audio_stop_all_sounds_in_bank(5U);
                        if (gPlayers[playerId].currentRank == 0) {
                            audio_stop_character_sounds(playerId);
                            D_800EA0F0 = 2;
                            audio_play_race_finish_sound(playerId);
                            play_sequences(SEQ_EVENT_RACE_FINISH_FIRST, SEQ_MENU_RESULTS_SCREEN_WIN);
                        } else if (gPlayers[playerId].currentRank < 4) {
                            audio_stop_character_sounds(playerId);
                            D_800EA0F0 = 2;
                            audio_play_race_finish_sound(playerId);
                            play_sequences(SEQ_EVENT_RACE_FINISH_OTHER, SEQ_MENU_RESULTS_SCREEN_WIN);
                        } else {
                            audio_push_cmd(-0x3E9F9C00);
                            play_sequences(SEQ_EVENT_RACE_FINISH_LOSE, SEQ_MENU_RESULTS_SCREEN_LOSE);
                        }
                    } else {
                        D_800EA0EC[playerId] = 2;
                        audio_play_sound_by_player_id(playerId, 0x1900F103U);
                        if (gPlayers[playerId].currentRank == 0) {
                            audio_push_cmd(0x100100FF);
                            audio_push_cmd(0x110100FF);
                            audio_stop_character_sounds(playerId);
                            D_800EA0F0 = 2;
                            audio_play_race_finish_sound(playerId);
                            play_sequences(SEQ_EVENT_RACE_FINISH_FIRST, SEQ_MENU_RESULTS_SCREEN_WIN);
                        } else if (gPlayers[playerId].currentRank < 4) {
                            if (D_800EA104 == 0) {
                                audio_push_cmd(0x100100FF);
                                audio_push_cmd(0x110100FF);
                            }
                            audio_stop_character_sounds(playerId);
                            D_800EA0F0 = 2;
                            audio_play_race_finish_sound(playerId);
                            play_sequences(SEQ_EVENT_RACE_FINISH_OTHER, SEQ_MENU_RESULTS_SCREEN_WIN);
                        } else if (D_800EA104 == 0) {
                            audio_push_cmd(0x100100FF);
                            audio_push_cmd(0x110100FF);
                            audio_push_cmd(-0x3E9F9C00);
                            play_sequences(SEQ_EVENT_RACE_FINISH_LOSE, SEQ_MENU_RESULTS_SCREEN_LOSE);
                        }
                        if ((D_800EA104 != 0) || (D_800EA0EC[playerId] != 1)) {
                            audio_stop_all_sounds_in_bank(5U);
                        }
                    }
                    break;
                case TIME_TRIALS:
                    audio_push_cmd(0x100100FF);
                    audio_push_cmd(0x110100FF);
                    audio_stop_character_sounds(playerId);
                    D_800EA0F0 = 2;
                    audio_play_race_finish_sound(0U);
                    D_800EA0EC[playerId] = 2;
                    audio_play_sound_by_player_id(playerId, 0x1900F103U);
                    if (D_801657E5 == 1) {
                        play_sequences(SEQ_EVENT_RACE_FINISH_FIRST, SEQ_MENU_RESULTS_SCREEN_WIN);
                    } else if (D_8018ED90 == 1) {
                        play_sequences(SEQ_EVENT_RACE_FINISH_OTHER, SEQ_MENU_RESULTS_SCREEN_WIN);
                    } else {
                        audio_push_cmd(0x01640010);
                    }
                    break;
                case VERSUS:
                    D_800EA0EC[playerId] = 2;
                    audio_play_sound_by_player_id(playerId, 0x1900F103U);
                    switch (gAudioNumCameras) { /* switch 1; irregular */
                        case 1:           /* switch 1 */
                            audio_push_cmd(0x100100FF);
                            audio_push_cmd(0x110100FF);
                            audio_stop_character_sounds(playerId);
                            D_800EA0F0 = 2;
                            audio_play_race_finish_sound(playerId);
                            play_sequences(SEQ_EVENT_RACE_FINISH_FIRST, SEQ_MENU_RESULTS_SCREEN_WIN_VS);
                            break;
                        case 2: /* switch 1 */
                            if ((D_800EA104 == 0) && (D_800EA0EC[playerId] == 1)) {
                                audio_push_cmd(0x100100FF);
                                audio_push_cmd(0x110100FF);
#ifdef VERSION_EU
                                play_sequence2(SEQ_EVENT_RACE_FINISH_FIRST);
#else
                                play_sequences(SEQ_EVENT_RACE_FINISH_FIRST, SEQ_MENU_RESULTS_SCREEN_WIN_VS);
#endif
                                D_800EA104 = 1;
                            } else if ((D_800EA104 == 1) && (D_800EA0EC[playerId] == 1)) {
                                audio_stop_all_sounds_in_bank(5U);
#ifndef VERSION_EU
                                if (audio_get_sequence_id(1) != 0x000D)
#endif
                                {
                                    D_800EA104 = 0;
                                    play_sequences(SEQ_EVENT_RACE_FINISH_OTHER, SEQ_MENU_RESULTS_SCREEN_WIN_VS);
                                }
                                D_800EA104 = 2;
                            }
                            break;
                        case 3: /* switch 1 */
                            if ((D_800EA104 == 0) && (D_800EA0EC[playerId] == 1)) {
                                audio_push_cmd(0x100100FF);
                                audio_push_cmd(0x110100FF);
                                play_sequence2(SEQ_EVENT_RACE_FINISH_FIRST);
                                D_800EA104 = 1;
                            } else if ((D_800EA104 == 1) && (D_800EA0EC[playerId] == 1)) {
                                if (audio_get_sequence_id(1) != 0x000D) {
                                    D_800EA104 = 0;
                                    play_sequence2(SEQ_EVENT_RACE_FINISH_OTHER);
                                }
                                D_800EA104 = 2;
                            } else if ((D_800EA104 == 2) && (D_800EA0EC[playerId] == 1)) {
                                audio_stop_all_sounds_in_bank(5U);
#ifndef VERSION_EU
                                if (audio_get_sequence_id(1) != 0x000E)
#endif
                                {
                                    D_800EA104 = 0;
                                    play_sequences(SEQ_EVENT_RACE_FINISH_OTHER, SEQ_MENU_RESULTS_SCREEN_WIN_VS);
                                }
                                D_800EA104 = 3;
                            }
                            break;
                    }
                    break;
                case BATTLE:
                    switch (gAudioNumCameras) { /* switch 2; irregular */
                        case 1:           /* switch 2 */
                            audio_push_cmd(0x100100FF);
                            audio_push_cmd(0x110100FF);
                            audio_stop_all_sounds_in_bank(5U);
                            audio_stop_player_sound(playerId, SOUND_ARG_LOAD(0x01, 0x00, 0xF9, 0x26));
                            play_sequence2(SEQ_MENU_RESULTS_SCREEN_WIN_VS);
                            D_800EA0EC[playerId] = 2;
                            audio_play_character_sound(playerId, (gPlayers[gPlayerWinningIndex].characterId * 0x10) +
                                                        SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x0D));
                            break;
                        case 2: /* switch 2 */
                            if ((D_800EA0EC[0] == 1) && (D_800EA0EC[1] == 1) && (D_800EA0EC[2] == 1)) {
                                audio_stop_all_sounds_in_bank(5U);
                                audio_stop_player_sound(playerId, SOUND_ARG_LOAD(0x01, 0x00, 0x80, 0x26));
                                play_sequence2(SEQ_MENU_RESULTS_SCREEN_WIN_VS);
                                D_800EA0EC[playerId] = 2;
                                audio_play_character_sound(playerId, (gPlayers[gPlayerWinningIndex].characterId * 0x10) +
                                                            SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x0D));
                            }
                            break;
                        case 3: /* switch 2 */
                            if ((D_800EA0EC[0] == 1) && (D_800EA0EC[1] == 1) && (D_800EA0EC[2] == 1) &&
                                (D_800EA0EC[3] == 1)) {
                                audio_stop_all_sounds_in_bank(5U);
                                audio_stop_player_sound(playerId, SOUND_ARG_LOAD(0x01, 0x00, 0x80, 0x26));
                                play_sequence2(SEQ_MENU_RESULTS_SCREEN_WIN_VS);
                                D_800EA0EC[playerId] = 2;
                                audio_play_character_sound(playerId, (gPlayers[gPlayerWinningIndex].characterId * 0x10) +
                                                            SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x0D));
                            }
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        if (D_800E9EA4[playerId] == 0x0000001E) {
            switch (gModeSelection) { /* switch 3; irregular */
                case BATTLE:          /* switch 3 */
                    break;
                case GRAND_PRIX: /* switch 3 */
                    if (gPlayers[playerId].currentRank == 0) {
                        D_800EA0EC[playerId] = 2;
                        audio_play_character_sound(playerId,
                                      (gPlayers[playerId].characterId * 0x10) + SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x07));
                    } else if (gPlayers[playerId].currentRank < 4) {
                        D_800EA0EC[playerId] = 2;
                        audio_play_character_sound(playerId,
                                      (gPlayers[playerId].characterId * 0x10) + SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x0D));
                    } else {
                        D_800EA0EC[playerId] = 2;
                        audio_play_character_sound(playerId,
                                      (gPlayers[playerId].characterId * 0x10) + SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x03));
                    }
                    break;
                case VERSUS: /* switch 3 */
                    if (gPlayers[playerId].currentRank == 0) {
                        D_800EA0EC[playerId] = 2;
                        audio_play_character_sound(playerId,
                                      (gPlayers[playerId].characterId * 0x10) + SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x0D));
                    }
                    break;
                case TIME_TRIALS: /* switch 3 */
                    if (D_801657E5 == 1) {
                        D_800EA0EC[playerId] = 2;
                        audio_play_character_sound(playerId,
                                      (gPlayers[playerId].characterId * 0x10) + SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x07));
                    } else if (D_8018ED90 == (u8) 1) {
                        D_800EA0EC[playerId] = 2;
                        audio_play_character_sound(playerId,
                                      (gPlayers[playerId].characterId * 0x10) + SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x0D));
                    }
                    break;
            }
        }
        switch (gModeSelection) { /* switch 4; irregular */
            case GRAND_PRIX:      /* switch 4 */
                if (gPlayers[playerId].currentRank == 0) {
                    if (D_800E9EA4[playerId] >= 0x15F) {
                        if (D_800E9EA4[playerId] == 0x0000015F) {
                            audio_stop_race_finish_sound(playerId);
                        }
                    } else {
                        D_800EA130[playerId] = (f32) D_800E9EA4[playerId] / 400.0f;
                    }
                } else if (gPlayers[playerId].currentRank < 4) {
                    if (D_800E9EA4[playerId] >= 0x15F) {
                        if (D_800E9EA4[playerId] == 0x0000015F) {
                            audio_stop_race_finish_sound(playerId);
                        }
                    } else {
                        D_800EA130[playerId] = (f32) D_800E9EA4[playerId] / 400.0f;
                    }
                } else if (D_800E9EA4[playerId] >= 0x12D) {
                    if (D_800E9EA4[playerId] == 0x0000012D) {
                        audio_stop_character_sounds(playerId);
                    }
                } else {
                    D_800EA130[playerId] = (f32) D_800E9EA4[playerId] / 330.0f;
                }
                break;
            case VERSUS: /* switch 4 */
                if (gAudioNumCameras == (u8) 1) {
                    if (D_800E9EA4[playerId] >= 0x65) {
                        if (D_800E9EA4[playerId] == 0x00000065) {
                            audio_stop_race_finish_sound(playerId);
                        }
                    } else {
                        D_800EA130[playerId] = (f32) D_800E9EA4[playerId] / 120.0f;
                    }
                } else if (D_800E9EA4[playerId] >= 0x65) {
                    if (D_800E9EA4[playerId] == 0x00000065) {
                        audio_stop_character_sounds(playerId);
                    }
                } else {
                    D_800EA130[playerId] = (f32) D_800E9EA4[playerId] / 120.0f;
                }
                /* fallthrough */
            case TIME_TRIALS: /* switch 4 */
                if (D_800E9EA4[playerId] >= 0x12D) {
                    if (D_800E9EA4[playerId] == 0x0000012D) {
                        audio_stop_race_finish_sound(0U);
                    }
                } else {
                    D_800EA130[playerId] = (f32) D_800E9EA4[playerId] / 350.0f;
                }
                break;
            case BATTLE: /* switch 4 */
                if (D_800E9EA4[playerId] >= 0x65) {
                    if (D_800E9EA4[playerId] == 0x00000065) {
                        audio_stop_character_sounds(playerId);
                    }
                } else {
                    D_800EA130[playerId] = (f32) D_800E9EA4[playerId] / 120.0f;
                }
                break;
        }
    }
}

void audio_update_water_sound(u8 playerId) {
    if ((gPlayers[playerId].oobProps & UNDER_OOB_OR_FLUID_LEVEL) == UNDER_OOB_OR_FLUID_LEVEL) {
        if (D_800E9F74[playerId] == 0) {
            if ((s32) gAudioNumCameras < 2) {
                audio_stop_player_sound(playerId, SOUND_ARG_LOAD(0x01, 0x00, 0xF9, 0x26));
            } else {
                audio_stop_player_sound(playerId, SOUND_ARG_LOAD(0x01, 0x00, 0x80, 0x26));
            }
            audio_stop_character_sounds(playerId);
            D_800E9F74[playerId] = 1;
            audio_play_character_engine_sound(playerId);
            if (((gCurrentCourseId == COURSE_CHOCO_MOUNTAIN) || (gCurrentCourseId == COURSE_BOWSER_CASTLE) ||
                 (gCurrentCourseId == COURSE_BANSHEE_BOARDWALK) || (gCurrentCourseId == COURSE_YOSHI_VALLEY) ||
                 (gCurrentCourseId == COURSE_FRAPPE_SNOWLAND) || (gCurrentCourseId == COURSE_KOOPA_BEACH) ||
                 (gCurrentCourseId == COURSE_ROYAL_RACEWAY) || (gCurrentCourseId == COURSE_SHERBET_LAND) ||
                 (gCurrentCourseId == COURSE_DK_JUNGLE) || (gCurrentCourseId == COURSE_BIG_DONUT)) &&
                (D_800EA0EC[playerId] == 0)) {
                play_sound((gPlayers[playerId].characterId * 0x10) + SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x05),
                           &gAudioCharacterStates[playerId].pos, playerId, &gAudioOneFloat, &gAudioOneFloat,
                           (s8*) &gAudioCharacterStates[playerId].unk_14);
            }
        }
    } else {
        if (D_800E9F74[playerId] == 1) {
            audio_stop_character_sounds(playerId);
            D_800E9F74[playerId] = 2;
            audio_play_character_engine_sound(playerId);
            D_800E9F74[playerId] = 0;
            if ((gCurrentCourseId == COURSE_KOOPA_BEACH) && (D_800EA0EC[playerId] == 0)) {
                play_sound((gPlayers[playerId].characterId * 0x10) + SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x08),
                           &gAudioCharacterStates[playerId].pos, playerId, &gAudioOneFloat, &gAudioOneFloat,
                           (s8*) &gAudioCharacterStates[playerId].unk_14);
            }
        }
    }
}

void audio_update_lightning_effect_sound(u8 playerId) {
    if (((gPlayers[playerId].effects & LIGHTNING_EFFECT) != LIGHTNING_EFFECT) && (D_800E9F24[playerId] == 1)) {
        audio_play_character_sound(playerId, (gPlayers[playerId].characterId * 0x10) + SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x08));
    }
}

void audio_update_lightning_effect_pitch(u8 playerId) {
    if ((gPlayers[playerId].effects & LIGHTNING_EFFECT) == LIGHTNING_EFFECT) {
        D_800E9F24[playerId] = 1;
        if (D_800E9F2C[playerId] < 0xFA) {
            D_800E9F2C[playerId]++;
        }
    } else {
        D_800E9F2C[playerId] = 0;
        if (D_800E9F24[playerId] == 1) {
            D_800E9F24[playerId] = 2;
        }
    }
    switch (D_800E9F24[playerId]) { /* irregular */
        case 1:
            if (D_800E9F34[playerId] < 0.7f) {
                D_800E9F34[playerId] += 0.1f;
                D_800E9F54[playerId] += 0.03f;
            }
            break;
        case 2:
            if (D_800E9F34[playerId] > 0.16f) {
                D_800E9F34[playerId] -= 0.15f;
                D_800E9F54[playerId] -= 0.03f;
            } else {
                D_800E9F34[playerId] = 0.0f;
                D_800E9F54[playerId] = 0.0f;
                D_800E9F24[playerId] = 0;
            }
            break;
    }
}

// Checks the same field for all players before doing something?
void audio_check_lightning_effect_end(void) {
    if (((u8) D_800EA168 != 0) && ((gPlayers[0].effects & LIGHTNING_EFFECT) != LIGHTNING_EFFECT) &&
        ((gPlayers[1].effects & LIGHTNING_EFFECT) != LIGHTNING_EFFECT) &&
        ((gPlayers[2].effects & LIGHTNING_EFFECT) != LIGHTNING_EFFECT) &&
        ((gPlayers[3].effects & LIGHTNING_EFFECT) != LIGHTNING_EFFECT) &&
        ((gPlayers[4].effects & LIGHTNING_EFFECT) != LIGHTNING_EFFECT) &&
        ((gPlayers[5].effects & LIGHTNING_EFFECT) != LIGHTNING_EFFECT) &&
        ((gPlayers[6].effects & LIGHTNING_EFFECT) != LIGHTNING_EFFECT) &&
        ((gPlayers[7].effects & LIGHTNING_EFFECT) != LIGHTNING_EFFECT)) {
        audio_stop_thunder_sound_effect();
    }
}

void audio_update_star_effect_volume(void) {
    if (D_800EA180 != 0) {
        D_800EA180++;
        if (D_800EA180 == 2) {
            D_800EA17C = 1.0f;
        }
        if (D_800EA180 < 0xF) {
            D_800EA178 = 1.0f - (D_800EA180 * 0.012f);
        }
        if ((D_800EA180 >= 0x33) && (D_800EA180 < 0x96)) {
            D_800EA17C = 1.0f - ((D_800EA180 - 0x32) / 110.0f);
        }
        if (D_800EA180 == 0x12D) {
            D_800EA17C = 0.0f;
        }
        if (D_800EA180 == 0x321) {
            D_800EA178 = 1.0f;
            D_800EA17C = 0.85f;
            D_800EA180 = 0;
        }
    }
}

void audio_update_luigi_raceway_tunnel_sound(void) {
    if (gCurrentCourseId == COURSE_LUIGI_RACEWAY) {
        if (D_800EA184 != 0) {
            if ((u8) D_800EA16C == 0) {
                // Has to be this way, can't be D_800EA184++
                D_800EA184 += 1;
            }
            if (D_800EA184 == 0x012C) {
                D_800EA17C = 0.85f;
                D_800EA184 = 0;
            }
        } else {
            switch (gAudioNumCameras) { /* irregular */
                case 0:
                    if (gAudioCharacterStates[0].unk_14 != 0) {
                        D_800EA17C = 0.0f;
                        D_800EA184 = 1;
                    }
                    break;
                case 1:
                    if ((gAudioCharacterStates[0].unk_14 != 0) || (gAudioCharacterStates[1].unk_14 != 0)) {
                        D_800EA17C = 0.0f;
                        D_800EA184 = 1;
                    }
                    break;
                case 2:
                    if ((gAudioCharacterStates[0].unk_14 != 0) || (gAudioCharacterStates[1].unk_14 != 0) || (gAudioCharacterStates[2].unk_14 != 0)) {
                        D_800EA17C = 0.0f;
                        D_800EA184 = 1;
                    }
                    break;
                case 3:
                    if ((gAudioCharacterStates[0].unk_14 != 0) || (gAudioCharacterStates[1].unk_14 != 0) || (gAudioCharacterStates[2].unk_14 != 0) ||
                        (gAudioCharacterStates[3].unk_14 != 0)) {
                        D_800EA17C = 0.0f;
                        D_800EA184 = 1;
                    }
                    break;
            }
        }
    }
}

void audio_update_camera_sound_volume(u8 arg0) {
    gAudioCameraStates[arg0].unk00[2] = (1.0f - D_800E9F54[arg0]) - D_800EA130[arg0];
}

void audio_update_all_player_sounds() {
    u8 var_s0;

    for (var_s0 = 0; var_s0 < gAudioNumCameras + 1; var_s0++) {
        audio_update_throttle_state(var_s0);
        audio_update_throttle_sound_state(var_s0);
        audio_update_throttle_sound_pitch(var_s0);
        audio_update_throttle_sound_volume(var_s0);
        audio_update_throttle_sound_speed(var_s0);
        audio_update_throttle_sound_type(var_s0);
        audio_update_surface_sound(var_s0);
        audio_handle_race_finish(var_s0);
        audio_update_water_sound(var_s0);
        audio_update_lightning_effect_sound(var_s0);
    }
    if (gModeSelection == GRAND_PRIX) {
        for (var_s0 = 0; var_s0 < 8; var_s0++) {
            audio_update_lightning_effect_pitch(var_s0);
            audio_update_camera_sound_volume(var_s0);
        }
    } else {
        for (var_s0 = 0; var_s0 < gAudioNumCameras + 1; var_s0++) {
            audio_update_lightning_effect_pitch(var_s0);
            audio_update_camera_sound_volume(var_s0);
        }
    }
    audio_check_lightning_effect_end();
    audio_update_star_effect_volume();
    audio_update_luigi_raceway_tunnel_sound();
}

void play_sound2(s32 soundBits) {
    if ((soundBits == SOUND_ACTION_REV_ENGINE) && (gCurrentCourseId == COURSE_DK_JUNGLE)) {
        soundBits = SOUND_ARG_LOAD(0x49, 0x00, 0x80, 0x27);
    }

    if ((soundBits == SOUND_ACTION_REV_ENGINE_2) && (gCurrentCourseId == COURSE_DK_JUNGLE)) {
        soundBits = SOUND_ARG_LOAD(0x49, 0x00, 0x80, 0x28);
    }
    play_sound(soundBits, &gAudioDefaultPos, 4, &gAudioOneFloat, &gAudioOneFloat, &gAudioZeroS8);
}

void play_sequence(u16 index) {
    audio_push_cmd(index | 0x0010000);
    D_800EA15C = index;
}

void play_sequence2(u16 index) {
    audio_push_cmd(index | 0x1010000);
    D_800EA160 = index;
}

void audio_set_sequence_volume_0(u8 arg0) {
    audio_set_sequence_volume(0, 0, arg0, 1);
}

void audio_play_sound_by_player_id_and_pos(u8 arg0, u32 soundBits) {
    if (D_800EA108 == 0) {
        switch (D_800EA0EC[arg0]) {
            case 2:
                D_800EA0EC[arg0] = 1;
            case 0:
                play_sound(soundBits, &gAudioCharacterStates[arg0].pos, arg0, &gAudioOneFloat, &gAudioOneFloat, &gAudioZeroS8);
                break;
        }
    }
}

void audio_stop_player_sound(u8 playerIndex, u32 soundBits) {
    audio_stop_sound_and_request_by_pos_and_id(&gAudioCharacterStates[playerIndex].pos, soundBits);
}

void audio_play_sound_by_player_id(u8 playerId, u32 soundBits) {
    if (D_800EA108 == 0) {
        switch (D_800EA0EC[playerId]) {
            case 2:
                D_800EA0EC[playerId] = 1;
            case 0:
                play_sound(soundBits, &gAudioCharacterStates[playerId].pos, playerId, &gAudioOneFloat, &gAudioOneFloat,
                           (s8*) &gAudioCharacterStates[playerId].unk_14);
                break;
        }
    }
}

void audio_play_character_sound(u8 playerId, u32 soundBits) {
    if (D_800EA108 == 0) {
        switch (D_800EA0EC[playerId]) {
            case 2:
                D_800EA0EC[playerId] = 1;
            case 0:
                if (((soundBits & ~0xF0) == SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x03)) ||
                    ((soundBits & ~0xF0) == SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x04)) ||
                    ((soundBits & ~0xF0) == SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x05))) {
                    D_800EA180 = 1;
                }
                if (((gPlayers[playerId].effects & LIGHTNING_EFFECT) == LIGHTNING_EFFECT) &&
                    ((s32) D_800E9F2C[playerId] >= 0x1F)) {
                    play_sound(soundBits, &gAudioCharacterStates[playerId].pos, playerId, &D_800EA150, &gAudioOneFloat,
                               (s8*) &gAudioCharacterStates[playerId].unk_14);
                } else {
                    play_sound(soundBits, &gAudioCharacterStates[playerId].pos, playerId, &gAudioOneFloat, &gAudioOneFloat,
                               (s8*) &gAudioCharacterStates[playerId].unk_14);
                }
                break;
            default:
                break;
        }
    }
}

void audio_play_character_sound_2901(u8 playerIndex) {
    audio_play_character_sound(playerIndex, (gPlayers[playerIndex].characterId * 0x10) + (gAudioRandom & 1) +
                                   SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x01));
}

void audio_play_character_sound_with_effects(u8 playerId, u32 soundBits) {
    u8 var_s0;
    struct Unk_8018EFD8* temp_v0;

    if ((D_800EA108 == 0) && (D_800EA0F0 == 0) && ((s32) gAudioNumCameras < 2)) {
        for (var_s0 = 0; var_s0 < gAudioNumCameras + 1; var_s0++) {
            temp_v0 = audio_alloc_sound_source(playerId, gPlayers[playerId].pos, gPlayers[playerId].velocity, gAudioDefaultPos,
                                    (u8) var_s0, soundBits);
            if (temp_v0 != NULL) {
                temp_v0->unk34 = 170.0f;
                if (((gPlayers[playerId].effects & LIGHTNING_EFFECT) == LIGHTNING_EFFECT) &&
                    ((s32) D_800E9F2C[playerId] >= 0x1F)) {
                    play_sound((gPlayers[playerId].characterId * 0x10) + soundBits, &temp_v0->unk18, var_s0,
                               &D_800EA150, &gAudioOneFloat, (s8*) &gAudioCameraStates[playerId].unk0C);
                } else {
                    play_sound((gPlayers[playerId].characterId * 0x10) + soundBits, &temp_v0->unk18, var_s0,
                               &temp_v0->unk2C, &gAudioOneFloat, (s8*) &gAudioCameraStates[playerId].unk0C);
                }
            }
        }
    }
}

void audio_play_character_engine_sound(u8 playerId) {
    u32 var_a0;

    if (D_800EA108 == 0) {
        switch (D_800EA0EC[playerId]) {
            case 2:
                D_800EA0EC[playerId] = 1;
            case 0:
                gAudioCharacterStates[playerId].unk_0C = 1.0f;
                gAudioCharacterStates[playerId].unk_10 = 0.0f;
                switch (gPlayers[playerId].characterId) {
                    case 0:
                    case 1:
                        gAudioCharacterStates[playerId].unk_18 = 2.8f;
                        gAudioCharacterStates[playerId].unk_1C = 3844.0f;
                        gAudioCharacterStates[playerId].unk_20 = 0.35f;
                        gAudioCharacterStates[playerId].unk_24 = -0.8f;
                        gAudioCharacterStates[playerId].unk_28 = 0.35f;
                        gAudioCharacterStates[playerId].unk_2C = 1568.9796f;
                        gAudioCharacterStates[playerId].unk_30 = 1067.7778f;
                        gAudioCharacterStates[playerId].unk_34 = 2766.065f;
                        break;
                    case 2:
                    case 6:
                        gAudioCharacterStates[playerId].unk_18 = 3.2f;
                        gAudioCharacterStates[playerId].unk_1C = 3844.0f;
                        gAudioCharacterStates[playerId].unk_20 = 0.6f;
                        gAudioCharacterStates[playerId].unk_24 = -1.7f;
                        gAudioCharacterStates[playerId].unk_28 = 0.6f;
                        gAudioCharacterStates[playerId].unk_2C = 1478.4615f;
                        gAudioCharacterStates[playerId].unk_30 = 784.4898f;
                        gAudioCharacterStates[playerId].unk_34 = 12813.335f;
                        break;
                    case 3:
                        gAudioCharacterStates[playerId].unk_18 = 2.8f;
                        gAudioCharacterStates[playerId].unk_1C = 3844.0f;
                        gAudioCharacterStates[playerId].unk_20 = 0.6f;
                        gAudioCharacterStates[playerId].unk_24 = -0.6f;
                        gAudioCharacterStates[playerId].unk_28 = 0.6f;
                        gAudioCharacterStates[playerId].unk_2C = 1747.2728f;
                        gAudioCharacterStates[playerId].unk_30 = 1130.5883f;
                        gAudioCharacterStates[playerId].unk_34 = 3844.001f;
                        break;
                    case 4:
                        gAudioCharacterStates[playerId].unk_18 = 2.0f;
                        gAudioCharacterStates[playerId].unk_1C = 3844.0f;
                        gAudioCharacterStates[playerId].unk_20 = 0.2f;
                        gAudioCharacterStates[playerId].unk_24 = -0.4f;
                        gAudioCharacterStates[playerId].unk_28 = 0.2f;
                        gAudioCharacterStates[playerId].unk_2C = 2135.5557f;
                        gAudioCharacterStates[playerId].unk_30 = 1601.6666f;
                        gAudioCharacterStates[playerId].unk_34 = 3203.333f;
                        break;
                    case 5:
                    case 7:
                        gAudioCharacterStates[playerId].unk_18 = 2.4f;
                        gAudioCharacterStates[playerId].unk_1C = 3844.0f;
                        gAudioCharacterStates[playerId].unk_20 = 0.4f;
                        gAudioCharacterStates[playerId].unk_24 = -0.8f;
                        gAudioCharacterStates[playerId].unk_28 = 0.4f;
                        gAudioCharacterStates[playerId].unk_2C = 1922.0f;
                        gAudioCharacterStates[playerId].unk_30 = 1201.25f;
                        gAudioCharacterStates[playerId].unk_34 = 4805.0f;
                        break;
                }
                var_a0 = gPlayers[playerId].characterId + 0x0104FF00;
                switch (D_800E9F74[playerId]) { /* switch 1; irregular */
                    case 0:                     /* switch 1 */
                        if (gAudioNumCameras != 0) {
                            var_a0 += 0x14;
                        }
                        break;
                    case 1: /* switch 1 */
                        var_a0 += 0x2E;
                        break;
                    case 2: /* switch 1 */
                        if (gAudioNumCameras == 0) {
                            var_a0 += 0x36;
                        } else {
                            var_a0 += 0x3E;
                        }
                        break;
                }
                play_sound(var_a0, &gAudioCharacterStates[playerId].pos, playerId, &gAudioCharacterStates[playerId].unk_0C,
                           &gAudioCharacterStates[playerId].unk_10, (s8*) &gAudioCharacterStates[playerId].unk_14);
                break;
            default:
                break;
        }
    }
}

void audio_stop_character_sounds(u8 arg0) {
    audio_stop_sound_and_request_by_pos_and_id(&gAudioCharacterStates[arg0].pos, gPlayers[arg0].characterId + SOUND_ARG_LOAD(0x01, 0x04, 0xFF, 0x00));
    audio_stop_sound_and_request_by_pos_and_id(&gAudioCharacterStates[arg0].pos, gPlayers[arg0].characterId + SOUND_ARG_LOAD(0x01, 0x04, 0xFF, 0x14));
    audio_stop_sound_and_request_by_pos_and_id(&gAudioCharacterStates[arg0].pos, gPlayers[arg0].characterId + SOUND_ARG_LOAD(0x01, 0x04, 0xFF, 0x2E));
    audio_stop_sound_and_request_by_pos_and_id(&gAudioCharacterStates[arg0].pos, gPlayers[arg0].characterId + SOUND_ARG_LOAD(0x01, 0x04, 0xFF, 0x36));
    audio_stop_sound_and_request_by_pos_and_id(&gAudioCharacterStates[arg0].pos, gPlayers[arg0].characterId + SOUND_ARG_LOAD(0x01, 0x04, 0xFF, 0x3E));
}

void audio_play_sound_by_pos(Vec3f position, Vec3f velocity, u32 soundBits) {
    u8 var_s0;
    struct Unk_8018EFD8* temp_v0;

    if ((D_800EA108 == 0) && (D_800EA0F0 == 0)) {
        for (var_s0 = 0; var_s0 < (gAudioNumCameras + 1); var_s0++) {
            temp_v0 = audio_alloc_sound_source(0U, position, velocity, gAudioDefaultPos, (u8) var_s0, soundBits);
            if (temp_v0 != 0) {
                temp_v0->unk34 = 170.0f;
                play_sound(soundBits, &temp_v0->unk18, var_s0, &temp_v0->unk2C, &gAudioOneFloat, &gAudioZeroS8);
            }
        }
    }
}

void audio_stop_sound_by_pos_and_id_all_cameras(Vec3f arg0, s32 soundBits) {
    Vec3f* temp_v0;
    u8 temp_t9;

    if (D_800EA108 == 0) {
        for (temp_t9 = 0; temp_t9 < gAudioNumCameras + 1; temp_t9++) {
            temp_v0 = audio_get_sound_source_pos(arg0, soundBits);
            if (temp_v0 != NULL) {
                audio_stop_sound_and_request_by_pos_and_id(temp_v0, soundBits);
            }
        }
    }
}

void audio_play_race_finish_sound(u8 playerId) {
    u8 var_s0;
    u32 soundBits;
    struct Unk_8018EFD8* temp_v0_6;

    if (D_800EA108 == 0) {
        switch (D_800EA0F0) {
            case 2:
                D_800EA0F0 = 1;
                /* fallthrough */
            case 0:
                switch (gPlayers[playerId].characterId) {
                    case 0:
                    case 1:
                        gAudioCameraStates[playerId].unk00[0] = 0.35f;
                        gAudioCameraStates[playerId].unk00[1] = 1568.9796f;
                        break;
                    case 2:
                    case 6:
                        gAudioCameraStates[playerId].unk00[0] = 0.6f;
                        gAudioCameraStates[playerId].unk00[1] = 1478.4615f;
                        break;
                    case 3:
                        gAudioCameraStates[playerId].unk00[0] = 0.6f;
                        gAudioCameraStates[playerId].unk00[1] = 1747.2728f;
                        break;
                    case 4:
                        gAudioCameraStates[playerId].unk00[0] = 0.2f;
                        gAudioCameraStates[playerId].unk00[1] = 2135.5557f;
                        break;
                    case 5:
                    case 7:
                        gAudioCameraStates[playerId].unk00[0] = 0.4f;
                        gAudioCameraStates[playerId].unk00[1] = 1922.0f;
                }
                if (gAudioNumCameras < 2) {
                    for (var_s0 = 0; var_s0 < gAudioNumCameras + 1; var_s0++) {
                        soundBits = gPlayers[playerId].characterId + SOUND_ARG_LOAD(0x31, 0x02, 0x80, 0x00);
                        temp_v0_6 = audio_alloc_sound_source(playerId, gPlayers[playerId].pos, gPlayers[playerId].velocity,
                                                  &gPlayers[playerId].unk_098, var_s0, soundBits);
                        if (temp_v0_6 != NULL) {
                            temp_v0_6->unk34 = 40.0f;
                            play_sound(soundBits, &temp_v0_6->unk18, var_s0, &temp_v0_6->unk2C,
                                       &gAudioCameraStates[playerId].unk00[2], (s8*) &gAudioCameraStates[playerId].unk0C);
                        }
                    }
                }
                break;
            default:
                break;
        }
    }
}

void audio_stop_race_finish_sound(u8 playerId) {
    audio_stop_all_sounds_and_requests_by_pos(
        audio_get_sound_source_pos(gPlayers[playerId].pos, gPlayers[playerId].characterId + SOUND_ARG_LOAD(0x31, 0x02, 0x80, 0x00)));
}

void audio_play_sound_by_pos_with_effects(Vec3f position, Vec3f velocity, u32 soundBits) {
    u8 var_s0;
    struct Unk_8018EFD8* temp_v0;

    if ((D_800EA108 == 0) && (D_800EA0F0 == 0) && ((s32) gAudioNumCameras < 4)) {
        for (var_s0 = 0; var_s0 < ((gAudioNumCameras + 1)); var_s0++) {
            temp_v0 = audio_alloc_sound_source(0U, position, velocity, gAudioDefaultPos, (u8) var_s0, soundBits);
            if (temp_v0 != 0) {
                temp_v0->unk34 = 170.0f;
                if (soundBits == SOUND_ARG_LOAD(0x51, 0x03, 0x70, 0x0B)) {
                    play_sound(soundBits, &temp_v0->unk18, var_s0, &D_800EA178, &D_800EA17C, &gAudioZeroS8);
                } else {
                    play_sound(soundBits, &temp_v0->unk18, var_s0, &temp_v0->unk2C, &gAudioOneFloat, &gAudioZeroS8);
                }
            }
        }
    }
}

void audio_stop_sound_by_pos_all_cameras(Vec3f arg0, u32 soundBits) {
    Vec3f* temp;
    u8 i;

    for (i = 0; i < gAudioNumCameras + 1; i++) {
        temp = audio_get_sound_source_pos(arg0, soundBits);
        if (temp != NULL) {
            audio_stop_sound_and_request_by_pos_and_id(temp, soundBits);
        }
    }
}

void audio_play_menu_sound(u8 arg0) {
    if ((arg0) != 0) {
        play_sound2(SOUND_ACTION_GO_BACK_2);
        eu_audio_cmd_send_u32(0xF1000000, 0);
        D_800EA16C = 1;
    } else {
        play_sound2(SOUND_ACTION_UNKNOWN_CONFIRMATION);
        eu_audio_cmd_send_u32(0xF2000000, 0);
        D_800EA16C = 0;
    }
}

void audio_set_sequence_and_volume(u8 arg0, u8 arg1) {
    audio_set_sequence_volume(0, 0, 0x7F, 1);
    audio_set_sequence_volume(1, 0, 0x7F, 1);

    if (arg1 >= 4) {
        if ((arg1 == 0xC) || (arg1 == 4)) {
            arg1 = 5;
        } else {
            arg1 = 4;
        }
    }
    audio_push_cmd((arg0 << 8) | 0xF0000000 | arg1);
}

// With -framepointer active, you CANNOT put void
// in the argument list, causes a minor stack difference
void audio_set_flag_800EA108_true() {
    D_800EA108 = 1;
}

void audio_set_flag_800EA108_false() {
    D_800EA108 = 0;
}

void audio_set_flag_800EA108_true2() {
    D_800EA108 = 1;
}

void audio_stop_banks_3_and_5(void) {
    audio_stop_all_sounds_in_bank(3);
    audio_stop_all_sounds_in_bank(5);
}

void audio_set_player_finished(u8 arg0) {
    D_800EA0EC[arg0] = 1;
    D_800E9EA4[arg0] = 1;
    switch (gAudioNumCameras) { /* irregular */
        case 0:
            D_800EA0F0 = 1;
            audio_stop_banks_3_and_5();
            break;
        case 1:
            if ((D_800EA0EC[0] == (u8) 1) && (D_800EA0EC[1] == (u8) 1)) {
                D_800EA0F0 = 1;
                audio_stop_banks_3_and_5();
            }
            break;
        case 2:
            if ((D_800EA0EC[0] == (u8) 1) && (D_800EA0EC[1] == (u8) 1) && (D_800EA0EC[2] == (u8) 1)) {
                D_800EA0F0 = 1;
                audio_stop_banks_3_and_5();
            }
            break;
        case 3:
            if ((D_800EA0EC[0] == (u8) 1) && (D_800EA0EC[1] == (u8) 1) && (D_800EA0EC[2] == (u8) 1) &&
                (D_800EA0EC[3] == (u8) 1)) {
                D_800EA0F0 = 1;
                audio_stop_banks_3_and_5();
            }
            break;
    }
}

void audio_set_player_finished_2(u8 playerIndex) {
    D_800EA0EC[playerIndex] = 2;
}

void audio_set_flag_800EA0F4_true() {
    D_800EA0F4 = 1;
}

void audio_set_sound_param_14(u8 arg0, s8 arg1) {
    gAudioCharacterStates[arg0].unk_14 = arg1;
}

void audio_clear_sound_param_14(u8 arg0) {
    gAudioCharacterStates[arg0].unk_14 = 0;
}

void audio_set_sound_param_0C(u8 arg0, s8 arg1) {
    gAudioCameraStates[arg0].unk0C = arg1;
}

void audio_clear_sound_param_0C(u8 arg0) {
    gAudioCameraStates[arg0].unk0C = 0;
}

void audio_push_volume_cmd(u8 arg0) {
    audio_push_cmd(arg0 << 0x10 | 0x100000FF);
    audio_push_cmd(arg0 << 0x10 | 0x110000FF);
}

void fade_all_channel_volume_scale(u8 arg0) {
    arg0 *= 2;
    fade_channel_volume_scale(0, 0, arg0);
    fade_channel_volume_scale(1, 0, arg0);
    fade_channel_volume_scale(2, 0, arg0);
    fade_channel_volume_scale(3, 0, arg0);
    fade_channel_volume_scale(5, 0, arg0);
}

void play_sequences(u16 first, u16 second) {
    if (D_800EA104 == 0) {
        audio_push_cmd(audio_get_sequence_id(0) | 0x30000000);
        audio_clear_sequence_timer(0);
        audio_push_cmd(second | 0xC1510000);
        audio_push_cmd(first | 0x01000000);
    }
    D_800EA104 = 1;
}

void audio_play_final_lap_music(u8 playerIndex) {
    if (D_800EA108 == 0) {
        if (gAudioNumCameras >= 2) {
            audio_play_sound_by_player_id(playerIndex, 0x1900FF3A);
        } else if (D_800EA164 != 0) {
            audio_push_cmd(0x100100FF); // 0x19000000
            audio_push_cmd(0x110100FF);
            play_sequence2(SEQ_EVENT_RACE_FINAL_LAP);
            audio_push_cmd(0xC1510011);
        } else {
            audio_push_cmd(0x100100FF); // 0x19000000
            audio_push_cmd(0x110100FF);
            play_sequence2(SEQ_EVENT_RACE_FINAL_LAP);
            audio_push_cmd(D_800EA15C | 0xC1500000);
            audio_push_cmd(0xC130017D);
        }
        D_8018FC08 = D_8018FC08 + 1;
    }
}

void play_star_music(u8 playerId) {
    if ((D_800EA0EC[playerId] == 0) && (D_800EA108 == 0)) {
        play_sound((gPlayers[playerId].characterId * 0x10) + 0x29008001, &gAudioCharacterStates[playerId].pos, playerId,
                   &gAudioOneFloat, &gAudioOneFloat, (s8*) &gAudioCharacterStates[playerId].unk_14);
        D_800EA164 = 1;
        if ((s32) gAudioNumCameras >= 2) {
            audio_play_sound_by_player_id_and_pos(playerId, 0x0100FF2C);
        } else {
            audio_push_cmd(0x100100FF);
            if (D_800EA104 != 0) {
                audio_play_sound_by_player_id_and_pos(playerId, 0x0100FF2C);
            } else if (D_8018FC08 != 0) {
                if ((audio_get_sequence_id(1) == 0x000C) || (audio_is_cmd_not_in_queue(0x0101000C) == 0)) {
                    audio_push_cmd(0xC1F00000);
                    audio_push_cmd(0xC1510011);
                } else {
                    play_sequence2(SEQ_EVENT_RACE_POWERUP_STAR);
                }
            } else {
                if (1) {} // ?
                play_sequence2(SEQ_EVENT_RACE_POWERUP_STAR);
            }
        }
        D_800EA10C[playerId] = 1;
    }
}

void stop_star_music(u8 playerIndex) {
    if (D_800EA0EC[playerIndex] == 0) {
        if ((D_800EA108 == 0) && (D_800EA10C[playerIndex] != 0)) {
            play_sound(gPlayers[playerIndex].characterId * 0x10 + SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x08),
                       &gAudioCharacterStates[playerIndex].pos, playerIndex, &gAudioOneFloat, &gAudioOneFloat,
                       (s8*) &gAudioCharacterStates[playerIndex].unk_14);
            if (D_800EA10C[playerIndex] != 0) {
                if ((s32) gAudioNumCameras >= 2) {
                    audio_stop_player_sound(playerIndex, SOUND_ARG_LOAD(0x01, 0x00, 0xFF, 0x2C));
                } else {
                    D_800EA10C[playerIndex] = 0;
                    if (D_800EA104 != 0) {
                        audio_stop_player_sound(playerIndex, SOUND_ARG_LOAD(0x01, 0x00, 0xFF, 0x2C));
                    } else if ((D_800EA10C[0] == 0) && (D_800EA10C[1] == 0)) {
                        if (D_8018FC08 != 0) {
                            if (((u32) (gSequencePlayers[1].enabled)) == 0) {
                                audio_clear_sequence_mask(1, 5);
                                play_sequence(D_800EA15C);
                                audio_push_cmd(0xB001307DU);
                            } else if ((audio_get_sequence_id(1) == 0xC) || (audio_is_cmd_not_in_queue(0x0101000C) == 0)) {
                                audio_push_cmd(0xC1F00000U);
                                audio_push_cmd(D_800EA15C | 0xC1500000);
                                audio_push_cmd(0xC130017DU);
                            } else {
                                audio_push_cmd(0x110100FFU);
                                play_sequence(D_800EA15C);
                                audio_push_cmd(0xB001307DU);
                            }
                        } else {
                            audio_push_cmd(0x110100FFU);
                            play_sequence(D_800EA15C);
                        }
                    }
                    D_800EA164 = 0;
                }
            }
            D_800EA10C[playerIndex] = 0;
        }
    }
}

void play_star_sound_effect(u8 playerIndex) {
    u8 i;
    struct Unk_8018EFD8* temp_v0_2;

    if ((D_800EA108 == 0) && (D_800EA0F0 == 0)) {
        for (i = 0; i < gAudioNumCameras + 1; i++) {
            temp_v0_2 = audio_alloc_sound_source(playerIndex, gPlayers[playerIndex].pos, gAudioDefaultPos,
                                      &gPlayers[playerIndex].unk_098, (u8) i, SOUND_ITEM_STAR);
            if (temp_v0_2) {
                play_sound(SOUND_ITEM_STAR, &temp_v0_2->unk18, i, &gAudioOneFloat, &gAudioOneFloat, &gAudioZeroS8);
            }
        }
    }
}

void play_star_music_stop_effect(u8 playerId) {
    if ((u8) D_800EA108 == 0) {
        audio_stop_sound_and_request_by_pos_and_id(audio_get_sound_source_pos(gPlayers[playerId].pos, SOUND_ITEM_STAR), SOUND_ITEM_STAR);
    }
}

void play_star_sound_effect_stop(u8 playerIndex) {
    UNUSED u8* temp_v1;
    UNUSED u8 temp_v0;

    if (D_800EA108 == 0) {
        switch (D_800EA0EC[playerIndex]) {
            case 2:
                D_800EA0EC[playerIndex] = 1;
            case 0:
                audio_set_sequence_volume(0, 1U, 0x55U, 5);
                audio_play_sound_by_player_id(playerIndex, 0x1900F013U);
                play_sound(SOUND_ITEM_THUNDERBOLT, &gAudioDefaultPos, 0U, &gAudioOneFloat, &gAudioOneFloat, &gAudioZeroS8);
                break;
            default:
                break;
        }
        D_800EA168 = 1;
    }
}

void audio_stop_thunder_sound_effect() {
    if (D_800EA108 == 0) {
        audio_set_sequence_volume(0, 1U, 0x7FU, 0x19);
        audio_stop_sound_and_request_by_id(SOUND_ITEM_THUNDERBOLT);
        D_800EA168 = 0;
    }
}

void play_thunder_sound_effect(UNUSED u8 arg0) {
    if ((D_800EA108 == 0) && (D_800EA0F0 == 0)) {
        play_sound(SOUND_ACTION_EXPLOSION_2, &gAudioDefaultPos, 0U, &gAudioOneFloat, &gAudioOneFloat, &gAudioZeroS8);
        if ((D_800EA10C[0] != 1) && (D_800EA10C[1] != 1)) {
            audio_set_sequence_volume(0, 1, 0x37U, 5);
            play_sound(SOUND_ITEM_THUNDERBOLT, &gAudioDefaultPos, 0U, &gAudioOneFloat, &gAudioOneFloat, &gAudioZeroS8);
            D_800EA168 = 1;
        }
    }
}

void play_thunder_sound_effect_stop(UNUSED s32 arg0) {
    if (D_800EA108 == 0) {
        if ((D_800EA170[0] == 0) && (D_800EA170[1] == 0) && (D_800EA170[2] == 0) && (D_800EA170[3] == 0)) {
            audio_set_sequence_volume(0, 1, 0x7FU, 0x19);
        }
        audio_stop_sound_and_request_by_id(SOUND_ITEM_THUNDERBOLT);
        D_800EA168 = 0;
    }
}

void audio_update_drift_sound_pitch(u8 playerIndex, f32 arg1) {
    if (D_800EA108 == 0) {
        switch (D_800EA0EC[playerIndex]) {
            case 2:
                D_800EA0EC[playerIndex] = 1;
                // Purposeful fallthrough
            case 0:
                arg1 = (arg1 * 0.55f) + 0.45f;
                if (arg1 > 1.0f) {
                    arg1 = 1.0f;
                }
                if (arg1 < 0.0f) {
                    arg1 = 0.0f;
                }
                D_800EA110[playerIndex] = arg1;
                play_sound(0x1900A209U, &gAudioCharacterStates[playerIndex].pos, playerIndex, &gAudioOneFloat,
                           &D_800EA110[playerIndex], (s8*) &gAudioCharacterStates[playerIndex].unk_14);
                break;
            default:
                break;
        }
    }
}

void set_player_sound_effect_volume(u8 playerId, f32 arg1) {
    if (D_800EA108 == 0) {
        switch (D_800EA0EC[playerId]) {
            case 2:
                D_800EA0EC[playerId] = 1;
                // Purposeful fallthrough
            case 0:
                arg1 = (arg1 * 0.7f) + 0.1f;
                if (arg1 > 1.0f) {
                    arg1 = 1.0f;
                }
                if (arg1 < 0.0f) {
                    arg1 = 0.0f;
                }
                D_800EA120[playerId] = arg1;
                play_sound(gCurrentCourseId + 0x19007020, &gAudioCharacterStates[playerId].pos, playerId, &gAudioOneFloat,
                           &D_800EA120[playerId], (s8*) &gAudioCharacterStates[playerId].unk_14);
                break;
            default:
                break;
        }
    }
}

void play_boo_sound_effect(u8 playerIndex) {
    if (D_800EA108 == 0) {
        switch (D_800EA0EC[playerIndex]) {
            case 2:
                D_800EA0EC[playerIndex] = 1;
            case 0:
                audio_set_sequence_volume(0, 1, 0x55U, 5);
                audio_play_sound_by_player_id(playerIndex, 0x19009E59U);
                audio_play_sound_by_player_id_and_pos(playerIndex, 0x0100FA4C);
                D_800EA170[playerIndex] = 1;
                break;
        }
    }
}

void stop_boo_sound_effect(u8 playerIndex) {
    if (D_800EA108 == 0) {
        if (D_800EA170[playerIndex] == 1) {
            if ((u8) D_800EA168 == 0) {
                audio_set_sequence_volume(0, 1U, 0x7FU, 0x19);
            }
            audio_play_character_sound(playerIndex,
                          gPlayers[playerIndex].characterId * 0x10 + SOUND_ARG_LOAD(0x29, 0x00, 0x80, 0x08));
            audio_stop_player_sound(playerIndex, SOUND_ARG_LOAD(0x01, 0x00, 0xFA, 0x4C));
            D_800EA170[playerIndex] = 0;
        }
    }
}

void audio_trigger_losing_ceremony_sequence() {
    D_800EA174 = 1;
}

/*
   Play the entire "losing" sequence for the podium ceremony.

   Increments a timer value by one per frame in order to tell which part of the sequence to play at which point.
*/
void begin_losing_ceremony_sequence() {
    if (D_800EA174 != 0) {
        D_800EA174++;

        if (D_800EA174 == 3) {
            play_sequence(SEQ_EVENT_CEREMONY_PRESENTATION_PART1); // Begin with Part 1 of the ceremony presentation music --- "Everything seems normal..."
            audio_push_cmd(0x4000007F);
        }

        if (D_800EA174 == 300) {
            play_sequence(SEQ_EVENT_CEREMONY_PRESENTATION_PART2_WIN); // Follow up with Part 2 of the winning ceremony presentation music --- "Looks like I won...?"
            audio_push_cmd(0x4000007F);
            play_sequence2(SEQ_EVENT_CEREMONY_PRESENTATION_PART2_LOSE); // Once it ends, begin the LOSING ceremony presentation music, which has a few notes changed to be off-tune --- "Uh oh..."
            audio_push_cmd(0x41000000);
        }

        if (D_800EA174 == 560) { // (Somewhere in this code it slows down the music, changes the pitch of it and completely breaks the music)
            audio_push_cmd(0x40640000);
            audio_push_cmd(0xB0640073);
            audio_push_cmd(0x4150007F);
            audio_push_cmd(0xB1640073);
        }

        if (D_800EA174 == 680) {
            audio_push_cmd(0x100100FF);
        }

        if (D_800EA174 == 1050) {
            audio_push_cmd(0xB1500001);
            audio_push_cmd(0x51500001);
        }

        if (D_800EA174 == 1130) {
            audio_push_cmd(0x41320000);
        }

        if (D_800EA174 == 1200) { // (Player gets hit by the bomb-omb car; play the "explosion" sound effect and the "hurt" voice for the current character)
            audio_push_cmd(0x110100FF);
        }

        if (D_800EA174 == 1230) { // Once the music is completely broken by this point, play the "No Trophy For You!" sequence --- "Aw man, I lost... :("
            play_sequence(SEQ_EVENT_CEREMONY_TROPHY_LOSE);
            audio_push_cmd(0x4000007F); // (Play the "losing" voice for the current character, twice)
        }
    }
}

// run audio?
void audio_game_loop_tick() {
    audio_update_sound_source_cameras();
    audio_update_sequences();
    audio_process_cmd_buffer();
    audio_process_all_sound_requests();
    audio_process_sound_banks();
    audio_update_all_player_sounds();
    audio_process_sfx_script(0);
    eu_audio_cmd_flush();
}
