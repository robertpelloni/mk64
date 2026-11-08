# Changelog

All notable changes to this project will be documented in this file.

## [8.107.36] - 2026-06-02
### Changed
- Labeled player spatial sound and character voice playback/stop routines across audio, actor, menu, and player systems:
  - `func_800C9018` -> `audio_stop_player_sound`: Stops active sounds at a player's spatial coordinates (`&D_800E9F7C[playerIndex].pos`).
  - `func_800C9060` -> `audio_play_player_sound`: Plays sound effect attached to player position, checking mute states and setting tunnel reverberation.
  - `func_800C90F4` -> `audio_play_player_character_voice`: Plays character speech audio at player position, applying lightning shock frequency modulation if shocked.
- Updated all call sites across `src/audio/external.c`, `src/menus.c`, `src/menu_items.c`, `src/player_controller.c`, `src/racing/actors.c`, `src/racing/actors_extended.c`, `src/racing/race_logic.c`, `src/update_objects.c`, `src/code_80057C60.c`, `src/code_80086E70.c`, `src/ending/ceremony_and_credits.c`, and `src/effects.c`.

## [8.107.35] - 2026-06-02
### Changed
- Labeled EEPROM course time trial record write and save reset routines in `src/save.c`, `src/save.h`, and `src/menus.c`:
  - `func_800B45E0` -> `write_eeprom_course_time_trial_records`: Calculates checksum and writes `CourseTimeTrialRecords` to EEPROM using `osEepromLongWrite`.
  - `func_800B46D0` -> `reset_all_save_data_to_defaults`: Resets all 16 course time trial records, best time records, Grand Prix points, and updates save backup.
  - `func_800B4728` -> `reset_course_time_trial_records`: Fills course time trial record slots with default times from `D_800F2E60`, calculates checksum, and writes to EEPROM.

## [8.107.34] - 2026-06-02
### Changed
- Labeled ghost data disk read/write and Controller Pak transfer routines in `src/save.c`, `src/save.h`, `src/menus.c`, and `src/menu_items.c`:
  - `func_800B6178` -> `save_ghost_data_to_pak1`: Writes 0x3C00 bytes of compressed ghost data to Controller Pak 1, computes and sets rolling page checksums, and saves the ghost header entry.
  - `func_800B64EC` -> `load_ghost_data_from_pak1`: Reads 0x3C00 bytes of compressed ghost data from Controller Pak 1 into `gReplayGhostCompressed`, validates page checksums, and enables player ghost replay.
  - `func_800B65F4` -> `copy_ghost_data_from_pak2_to_buffer`: Reads ghost data from Controller Pak 2 into `gReplayGhostCompressed`, verifies page checksums, and stages metadata for copying to Pak 1.

## [8.107.33] - 2026-06-02
### Changed
- Labeled ghost slot lookup, course matching, and candidate verification routines in `src/save.c`, `src/save.h`, `src/menus.c`, and `src/menu_items.c`:
  - `func_800B6348` -> `get_ghost_slot_index_for_course`: Returns ghost slot (0 or 1) saving ghost data for the specified course.
  - `func_800B639C` -> `find_saved_ghost_index_for_course`: Finds matching ghost slot (0 or 1), or -1 if no saved ghost matches course.
  - `func_800B63F0` -> `verify_ghost_candidate_match`: Validates course index, ghost metadata, character ID, and page checksums against candidates.

## [8.107.32] - 2026-06-02
### Changed
- Labeled spatial sound cancellation, request processing, and channel volume scale updates in `src/audio/external.c` and `src/audio/external.h`:
  - `func_800C5384` -> `audio_stop_sounds_at_position_in_bank`: Stops active sound instances in target bank matching a specific position vector pointer.
  - `func_800C54B8` -> `audio_stop_and_cancel_sounds_at_position_in_bank`: Stops active sounds and cancels queued sound requests matching position in bank.
  - `func_800C550C` -> `audio_stop_all_sounds_at_position`: Stops all sound instances across all 6 sound banks associated with a given position vector.
  - `func_800C5578` -> `audio_stop_sound_at_position`: Stops specific sound bits at a given position vector and cancels matching requests.
  - `func_800C56F0` -> `audio_stop_sound_by_bits`: Stops specific sound bits across its bank and cancels matching requests.
  - `func_800C5848` -> `audio_process_all_pending_sound_requests`: Processes all unhandled sound requests in queue up to `sSoundRequestCount`.
  - `func_800C5968` -> `audio_update_channel_volume_scale_fade`: Ticks volume fade interpolation for a channel.
  - `func_800C59C4` -> `audio_update_all_sound_banks`: Iterates all sound banks to sort priorities, dispatch voices, and tick volume fades.

## [8.107.31] - 2026-06-02
### Changed
- Labeled sound request processing, sound bank priority sorting, and channel voice dispatch routines in `src/audio/external.c` and `src/audio/external.h`:
  - `func_800C41CC` -> `audio_cancel_matching_sound_requests`: Cancels queued sound requests matching filter conditions by zeroing out their soundBits and unlinking spatial nodes.
  - `func_800C4398` -> `audio_process_sound_requests`: Inserts newly requested sounds into destination sound banks with priority scoring and freshness parameters.
  - `func_800C4888` -> `audio_sort_sound_bank_priorities`: Evaluates sound distance and priority scores, selecting highest-priority active sounds to occupy hardware channels.
  - `func_800C4FE4` -> `audio_dispatch_active_sound_bank_channels`: Dispatches pitch, pan, volume, and note-on commands to hardware channels on SequencePlayer 2.
  - `func_800C5278` -> `audio_clear_sound_bank`: Stops and flushes all active sound instances within a target sound bank.

## [8.107.30] - 2026-06-02
### Changed
- Labeled 3D active sound relative position query and sequence script IO sync routines in `src/audio/external.c` and `src/audio/external.h`:
  - `func_800C21E8` -> `audio_get_active_3d_sound_relative_pos`: Queries active 3D sound nodes in `D_8018EFD8` matching sound coordinates and soundBits, returning a pointer to the relative orientation vector.
  - `func_800C2274` -> `audio_sync_sequence_script_io`: Reads sequence player channel script IO registers (`soundScriptIO[0..3]`) to synchronize music cues with camera cues and trigger gameplay sound sync events (`func_8001AAAC`).

## [8.107.29] - 2026-06-02
### Changed
- Labeled 3D spatial sound characteristics calculation routines (attenuation, reverb, pan, pitch variation, and channel push) in `src/audio/external.c` and `src/audio/external.h`:
  - `func_800C1480` -> `audio_calculate_distance_attenuation`: Computes distance-based volume attenuation factor 0.0f..1.0f.
  - `func_800C15D0` -> `audio_calculate_sound_reverb`: Computes distance-dependent reverb level clamped to 0x7F.
  - `func_800C16E8` -> `audio_calculate_sound_panning`: Computes stereo panning balance (0..127) based on sound relative X/Z coordinates.
  - `func_800C1934` -> `audio_calculate_random_pitch_variation`: Applies small random pitch variation if flag 0x800000 is present.
  - `func_800C19D0` -> `audio_apply_sound_characteristics_to_channel`: Combines volume attenuation, reverb, pitch, and pan, pushing updates to the audio channel queue.

## [8.107.28] - 2026-06-02
### Changed
- Labeled 3D spatial audio node allocation, camera relative orientation, Doppler pitch calculation, and periodic spatial updates in `src/audio/external.c` and `src/audio/external.h`:
  - `func_800C1C88` -> `audio_allocate_3d_sound_node`: Allocates an available slot from the 3D spatial node linked list (`D_8018EFD8`), assigning 3D coordinates, velocity vectors, sound bits, and camera associations.
  - `func_800C1DA4` -> `audio_calculate_sound_relative_camera_position`: Computes 3D relative positioning of a sound node rotated by camera yaw angle.
  - `func_800C1E2C` -> `audio_calculate_doppler_pitch_shift`: Calculates Doppler pitch shift factor (`unk2C`) based on camera and sound source relative motion vectors and sound speed.
  - `func_800C1F8C` -> `audio_update_3d_spatial_sounds`: Frame tick updater that recalculates camera velocities, updates active spatial node orientations/Doppler shifts, and frees inactive nodes back to the free list.

## [8.107.27] - 2026-06-02
### Changed
- Labeled surface skid effect selector routine in `src/audio/external.c` and `src/audio/external.h`:
  - `func_800C70A8` -> `audio_determine_surface_skid_effect`: Evaluates player tyres surface type (DIRT, SAND, BRIDGE, STONE, SNOW, ICE, ROPE_BRIDGE, WOOD_BRIDGE, TRAIN_TRACK, GRASS), drift status, and spinout flags, selecting the active sound index into `D_800E9E74[playerId]`.

## [8.107.26] - 2026-06-02
### Changed
- Labeled tyre squeal and offroad skid volume, frequency, and sound playback routines in `src/audio/external.c` and `src/audio/external.h`:
  - `func_800C64A0` -> `audio_update_skid_sound_volume`: Computes skid volume scalers `D_800E9EF4[playerId]` and `D_800E9F04[playerId]` based on kart surface type and speed.
  - `func_800C6758` -> `audio_update_skid_sound_frequency`: Computes dynamic pitch frequency scaler `D_800E9F14[playerId]` from kart drift/spin speed.
  - `func_800C683C` -> `audio_update_tyre_skid_sound`: Coordinates triggering sound effects (tyre squeal, spinout, dirt drift, grass drift) when skid state changes.

## [8.107.25] - 2026-06-02
### Changed
- Labeled player character sound bank initialization and kart throttle/pitch calculation routines in `src/audio/external.c` and `src/audio/external.h`:
  - `func_800C5BD0` -> `audio_init_player_sound_bank`: Dispatches command `0xF3000000` with the character voice sound bank ID from `D_800EA154[gPlayers[0].characterId]`.
  - `func_800C5D04` -> `audio_update_kart_throttle_timer`: Updates throttle on/off frame counters (`D_800E9E24[playerId]`, `D_800E9E34[playerId]`) and triggers engine idle audio on initial throttle press.
  - `func_800C5E38` -> `audio_update_kart_engine_rev_sound`: Manages kart deceleration and throttle release audio effects.
  - `func_800C6108` -> `audio_calculate_kart_engine_pitch`: Computes dynamic engine pitch scale `D_800E9E64[playerId]` from player engine RPM / unk_098 and forward speed.

## [8.107.24] - 2026-06-02
### Changed
- Labeled sequence player frame update, volume target, and setup cancel routines in `src/audio/external.c` and `src/audio/external.h`:
  - `func_800C3724` -> `audio_update_sequence_players`: Frame tick update executed every audio loop cycle; computes composite sequence player volumes and pushes volume/tempo updates.
  - `func_800C36C4` -> `seq_player_set_volume_target`: Configures sequence player sub-volume targets in `D_801930D0[seqPlayer].unk_00E[channel]` with transition frame duration.
  - `func_800C3608` -> `seq_player_cancel_setup_operations`: Cancels queued operations matching a given setup op code across the target sequence player.

## [8.107.23] - 2026-06-02
### Changed
- Labeled sequence player dispatch, start, stop, and active state query routines in `src/audio/external.c` and `src/audio/external.h`:
  - `func_800C284C` -> `seq_player_play_sequence`: Dispatches sequence playback command `0x82000000`, initializes sequence ID and priority in `D_801930D0[seqPlayer].unk_248`, and sets default channel volume states.
  - `func_800C29B4` -> `seq_player_stop_sequence`: Pushes sequence stop command `0x83000000` with fade duration and clears `unk_248`.
  - `func_800C2A2C` -> `audio_execute_sequence_command`: Command dispatcher parsing opcode switches (0..15) for sequence volume fades, channel masks, session resets, and sequence playback.
  - `func_800C3508` -> `seq_player_get_active_sequence_id`: Returns currently playing sequence ID for a given sequence player index, or -1 if inactive.
  - `func_800C357C` -> `audio_is_sequence_command_pending`: Scans sequence command ring buffer for matching command.
  - `func_800C35E8` -> `seq_player_clear_queued_count`: Resets the active queued sequence count in `D_80192CC6[player]`.

## [8.107.22] - 2026-06-02
### Changed
- Labeled audio course sequence initialization and race finish status handlers in `src/audio/external.c`, `src/audio/external.h`, `src/code_800029B0.c`, `src/menus.c`, `src/ending/ceremony_and_credits.c`, `src/effects.c`, `src/cpu_vehicles_camera_path.c`, and `src/menu_items.c`:
  - `func_800CA008` -> `audio_init_course_sequence`: Adjusts volume channels, determines sequence index by course ID/game mode, and dispatches the corresponding sequence command.
  - `func_800CA24C` -> `audio_set_player_finish_state`: Updates `D_800EA0EC[playerIndex] = 2` to signal that player has completed their race.
  - `func_800CA270` -> `audio_set_race_finish_flag`: Sets global finish flag `D_800EA0F4 = 1`.
- Cleaned up obsolete symbol declarations and updated callsites across racing, awards, and menu logic.

## [8.107.21] - 2026-06-02
### Changed
- Labeled Controller Pak ghost file allocation and entry clearing routines in `src/save.c`, `src/save.h`, `src/menus.c`, and `src/menu_items.c`:
  - `func_800B69BC` -> `clear_and_write_pak1_ghost_header`: Clears a ghost header slot in `D_8018EE10[arg0]`, computes header checksum, and writes to Controller Pak 1 via `osPfsReadWriteFile`.
  - `func_800B6A68` -> `allocate_pak1_ghost_file`: Allocates the 0x7900 byte ghost note on Controller Pak 1 using `osPfsAllocateFile` and clears both ghost header slots.
- Updated all callsites in file management menus (`options_menu_act`, `course_data_menu_act`) and menu item handlers.

## [8.107.20] - 2026-06-02
### Changed
- Labeled Controller Pak ghost header validation and checksum functions in `src/save.c`, `src/save.h`, `src/menus.c`, and `src/menu_items.c`:
  - `func_800B6708` -> `load_and_validate_pak1_ghost_headers`: Reads ghost headers from Controller Pak 1 into `D_8018EE10` via `osPfsReadWriteFile` and verifies checksums.
  - `func_800B6798` -> `load_and_validate_pak2_ghost_headers`: Reads ghost headers from Controller Pak 2 into `gSomeDLBuffer` and verifies checksums.
  - `func_800B6828` -> `calculate_pak1_ghost_header_checksum`: Calculates checksum for Pak 1 ghost header entry `D_8018EE10[arg0]`.
  - `func_800B68F4` -> `calculate_pak2_ghost_header_checksum`: Calculates checksum for Pak 2 ghost header entry in `gSomeDLBuffer`.
- Updated all callsites across options menu pak copy logic and time trial ghost menus.

## [8.107.19] - 2026-06-02
### Changed
- Labeled Controller Pak 2 probe and ghost save/checksum routines in `src/save.c`, `src/save.h`, `src/menus.c`, and `src/menu_items.c`:
  - `func_800B6014` -> `probe_controller_pak_2`: Probes controller pak 2 insertion state (`sControllerPak2State`) and initialises `&gControllerPak2FileHandle` using `osPfsInit`.
  - `func_800B6088` -> `save_ghost_header_to_pak`: Computes header checksum via `func_800B6828` and writes the 128-byte `struct_8018EE10_entry` header into Controller Pak 1.
  - `func_800B60E8` -> `calculate_ghost_page_checksum`: Calculates rolling checksum for a 256-byte page of compressed ghost data in `gReplayGhostCompressed`.
- Cleaned up call sites across time-trial ghost saving and menu pak management.

## [8.107.18] - 2026-06-02
### Changed
- Labeled Controller Pak 1 status probe function in `src/save.c`, `src/save.h`, `src/menu_items.c`, and `src/menus.c`:
  - `func_800B5F30` -> `probe_controller_pak_1`: Probes controller pak 1 status (`gControllerPak1State`), initialises PFS via `osPfsInitPak`, checks file state, and populates `gControllerPak1Files`.
- Labeled Grand Prix CPU setup and rival character selection functions in `src/cpu_vehicles_camera_path.c`, `src/cpu_vehicles_camera_path.h`, `src/menu_items.c`, and `src/menus.c`:
  - `func_8000F0E0` -> `reset_cpu_camera_path_indices`: Clears CPU vehicle waypoint and camera path tracking indices.
  - `func_8000F124` -> `select_grand_prix_rival_characters`: Selects and assigns non-human rival racer characters for Grand Prix mode based on current character table rankings.
- Cleaned up obsolete symbol declarations and updated all callsites across save and menu systems.

## [8.107.17] - 2026-06-02
### Changed
- Labeled screen transition visual fader routines in `src/menu_items.c` and `src/menu_items.h`:
  - `func_8009DEF8` -> `start_screen_fade_in_type`: Custom duration/type fade-in on transition channel 4.
  - `func_8009DF4C` -> `start_screen_fade_in`: Default type 1 fade-in.
  - `func_8009DF8C` -> `start_screen_fade_out_type`: Custom duration/type fade-out on transition channel 4.
  - `func_8009DFE0` -> `start_screen_fade_out`: Default type 2 fade-out used across menus and transitions.
  - `func_8009E000` -> `start_screen_fade_out_alt`: Alternate type 7 fade-out.
  - `func_8009E020` -> `start_channel_fade_in`: Per-channel fade-in (used in `effects.c` for screen-specific player effects).
  - `func_8009E088` -> `start_channel_fade_out`: Per-channel fade-out (used in `effects.c`).
  - `func_8009E0F0` -> `start_screen_mosaic_fade_out`: Low-res mosaic pixelation fade-out in `sTKMK00_LowResBuffer`.
  - `func_8009E17C` -> `start_screen_transition_type_4`.
- Updated all callsites in `src/menus.c` and `src/effects.c`.

## [8.107.16] - 2026-06-01
### Changed
- Labeled menu transition fade helper routines in `src/menu_items.c`, `src/menu_items.h`, and `src/menus.c`:
  - `func_8009E1C0` -> `set_menu_fade_main`: Triggers a 10-frame screen fade and sets `gMenuFadeType = MENU_FADE_TYPE_MAIN`.
  - `func_8009E1E4` -> `set_menu_fade_main_alt`: Triggers alternative screen fade and sets `gMenuFadeType = MENU_FADE_TYPE_MAIN`.
  - `func_8009E208` -> `set_menu_fade_back`: Triggers a 10-frame screen fade and sets `gMenuFadeType = MENU_FADE_TYPE_BACK`.
  - `func_8009E230` -> `set_menu_fade_demo`: Triggers fade and sets `gMenuFadeType = MENU_FADE_TYPE_DEMO`.
  - `func_8009E258` -> `set_menu_fade_data`: Triggers fade and sets `gMenuFadeType = MENU_FADE_TYPE_DATA`.
  - `func_8009E280` -> `set_menu_fade_option`: Triggers fade and sets `gMenuFadeType = MENU_FADE_TYPE_OPTION`.
- Updated all declarations and call sites across `src/menu_items.c`, `src/menu_items.h`, and `src/menus.c`.

## [8.107.15] - 2026-05-31
### Changed
- Labeled sequence player settings and bank mask routines in `src/audio/external.c`:
  - `func_800C3F70` -> `audio_reset_all_sequence_player_settings`: Resets sequence player structures, volumes, tempo scales, and channel masks across players 0..2.
  - `func_800C400C` -> `audio_reset_soft_sequence_player_settings`: Performs lightweight reset preserving volume scales while zeroing pending command queues and tempo states.
  - `func_800C4084` -> `audio_set_sound_banks_enabled_mask`: Enables/disables sound banks according to provided bitmask in `sSoundBankDisabled`.
  - `func_800C40F0` -> `audio_clear_sound_channel_active_bit`: Clears channel bit in `D_800EA1C4` and restores sequence player volume when all channels are inactive.
- Updated callsites across `src/audio/external.c` and prototypes in `src/audio/external.h`.

## [8.107.14] - 2026-05-30
### Changed
- Synchronized `SUBMODULE_INVENTORY.md` with active pinned submodule commits across `doxygen-awesome-css` (v2.5.0, `46483f1`), `tools/asm-differ` (`0dd09af`), `tools/blender/fast64` (`b130109`), `tools/decomp-permuter` (`8556c81`), and `tools/torch` (`7f5d55f`).
- Verified full tool compilation (`make -C tools`) for Torch asset pipeline.

## [8.107.13] - 2026-05-29
### Changed
- Labeled audio sequence command buffer and universal fade-out routines:
  - `func_800CA330` -> `audio_fade_out_all_sequences`: Triggers rapid or timed sequence fadeouts across sequence players 0 and 1 throughout menu navigation and race transitions.
  - `func_800C3448` -> `audio_push_sequence_command`: Queues an encoded 32-bit sequence playback or volume command into `D_80192CD0`.
  - `func_800C3478` -> `audio_process_sequence_commands`: Flushes and dispatches all buffered sequence commands during `audio_game_loop_tick`.
- Updated prototypes and callsites in `src/audio/external.c`, `src/audio/external.h`, `src/menus.c`, `src/menu_items.c`, and `src/racing/race_logic.c`.

## [8.107.12] - 2026-05-28
### Changed
- Labeled race finish and post-race sequence audio routines:
  - `func_800CA118` -> `audio_trigger_race_finish`: Triggers finish state audio for winning/finishing karts across Grand Prix and Battle modes in `src/racing/race_logic.c`.
  - `func_800C76C0` -> `audio_update_race_finish_sequences`: Progresses post-finish timer `D_800E9EA4`, plays character win/lose jingles, and transitions background music to results screens.
- Updated prototypes and callsites in `src/audio/external.c`, `src/audio/external.h`, and `src/racing/race_logic.c`.

## [8.107.11] - 2026-05-27
### Changed
- Labeled audio subsystem initialization and reset routines:
  - `func_800C5CB8` -> `audio_init`: Master audio system startup function called prior to the main game loop in `src/main.c`.
  - `func_800C5C40` -> `audio_soft_reset`: Resets audio states, camera orientation vectors, and sound channels during course restarts and scene loads.
  - `func_800C2474` -> `audio_reset_state_and_cameras`: Resets audio camera copy structures (`gCopyCamera`), velocity vectors, and player tire surface state.
- Updated prototypes and callsites in `src/audio/external.c`, `src/audio/external.h`, and `src/main.c`.

## [8.107.10] - 2026-05-26
### Changed
- Labeled tunnel acoustics reverberation and final lap fanfare audio routines:
  - `func_800CA49C` -> `audio_play_final_lap_fanfare`: Plays the final lap sequence fanfare and speeds up race music upon lap 2 completion in `src/racing/race_logic.c`.
  - `func_800CA288` -> `audio_set_player_tunnel_reverb`: Applies wet reverberation parameters to human player audio inside enclosed tunnel waypoints (e.g. Mario Raceway, Choco Mountain, Koopa Beach, Yoshi Valley).
  - `func_800CA2B8` -> `audio_clear_player_tunnel_reverb`: Restores dry acoustics upon exiting tunnel segments.
  - `func_800CA2E4` -> `audio_set_cpu_tunnel_reverb`: Sets tunnel reverberation for CPU karts in `D_800EA06C`.
  - `func_800CA30C` -> `audio_clear_cpu_tunnel_reverb`: Clears CPU tunnel reverberation.
- Updated all callsites and declarations in `src/audio/external.c`, `src/audio/external.h`, `src/player_controller.c`, and `src/racing/race_logic.c`.

## [8.107.9] - 2026-05-25
### Changed
- Labeled player-specific audio events and kart engine sound loops:
  - `func_800C847C` -> `audio_update_player_submerged_sound`: Handles player splash sounds, voicelines, and pitch modulation upon submerged fluid entry or falling out-of-bounds.
  - `func_800C8770` -> `audio_update_player_lightning_distortion`: Adjusts audio distortion and channel volume ducking while shock status (`LIGHTNING_EFFECT`) is active.
  - `func_800C94A4` -> `audio_play_kart_engine_idle`: Starts and parameterizes idle/rev engine sounds for character karts.
  - `func_800C97C4` -> `audio_stop_kart_engine_sound`: Stops active engine audio channels for a player.
  - `func_800C9A88` -> `audio_play_kart_engine_driving`: Initiates dynamic driving engine playback loop with velocity tracking.
- Updated all call sites and prototypes across `src/audio/external.c`, `src/audio/external.h`, `src/player_controller.c`, and `src/menu_items.c`.

## [8.107.8] - 2026-05-24
### Changed
- Labeled audio mute and sound bank cleanup routines:
  - `func_800C9F90` -> `audio_set_pause_mute`: Mutes/unmutes audio sequences and tracks pause mute state in `D_800EA16C`.
  - `func_800CA0A0` -> `audio_mute_sfx_enable`: Enables SFX mute flag (`D_800EA108 = 1`).
  - `func_800CA0B8` -> `audio_mute_sfx_disable`: Disables SFX mute flag (`D_800EA108 = 0`).
  - `func_800CA0CC` -> `audio_mute_sfx_enable_cutscene`: Cutscene-specific wrapper to activate SFX mute.
  - `func_800CA0E4` -> `audio_clear_sound_banks`: Purges audio banks 3 and 5 during sequence transitions.
- Updated all call sites and prototypes across `src/audio/external.c`, `src/audio/external.h`, `src/racing/race_logic.c`, `src/menu_items.c`, and `src/ending/ceremony_and_credits.c`.

## [8.107.7] - 2026-05-23
### Changed
- Labeled audio command queue and sequence fade routines in `src/audio/port_eu.c` and `src/audio/port_eu.h`:
  - `func_800CBB48` -> `audio_cmd_queue_push`: Pushes an audio command into the command ring buffer `sAudioCmd`.
  - `func_800CBB88` -> `audio_cmd_queue_push_f32`: Pushes command with 32-bit floating point payload (e.g. channel volumes).
  - `func_800CBBB8` -> `audio_cmd_queue_push_u32`: Pushes command with 32-bit unsigned payload (e.g. sequence loading and sound modes).
  - `func_800CBBE8` -> `audio_cmd_queue_push_s8`: Pushes command with 8-bit signed payload (e.g. panning/channel options).
  - `func_800CBC24` -> `audio_cmd_queue_flush`: Flushes queued audio commands to the audio execution thread via message queue.
  - `func_800CBCB0` -> `audio_cmd_queue_process`: Dispatches and executes queued commands in the audio synthesis loop.
  - `func_800CBA64` -> `seq_player_fade_in`: Initiates volume fade-in sequence over specified frames.
- Updated callsites across `src/audio/external.c` and `src/audio/external.h`.

## [8.107.6] - 2026-05-22
### Changed
- Labeled audio subsystem engine functions:
  - `func_800CB2C4` -> `audio_game_loop_tick`: Main audio update tick executed once per game loop.
  - `func_800CAC08` -> `reset_thunder_sound_effect`: Resets thunder/lightning volume and active sound state.
  - `func_800C8920` -> `check_and_reset_thunder_effect`: Checks all players for the active lightning effect and resets audio once extinguished.
  - `func_800CB134` -> `trigger_losing_ceremony_sequence`: Initiates losing podium presentation sequence timer.
  - `func_800CADD0` -> `play_kart_landing_sound_effect`: Sound effect triggered when karts land from hops/falls with intensity scaling.
- Cleaned and updated calling sites across `src/main.c`, `src/menus.c`, `src/code_800029B0.c`, `src/player_controller.c`, and `src/ending/ceremony_and_credits.c`.

## [8.107.5] - 2026-05-21
### Changed
- Labeled sound effect and music control functions in `src/audio/external.c` (`play_star_music`, `stop_star_music`, `play_star_sound_effect`, `play_star_music_stop_effect`, `play_star_sound_effect_stop`, `play_thunder_sound_effect`, `play_thunder_sound_effect_stop`, `set_player_sound_effect_volume`, `play_boo_sound_effect`, `stop_boo_sound_effect`).

## [8.107.4] - 2026-05-20
### Removed
- Removed the `bobcoin` submodule to decouple unused blockchain experimental UI from the core engine repo.
### Changed
- Standardized AI documentation referencing the Omni-Workspace guidelines.

## [8.107.3] - 2026-05-20
### Fixed
- Identified `func_800CA388` as audio channel scaler and mapped it to `fade_all_channel_volume_scale` in `src/menus.c`.

## [8.107.2] - 2026-05-19
### Updated
- Synced `tools/torch` and `tools/blender/fast64` submodules to latest upstream commits.
