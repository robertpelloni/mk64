# Session Handoff - 2026-06-02 (v8.107.25)

## Executive Summary
Completed decompilation labeling of character sound bank initialization, throttle counter tracking, and dynamic engine pitch calculation routines across `src/audio/external.c` and `src/audio/external.h`. Verified with static C syntax checking, and bumped the project version to `8.107.25`.

### Recent Fixes & Additions
- **Player Voice Bank & Kart Engine Dynamics Audio Routines (v8.107.25):**
  - `func_800C5BD0` -> `audio_init_player_sound_bank`: Dispatches command `0xF3000000` with the character voice sound bank ID from `D_800EA154[gPlayers[0].characterId]`.
  - `func_800C5D04` -> `audio_update_kart_throttle_timer`: Updates throttle on/off frame counters (`D_800E9E24[playerId]`, `D_800E9E34[playerId]`) and triggers engine idle audio on initial throttle press.
  - `func_800C5E38` -> `audio_update_kart_engine_rev_sound`: Manages kart deceleration and throttle release audio effects.
  - `func_800C6108` -> `audio_calculate_kart_engine_pitch`: Computes dynamic engine pitch scale `D_800E9E64[playerId]` from player engine RPM / unk_098 and forward speed.
- **Sequence Player Volume & Setup Update Routines (v8.107.24):**
  - `func_800C3724` -> `audio_update_sequence_players`: Audio tick updater that computes composite sequence player volumes and pushes volume/tempo updates.
  - `func_800C36C4` -> `seq_player_set_volume_target`: Configures sequence player sub-volume targets in `D_801930D0[seqPlayer].unk_00E[channel]` with transition frame duration.
  - `func_800C3608` -> `seq_player_cancel_setup_operations`: Cancels queued operations matching a given setup op code across the target sequence player.
- **Sequence Player Control & Command Dispatcher Routines (v8.107.23):**
  - `func_800C284C` -> `seq_player_play_sequence`: Dispatches sequence playback command `0x82000000`, initializes sequence ID and priority in `D_801930D0[seqPlayer].unk_248`, and sets default channel volume states.
  - `func_800C29B4` -> `seq_player_stop_sequence`: Pushes sequence stop command `0x83000000` with fade duration and clears `unk_248`.
  - `func_800C2A2C` -> `audio_execute_sequence_command`: Command dispatcher parsing opcode switches (0..15) for sequence volume fades, channel masks, session resets, and sequence playback.
  - `func_800C3508` -> `seq_player_get_active_sequence_id`: Returns currently playing sequence ID for a given sequence player index, or -1 if inactive.
  - `func_800C357C` -> `audio_is_sequence_command_pending`: Scans sequence command ring buffer for matching command.
  - `func_800C35E8` -> `seq_player_clear_queued_count`: Resets the active queued sequence count in `D_80192CC6[player]`.
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
