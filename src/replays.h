#ifndef STAFF_GHOSTS_H
#define STAFF_GHOSTS_H

#include <PR/os.h>
#include <common_structs.h>

void update_time_trial_replays(void);
void load_course_ghost(void);
void load_post_time_trial_replay(void);
void load_player_ghost(void);
void set_staff_ghost(void);
s32 compress_ghost_replay_data(void);
void decompress_player_ghost(void);
void swap_replay_buffers(void);
void init_time_trial_replay_state(void);
void process_post_time_trial_replay(void);
void process_course_ghost_replay(void);
void process_player_ghost_replay(void);
void set_player_to_cinematic_cpu(Player*);
void playback_post_time_trial_replays(void);
void replays_loop(void);

// mi0decode

extern s32 mio0encode(s32 input, s32, s32);
extern s32 mio0_encode_preprocess(void*, s32, s32);

extern s32 D_80162DC8;
extern s32 D_80162DCC;
extern u16 bPlayerGhostDisabled;
extern u16 bCourseGhostDisabled;
extern u16 D_80162DD8;
extern s32 D_80162E00;
extern s32 D_80162DE0;
extern s32 D_80162DE4;
extern s32 D_80162DE8;
extern s32 gPauseTriggered;
extern s32 gPostTimeTrialReplayCannotSave;

#endif /* STAFF_GHOSTS_H */
