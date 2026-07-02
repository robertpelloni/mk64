#ifndef RACE_LOGIC_H
#define RACE_LOGIC_H

/* Function Prototypes */

void check_player_player_collision(Player*, Player*);
void func_8028DF00(void);
void func_8028DF38(void);
void func_8028E028(void);
void update_player_battle_status(void);
void func_8028E298(void);
void func_8028E3A0(void);
void func_8028E438(void);
void func_8028E678(void);
void func_8028EC38(s32);
void play_music_for_current_track(s32);
void start_race(void);
f32 func_8028EE8C(s32);
void func_8028EEF0(s32);
void func_8028EF28(void);
void func_8028F3E8(void);
void update_race_position_data(void);
void func_8028F474(void);
void func_8028F4E8(void);
void func_8028F588(void);
void func_8028F8BC(void);
void func_8028F914(void);
void func_8028F970(void);
void func_8028FBD4(void);
void end_demo_update(void);
void update_race_state_machine(void);
void quit_to_start_menu(void);
void quit_to_main_menu(void);
void quit_to_player_select_menu(void);
void quit_to_course_select_menu(void);
void trigger_restart_race(void);
void evaluate_all_player_collisions(void);
void update_all_cameras(void);

extern f32 gLapCompletionPercentByPlayerId[];
extern s32 gGPCurrentRaceRankByPlayerId[]; // D_801643B8 (position for each player)

#endif
