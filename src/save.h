#ifndef SAVE_H
#define SAVE_H

#include <PR/os.h>
#include <common_structs.h>

/* define symbols */

#define CONTROLLER_1 0
#define CONTROLLER_2 1
#define CONTROLLER_3 2
#define CONTROLLER_4 3

#define PFS_NO_ERROR 0        // controller pak no error return
#define PFS_NO_PAK_INSERTED 1 // no pak pressent or wrong device inserted into the controller
#define PFS_PAK_BAD_READ 2    // controller pak error while data transfer
#define PFS_PAK_CORRUPTED 3   // controller pak has courrupted or has weird data
#define PFS_FILE_OVERFLOW 4   // too many files written to in the controller pak
#define PFS_INVALID_DATA -1   // bad arguments, game note does not exist, osPfsInit was not called
// controller pak test functions
#define PFS_NUM_FILES_ERROR -2
#define PFS_FREE_BLOCKS_ERROR -3
#define PFS_PAK_STATE_OK -4

#define NO_PAK 0
#define PAK 1
#define PAK_NOT_INSERTED -1

/* Function Prototypes */

void write_eeprom_course_time_trial_records(s32);
void write_save_data_grand_prix_points_and_sound_mode(void);
void reset_all_save_data_to_defaults(void);
void reset_course_time_trial_records(s32);
void reset_save_data_grand_prix_points_and_sound_mode(void);
u8 checksum_time_trial_records(s32);
s32 get_ghost_slot_index_for_course(s32);
s32 find_saved_ghost_index_for_course(s32);
s32 verify_ghost_candidate_match(s32);
u8 compute_save_data_checksum_1(void);
u8 compute_save_data_checksum_2(void);
void load_save_data(void);
void validate_and_recover_course_time_trials(s32);
void validate_save_data(void);
void populate_time_trial_record(u8* timeTrialRecord, u32 time, s32 characterId);
u32 unpack_time_trial_record(u8*);
s32 get_current_course_time_trial_record(s32);
u32 get_course_time_trial_record(s32, s32);
s32 get_current_course_best_lap_record(void);
s32 get_course_best_lap_record(s32);
s32 update_course_three_lap_records(u32, s32);
s32 update_course_best_single_lap_record(void);
void update_current_cup_grand_prix_points(s32);
void update_cup_grand_prix_points(s32, s32);
u8 get_cup_grand_prix_points(s32, s32);
u8 extract_cup_grand_prix_points(s32, s32);
u8 pack_cup_grand_prix_points(s32, s32, s32);
s32 is_cc_mode_complete(s32);
s32 has_unlocked_extra_mode(void);
s32 has_completed_extra_mode(void);
void write_eeprom_best_time_trial_records(s32);
u8 compute_best_time_trial_records_checksum_1(s32);
s32 compute_best_time_trial_records_checksum_2(s32);
s32 validate_best_time_trial_records_checksum(s32);
void update_save_data_backup(void);
u8 compute_save_data_checksum_backup_1(void);
u8 compute_save_data_checksum_backup_2(void);
s32 validate_save_data_checksum_backup(void);
s32 check_for_controller_pak(s32);
s32 controller_pak_1_status(void);
s32 controller_pak_2_status(void);
s32 probe_controller_pak_1(void);
s32 probe_controller_pak_2(void);
s32 save_ghost_header_to_pak(s32);
u8 calculate_ghost_page_checksum(s32);
s32 save_ghost_data_to_pak1(s32);
s32 load_ghost_data_from_pak1(s32);
s32 copy_ghost_data_from_pak2_to_buffer(s32, s32);
void load_and_validate_pak1_ghost_headers(void);
void load_and_validate_pak2_ghost_headers(void);
u8 calculate_pak1_ghost_header_checksum(s32);
u8 calculate_pak2_ghost_header_checksum(s32);
s32 clear_and_write_pak1_ghost_header(s32);
s32 allocate_pak1_ghost_file(void);

/* data */
// these might not be in this file, but for now...

extern u32* gReplayGhostCompressed;
extern struct_8018EE10_entry D_8018EE10[];

extern u16 gCompanyCode;
extern u32 gGameCode;           // osPfs gamecode
extern s8 gControllerPak1State; // Current state of Controller Pak 1

extern s8 sControllerPak2State; // Current state of the Controller Pak 2
extern const u8 D_800F2E60[];
extern const u8 gGameName[];
extern const u8 gExtCode[];
extern u16 D_80162DD6;
extern s32 D_80162DE0;
extern s32 D_80162DFC;
extern OSPfs gControllerPak1FileHandle;
extern OSPfs gControllerPak2FileHandle;
extern OSPfsState pfsState[16];
extern s32 pfsError[16];
extern s32 gControllerPak1NumFilesUsed;
extern s32 gControllerPak1MaxWriteableFiles;
extern s8 D_8018EDE5;
extern s8 D_8018EDE6;
extern s8 D_8018EDE7;

#endif /* CODE_800B045E0_H */
