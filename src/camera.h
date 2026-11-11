#ifndef CAMERA_H
#define CAMERA_H

#include <common_structs.h>

/**
 * @todo put this define in types.h or similar.
 * Certain functions are marked as having return values, but do not
 * actually return a value. This causes undefined behavior, which we'd rather
 * avoid on modern GCC. This only impacts -O2 and can matter for both the function
 * itself and functions that call it.
 */
#ifdef AVOID_UB
#define BAD_RETURN(cmd) void
#else
#define BAD_RETURN(cmd) cmd
#endif

typedef struct {
    f32 unk_0;
    s16 unk_4;
    s16 unk_6;
    s16 unk_8;
} UnkCameraInner;

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3f lookAt;
    // This is expected to be a normalized vector, indicates what direction is "up" for the camera
    /* 0x18 */ Vec3f up;
    // I think these are the "nautical angles" between pos and lookAt
    // rot[0] = roll? Does nothing?, rot[1] = yaw, rot[2] = pitch
    /* 0x24 */ Vec3s rot;
    /* 0x2A */ u16 someBitFlags;
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ Vec3f unk_30;
    /* 0x3C */ Vec3f unk_3C;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ Collision collision;
    // When you hit a wall (or another driver) the camera's pos and lookAt bounce up and down. This is the velocity(?)
    // of that bouncing
    /* 0x94 */ UnkCameraInner unk_94;
    // Timer for wall-hit bounce. Counts up instead of down
    /* 0xA0 */ f32 unk_A0;
    /* 0xA4 */ s32 unk_A4;
    /* 0xA8 */ s32 unk_A8;
    /* 0xAC */ s16 unk_AC;
    // Id of the player the camera is following.
    /* 0xAE */ s16 playerId;
    // Seems related to camera movement during drifting
    /* 0xB0 */ s16 unk_B0;
    /* 0xB2 */ s16 unk_B2;
    /* 0xB4 */ f32 unk_B4;
} Camera; /* size = 0xB8 */

void camera_init(f32, f32, f32, s16, u32, s32);
void camera_trigger_screen_shake(Camera*);
void player_trigger_screen_shake(Player*, f32);
void camera_calculate_grid_start_position(Player*, Camera*, Vec3f, f32*, f32*, f32*, s32, s32);
void camera_calculate_driving_follow_position(Player*, Camera*, Vec3f, f32*, f32*, f32*, s32*, s16, s16);
void camera_calculate_lakitu_retrieval_position(Player*, Camera*, Vec3f, f32*, f32*, f32*, s16, s16);
void camera_calculate_reverse_look_position(Player*, Camera*, Vec3f, f32*, f32*, f32*, s16);
void camera_calculate_close_follow_position(Player*, Camera*, Vec3f, f32*, f32*, f32*, s32*, s16, s16);
void camera_update_grid_start(Camera*, Player*, s8);
void camera_update_normal_follow(Camera*, Player*, s8);
void camera_update_lakitu_follow(Camera*, Player*, s8);
void camera_update_close_follow(Camera*, Player*, s8);
void camera_update_state_machine(Player*, Camera*, s8);
void camera_update_dynamic_fov_zoom(Player*, f32*);
void camera_check_grid_start_complete(s32);

extern f32 D_800DDB30[];

extern Camera cameras[];
extern Camera* camera1;
extern Camera* camera2;
extern Camera* camera3;
extern Camera* camera4;

// end of camera.c variables

extern s8 D_80164A89;

extern s32 D_80164A08[4];

extern s32 D_80164A28;
extern s32 D_80164A2C;
extern f32 D_80164A30;
extern f32 D_80164A90[];
extern f32 D_80164AA0[];

#endif
