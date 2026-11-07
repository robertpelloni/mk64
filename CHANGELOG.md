# Changelog

All notable changes to this project will be documented in this file.

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
