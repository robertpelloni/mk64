# Changelog

All notable changes to this project will be documented in this file.

## [8.107.49] - 2026-06-02
### Changed
- Labeled player kart vertex squash/stretch, lighting tinting, and particle rendering dispatch routines across `src/render_player.c`, `src/render_player.h`, `src/main.c`, `src/player_controller.c`, `src/racing/skybox_and_splitscreen.c`, `src/ending/code_80281C40.c`, and `src/ending/podium_ceremony_actors.c`:
  - `func_8001F980` -> `get_camera_frustum_offsets`: Retrieves camera frustum check offset bounds.
  - `func_8001F9E4` -> `update_player_visibility_flags`: Sets camera visibility bitmasks for player kart viewports.
  - `func_8001FD78` -> `is_point_inside_kart_bounding_polygon`: Evaluates 2D triangular/polygonal collision with player kart bounds.
  - `func_80021B0C` -> `render_player_particles_screen_one`: Dispatches player particles for screen 1.
  - `func_80021C78` -> `render_player_particles_screen_two`: Dispatches player particles for screen 2.
  - `func_80021D40` -> `render_player_particles_screen_three`: Dispatches player particles for screen 3.
  - `func_80021DA8` -> `render_player_particles_screen_four`: Dispatches player particles for screen 4.
  - `func_80021F50` -> `mtxf_translate_vec3f`: Translates 4x4 matrix position by Vec3f.
  - `func_80022744` -> `update_player_render_state`: Top-level per-tick player render update hook.
  - `func_8002276C` -> `update_all_players_render_state`: Dispatches render state update across active players per screen mode.
  - `func_80022A98` -> `update_single_player_render_state`: Updates single player squash, palette, and bounce state.
  - `func_80022B50` -> `update_player_squish_physics`: Computes squash compression deformation physics.
  - `func_80022BC4` -> `update_player_post_squish_physics`: Computes post-squish decompression bounce oscillation.
  - `func_80022CA8` -> `deform_player_vertices_squish`: Deforms player sprite vertices for squish animation.
  - `func_80022D60` -> `deform_player_vertices_lakitu_carry`: Deforms player sprite vertices during Lakitu retrieval.
  - `func_80022DB4` -> `update_player_vertical_bounce_physics`: Computes standard vertical bounce oscillation physics.
  - `func_80022E84` -> `deform_player_vertices_bounce`: Deforms player sprite vertices for standard vertical bounce.
  - `func_800235AC` -> `update_player_color_effects`: Updates atmospheric light tinting and star/invincibility color cycling.
  - `func_80023BF0` -> `apply_player_vertex_deformations`: Dispatches vertex deformations based on squish, bounce, or Lakitu retrieval.

## [8.107.48] - 2026-06-02
### Changed
- Labeled camera follow positioning, Lakitu tracking, and dynamic FOV zoom routines in `src/camera.c`, `src/camera.h`, and `src/racing/skybox_and_splitscreen.c`:
  - `func_8001D53C` -> `camera_calculate_lakitu_retrieval_position`: Computes camera position and orientation during Lakitu retrieval.
  - `func_8001D794` -> `camera_calculate_reverse_look_position`: Computes reverse/behind camera lookAt and position.
  - `func_8001D944` -> `camera_calculate_close_follow_position`: Computes close-up behind camera follow position.
  - `func_8001E0C4` -> `camera_update_grid_start`: Updates camera during race countdown and grid positioning.
  - `func_8001E45C` -> `camera_update_normal_follow`: Updates camera in standard driving follow mode with drift angling.
  - `func_8001E8E8` -> `camera_update_lakitu_follow`: Updates camera when player kart is being transported by Lakitu.
  - `func_8001EA0C` -> `camera_update_close_follow`: Updates camera in close-up behind-the-kart driving mode.
  - `func_8001EE98` -> `camera_update_state_machine`: Dispatches per-frame camera state update machine based on game mode and pause state.
  - `func_8001F394` -> `camera_update_dynamic_fov_zoom`: Computes dynamic field-of-view zoom level based on speed, mushroom boosts, and squish triggers.
  - `func_8001F87C` -> `camera_check_grid_start_complete`: Checks if all Grand Prix karts have completed grid setup to transition camera to race follow mode.

## [8.107.47] - 2026-06-02
### Changed
- Labeled camera screen shake and position calculation routines across `src/camera.c`, `src/camera.h`, `src/player_controller.c`, and `src/update_objects.c`:
  - `func_8001CA10` -> `camera_trigger_screen_shake`: Triggers screen shake with default 6.0f intensity on camera.
  - `func_8001CA24` -> `player_trigger_screen_shake`: Triggers screen shake for the viewport camera belonging to `player` with specified intensity.
  - `func_8001CA78` -> `camera_calculate_grid_start_position`: Computes fixed starting grid track orientation and camera offset.
  - `func_8001CCEC` -> `camera_calculate_driving_follow_position`: Computes standard behind-the-kart driving camera follow position with vertical bounce and shake decay.

## [8.107.46] - 2026-06-02
### Changed
- Labeled ghost replay compression, decompression, buffer swapping, and cinematic player transition routines across `src/replays.c`, `src/replays.h`, `src/save.c`, `src/code_800029B0.c`, `src/menu_items.c`, `src/racing/race_logic.c`, and `asm/mio0_decode.s`:
  - `func_80040174` -> `mio0_encode_preprocess`: Pre-processes uncompressed buffer and constructs MIO0 lookup table.
  - `func_800051C4` -> `compress_ghost_replay_data`: Encodes and compresses ghost replay buffer with MIO0 for Controller Pak storage.
  - `func_8000522C` -> `decompress_player_ghost`: Decompresses saved ghost from compressed buffer into `sPlayerGhostReplay`.
  - `func_800052A4` -> `swap_replay_buffers`: Swaps active and standby replay buffer slots and tracks recorded length.
  - `func_80005310` -> `init_time_trial_replay_state`: Initializes ghost recording and playback states at the start of a time trial.
  - `func_80005AE8` -> `set_player_to_cinematic_cpu`: Disables human player input and converts target player kart to CPU cinematic mode.
  - `func_80005B18` -> `update_time_trial_replays`: Frame update loop processing ghost recording and active ghost playback during a race.
  - `func_80005E6C` -> `playback_post_time_trial_replays`: Frame update loop executing post-race time trial replay viewing.
  - Removed obsolete stray prototype `func_8000599C` from `src/replays.h`.

## [8.107.44] - 2026-06-02
### Changed
- Labeled audio memory allocation, sample DMA caching, and bank loading routines across `src/audio/load.c`, `src/audio/load.h`, `src/audio/heap.c`, `src/audio/heap.h`, `src/audio/port_eu.c`, and `src/audio/seqplayer.c`:
  - `func_800BB030` -> `init_sample_dma_buffers`: Allocates and initializes audio sample DMA buffers and reuse queues from `gNotesAndBuffersPool`.
  - `func_800BB304` -> `audio_dma_load_sample_immediate`: Immediately loads and DMAs audio sample into memory buffer.
  - `func_800BB388` -> `audio_load_instrument_samples_immediate`: Immediately loads samples for normal and high/low note ranges of an instrument or drum.
  - `func_800BB43C` -> `patch_seq_file`: Relocates sequence file offset pointers to base address.
  - `func_800BB584` -> `patch_audio_bank_by_id`: Patches audio bank instruments and drum table offsets by bank ID.
  - `func_800B90E0` -> `sound_alloc_pool_clear`: Resets sound allocation pool pointers and allocated count.
  - `func_800B914C` -> `session_pools_init`: Initializes session note/buffer and sequence/bank pools.
  - `func_800B9BE4` -> `audio_calculate_filter_coefficients`: Computes audio IIR/FIR filter coefficient arrays.
  - `func_800BA8B0` -> `audio_load_asset_to_pool`: Allocates memory and DMAs sequence or bank assets into `gUnkPool1`.

## [8.107.43] - 2026-06-02
### Changed
- Labeled coordinate rotation, inverse trigonometric, and camera override routines across `src/math_util_2.c`, `src/math_util_2.h`, `src/cpu_vehicles_camera_path.c`, `src/cpu_vehicles_camera_path.h`, `src/audio/external.c`, `src/code_80086E70.c`, and `src/update_objects.c`:
  - `func_800416D8` -> `rotate_xz_x`: Rotates coordinate in XZ plane: `(cos(angle) * x) - (sin(angle) * z)`.
  - `func_80041724` -> `rotate_xz_z`: Rotates coordinate in XZ plane: `(cos(angle) * z) + (sin(angle) * x)`.
  - `func_80041658` -> `atan2s_neg`: Computes negative arctangent `-atan2s(x, y) & 0xFFFF`.
  - `func_80041680` -> `atan2s_yx_1`: Computes arctangent `atan2s(y, x)`.
  - `func_800416AC` -> `atan2s_yx_2`: Computes arctangent `atan2s(y, x)`.
  - `func_8001AAAC` -> `camera_set_target_override`: Sets camera target player override request in `D_801646D0[cameraIndex]` triggered by audio sound script events.

## [8.107.42] - 2026-06-02
### Changed
- Labeled and documented screen transition, viewport fading, and demo sequence audio routines in `src/menu_items.c` and `src/menu_items.h`:
  - `func_8009CE1C` -> `menu_init_demo_audio`: Dispatches demo mode audio sequence command (0xE0000002) in multiplayer.
  - `func_8009CE64` -> `handle_screen_transition_complete`: Handles menu navigation or race state switches upon transition completion.
  - `func_8009D77C` -> `draw_fade_out`: Generic box-fill fade-out routine with custom color and alpha step.
  - `func_8009D958` -> `draw_black_fade_out`: Solid black box-fill fade out.
  - `func_8009D978` -> `draw_white_fade_out`: Solid white box-fill fade out.
  - `func_8009D998` -> `draw_black_box_viewport`: Draws solid black box covering player viewport.
  - `func_8009DAA8` -> `draw_screen_fade_out_step`: Full screen fade out animation step.
  - `func_8009DB8C` -> `draw_screen_mosaic_fade_out_step`: Full screen mosaic pixelation fade out step.
  - `func_8009DF6C` -> `start_screen_fade_in_alt`: Starts alternate screen fade-in type 8.

## [8.107.41] - 2026-06-02
### Changed
- Labeled MIO0 alternative decompressor and menu texture rectangle drawing routines in `include/decode.h`, `src/racing/memory.c`, `asm/unused_mio0_decode.s`, `src/menu_items.c`, `src/menu_items.h`, and `src/main.h`:
  - `func_80040030` -> `mio0decode_alt`: Alternative MIO0 decompressor variant.
  - `func_80095BD0` -> `render_textured_rectangle_4b_scaled`: Emits Fast3D matrix and 4-bit texture rectangle rendering display lists with scaling.
  - `func_80095E10` -> `render_textured_rectangle_16b`: Renders 16-bit texture rectangle tiles with power-of-two alignment.
  - `func_80096CD8` -> `render_course_preview_static_overlay`: Renders subtle static noise overlay during cup preview transitions.
  - `func_80097274` -> `render_textured_rectangle_multitile`: Emits 2-cycle multi-tile texture rendering with randomized noise mixing.
  - `func_80097A14` -> `render_textured_rectangle_16b_copy`: Renders 16-bit texture rectangle using Fast3D G_CYC_COPY mode.
  - `func_80097AE4` -> `render_textured_rectangle_split_horizontal`: Renders two-half split horizontally scaled texture rectangles.
  - `func_80097E58` -> `render_textured_rectangle_split_horizontal_scaled`: Renders multi-slice split horizontally scaled texture tiles.

## [8.107.40] - 2026-06-02
### Changed
- Labeled and documented final unnamed audio routines across `src/audio/external.c`, `src/audio/external.h`, `src/code_800029B0.c`, `src/player_controller.c`, and `src/update_objects.c`:
  - `func_800C13F0` -> `audio_dummy_nop`: Empty no-op function stub.
  - `func_800C86D8` -> `audio_play_player_lightning_recovery_voice`: Dispatches character voice line when recovery from lightning effect completes.
  - `func_800C89E4` -> `audio_update_ambient_volume_fade`: Ticks master volume fade-in and ducking states via timer `D_800EA180`.
  - `func_800C8AE4` -> `audio_update_tunnel_ambient_reverb`: Updates tunnel reverb and ducking transitions for Luigi Raceway and other tracks via `D_800EA184`.
  - `func_800C8C7C` -> `audio_update_player_effective_volume`: Computes per-player effective volume attenuation based on lightning distortion and master volume.
  - `func_800C8CCC` -> `audio_update_all_player_sounds`: Frame audio update iterating over active players to update engines, skids, surface sounds, finish fanfares, water splashes, and lightning distortion.
  - `func_800C8F44` -> `audio_set_music_volume`: Sets sequence player 0 volume target.
  - `func_800C8F80` -> `audio_play_player_sound_at_position`: Plays positional sound attached to a player while checking finish state and mute flags.

## [8.107.39] - 2026-06-02
### Changed
- Labeled and documented remaining unnamed save, time trial, and Grand Prix score routines in `src/save.c`, `src/save.h`, `src/menu_items.c`, `src/menus.c`, `src/replays.c`, and `src/code_8006E9C0.c`:
  - `func_800B4A9C` -> `validate_and_recover_course_time_trials`: Validates and recovers EEPROM time trial records for a specific course from the best records backup.
  - `func_800B4DF4` -> `unpack_time_trial_record`: Deserializes/unpacks a 3-byte time trial record into a 24-bit integer timestamp.
  - `func_800B4E24` -> `get_current_course_time_trial_record`: Retrieves an unpacked time trial record for the active cup & course.
  - `func_800B4EB4` -> `get_course_time_trial_record`: Retrieves an unpacked time trial record for an explicit course index.
  - `func_800B4F2C` -> `get_current_course_best_lap_record`: Retrieves the best single-lap time record for the active cup & course.
  - `func_800B4FB0` -> `get_course_best_lap_record`: Retrieves the best single-lap time record for an explicit course index.
  - `func_800B5020` -> `update_course_three_lap_records`: Inserts and updates top 5 three-lap race times in EEPROM.
  - `func_800B5218` -> `update_course_best_single_lap_record`: Checks completed laps to update the best single lap time record in EEPROM.
  - `func_800B536C` -> `update_current_cup_grand_prix_points`: Updates Grand Prix score in EEPROM and backup for the current cup/engine class.
  - `func_800B5404` -> `update_cup_grand_prix_points`: Updates Grand Prix score in EEPROM and backup for an explicit cup/engine class.
  - `func_800B54C0` -> `get_cup_grand_prix_points`: Fetches scored Grand Prix cup points for a specified cup and engine class.
  - `func_800B54EC` -> `extract_cup_grand_prix_points`: Bitwise extracts 2-bit cup score from packed CC points byte.
  - `func_800B5508` -> `pack_cup_grand_prix_points`: Bitwise packs 2-bit cup score into a CC points byte.
  - Removed obsolete stray prototype `func_800B5B2C` from `src/save.h`.

## [8.107.38] - 2026-06-02
### Changed
- Labeled best time trial record checksum calculation, validation, and EEPROM commit routines in `src/save.c`, `src/save.h`, `src/menus.c`, and `src/menu_items.c`:
  - `func_800B559C` -> `write_eeprom_best_time_trial_records`: Updates best 3-lap and single-lap times for cup block `x`, calculates checksums, and writes to EEPROM.
  - `func_800B578C` -> `compute_best_time_trial_records_checksum_1`: Calculates primary 51-byte checksum for `onlyBestTimeTrialRecords[arg0]`.
  - `func_800B5888` -> `compute_best_time_trial_records_checksum_2`: Calculates secondary checksum offset by +90.
  - `func_800B58C4` -> `validate_best_time_trial_records_checksum`: Validates primary and secondary checksums for `onlyBestTimeTrialRecords[arg0 / 8]`.

## [8.107.37] - 2026-06-02
### Changed
- Labeled 3D spatial sound emission, player vocalization, and spatial sound stopping routines in `src/audio/external.c` and `src/audio/external.h`:
  - `func_800C9250` -> `audio_play_player_random_voice`: Dispatches a randomized character voice line.
  - `func_800C92CC` -> `audio_play_player_speech_3d`: Allocates 3D audio node for each active camera viewport and plays speech line with Doppler/shock modulation.
  - `func_800C98B8` -> `audio_play_sound_at_position_3d`: Emits 3D positional sound effect with camera-relative spatialization.
  - `func_800C99E0` -> `audio_stop_sound_at_position_3d`: Stops active 3D sound instances at spatial coordinates across viewports.
  - `func_800C9D0C` -> `audio_stop_player_driving_sound_3d`: Stops driving engine loop sound at player's 3D position.
  - `func_800C9D80` -> `audio_play_looping_sound_at_position_3d`: Emits continuous looping positional sound with Doppler shifts.
  - `func_800C9EF4` -> `audio_stop_looping_sound_at_position_3d`: Stops continuous looping positional sounds across viewports.

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
