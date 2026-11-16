#ifndef STAFF_GHOSTS_H
#define STAFF_GHOSTS_H

#include <PR/os.h>
#include <common_structs.h>

void check_and_finalize_ghost_data(void);
void load_course_ghost(void);
void load_post_time_trial_replay(void);
void load_player_ghost(void);
void set_staff_ghost(void);
s32 encode_ghost_data(void);
void decode_ghost_data(void);
void swap_ghost_buffer_index(void);
void init_ghost_data(void);
void process_post_time_trial_replay(void);
void process_course_ghost_replay(void);
void process_player_ghost_replay(void);
void init_ghost_player(Player*);
void update_ghost_replays(void);
void replays_loop(void);

// mi0decode

extern s32 mio0encode(s32 input, s32, s32);
extern s32 func_80040174(void*, s32, s32);

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
