# Session Handoff - 2026-06-02 (v8.107.22)

## Executive Summary
Completed decompilation labeling of course sequence initialization and race finish status handlers across `src/audio/external.c`, `src/audio/external.h`, `src/code_800029B0.c`, `src/menus.c`, `src/ending/ceremony_and_credits.c`, `src/effects.c`, `src/cpu_vehicles_camera_path.c`, and `src/menu_items.c`. Verified with static C syntax checking, and bumped the project version to `8.107.22`.

### Recent Fixes & Additions
- **Audio Course Sequence & Race Finish Status Routines (v8.107.22):**
  - `func_800CA008` -> `audio_init_course_sequence`: Adjusts volume channels, determines sequence index by course ID/game mode, and dispatches the corresponding sequence command.
  - `func_800CA24C` -> `audio_set_player_finish_state`: Updates `D_800EA0EC[playerIndex] = 2` to signal that player has completed their race.
  - `func_800CA270` -> `audio_set_race_finish_flag`: Sets global finish flag `D_800EA0F4 = 1`.
- **Controller Pak Ghost File Allocation & Entry Clearing Routines (v8.107.21):**
  - `func_800B69BC` -> `clear_and_write_pak1_ghost_header`: Clears a ghost header slot in `D_8018EE10[arg0]`, computes header checksum, and writes to Controller Pak 1 via `osPfsReadWriteFile`.
  - `func_800B6A68` -> `allocate_pak1_ghost_file`: Allocates the 0x7900 byte ghost note on Controller Pak 1 using `osPfsAllocateFile` and clears both ghost header slots.
- **Controller Pak Ghost Header Validation & Checksum Routines (v8.107.20):**
  - `func_800B6708` -> `load_and_validate_pak1_ghost_headers`: Reads ghost headers from Pak 1 into `D_8018EE10` and validates checksums.
  - `func_800B6798` -> `load_and_validate_pak2_ghost_headers`: Reads ghost headers from Pak 2 into `gSomeDLBuffer` and validates checksums.
  - `func_800B6828` -> `calculate_pak1_ghost_header_checksum`: Calculates checksum for Pak 1 ghost header entry `D_8018EE10[arg0]`.
  - `func_800B68F4` -> `calculate_pak2_ghost_header_checksum`: Calculates checksum for Pak 2 ghost header entry in `gSomeDLBuffer`.
- **Controller Pak 2 Probe & Ghost Checksum Routines (v8.107.19):**
  - `func_800B6014` -> `probe_controller_pak_2`: Probes controller pak 2 insertion state (`sControllerPak2State`) and initialises `&gControllerPak2FileHandle` using `osPfsInit`.
  - `func_800B6088` -> `save_ghost_header_to_pak`: Computes header checksum via `func_800B6828` and writes the 128-byte `struct_8018EE10_entry` header into Controller Pak 1.
  - `func_800B60E8` -> `calculate_ghost_page_checksum`: Calculates rolling checksum for a 256-byte page of compressed ghost data in `gReplayGhostCompressed`.
- **Controller Pak & Grand Prix Selection Routines (v8.107.18):**
  - `func_800B5F30` -> `probe_controller_pak_1`: Checks controller pak 1 initialization status (`gControllerPak1State`), initialises PFS via `osPfsInitPak`, checks file state, and sets `gControllerPak1Files`.
  - `func_8000F0E0` -> `reset_cpu_camera_path_indices`: Clears CPU vehicle waypoint and camera path tracking indices.
  - `func_8000F124` -> `select_grand_prix_rival_characters`: Selects and assigns non-human rival racer characters for Grand Prix mode based on current character table rankings.
- **Screen Transition Visual Faders (v8.107.17):**
  - `func_8009DEF8` -> `start_screen_fade_in_type`: Custom duration/type fade-in on transition channel 4.
  - `func_8009DF4C` -> `start_screen_fade_in`: Default type 1 fade-in.
  - `func_8009DF8C` -> `start_screen_fade_out_type`: Custom duration/type fade-out on transition channel 4.
  - `func_8009DFE0` -> `start_screen_fade_out`: Default type 2 fade-out used across menus and transitions.
  - `func_8009E000` -> `start_screen_fade_out_alt`: Alternate type 7 fade-out.
  - `func_8009E020` -> `start_channel_fade_in`: Per-channel fade-in (used in `effects.c` for screen-specific player effects).
  - `func_8009E088` -> `start_channel_fade_out`: Per-channel fade-out (used in `effects.c`).
  - `func_8009E0F0` -> `start_screen_mosaic_fade_out`: Low-res mosaic pixelation fade-out in `sTKMK00_LowResBuffer`.
  - `func_8009E17C` -> `start_screen_transition_type_4`.
- **Menu Screen Transition & Fade Handlers (v8.107.16):**
  - Labeled `set_menu_fade_main`, `set_menu_fade_main_alt`, `set_menu_fade_back`, `set_menu_fade_demo`, `set_menu_fade_data`, and `set_menu_fade_option`.
- **Audio Sequence Player Settings & Bank Mask Routines (v8.107.15):**
  - Labeled `audio_reset_all_sequence_player_settings`, `audio_reset_soft_sequence_player_settings`, `audio_set_sound_banks_enabled_mask`, and `audio_clear_sound_channel_active_bit`.
- **Submodule Inventory Alignment (v8.107.14):**
  - Synchronized `SUBMODULE_INVENTORY.md` across all submodules.
- **Audio Sequence Command Buffer & Fadeouts (v8.107.13):**
  - Labeled `audio_fade_out_all_sequences`, `audio_push_sequence_command`, and `audio_process_sequence_commands`.
- **Race Finish and Results Sequence Audio Labeling (v8.107.12):**
  - `audio_trigger_race_finish` and `audio_update_race_finish_sequences`.
- **Audio Initialization & State Resets (v8.107.11):**
  - `audio_init`, `audio_soft_reset`, and `audio_reset_state_and_cameras`.
- **Tunnel Acoustics & Final Lap Audio Labeling (v8.107.10):**
  - `audio_play_final_lap_fanfare`, `audio_set_player_tunnel_reverb`, `audio_clear_player_tunnel_reverb`, `audio_set_cpu_tunnel_reverb`, and `audio_clear_cpu_tunnel_reverb`.
- **Kart Engine & Player Physics Audio Labeling (v8.107.9):**
  - `audio_update_player_submerged_sound`, `audio_update_player_lightning_distortion`, `audio_play_kart_engine_idle`, `audio_stop_kart_engine_sound`, and `audio_play_kart_engine_driving`.
- **Audio Mute & Sound Bank Routine Renaming (v8.107.8):**
  - `audio_set_pause_mute`, `audio_mute_sfx_enable`, `audio_mute_sfx_disable`, `audio_mute_sfx_enable_cutscene`, and `audio_clear_sound_banks`.
- **Audio Port EU Command Queue Renaming (v8.107.7):**
  - `audio_cmd_queue_push_*`, `audio_cmd_queue_flush`, `audio_cmd_queue_process`, and `seq_player_fade_in`.
- **Environment & Build Infrastructure:**
  - Installed MIPS cross-compilers (`binutils-mips-linux-gnu`, `gcc-mips-linux-gnu`).
  - Verified Torch and recompilation tools build cleanly (`make -C tools`).
  - Zero syntax errors confirmed across all updated files.

## Next Steps for Implementor
1. **Zero-Latency Rust Bridge:** Review the `TODO.md` backlog regarding the porting of collision logic (`src/racing/`) into native Rust routines to circumvent N64 physics limitations.
2. **Continue C Renaming:** Continue mapping remaining `func_800...` routines in `src/audio` (spatial positioning, sound banks) and `src/racing` (collision and course rendering).
