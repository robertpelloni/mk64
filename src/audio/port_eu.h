#ifndef AUDIO_PORT_EU_H
#define AUDIO_PORT_EU_H

#include "audio/internal.h"

#define SAMPLES_TO_OVERPRODUCE 0x10
#define EXTRA_BUFFERED_AI_SAMPLES_TARGET 0x40

void eu_process_audio_cmd(struct EuAudioCmd*);
void seq_player_fade_to_zero_volume(s32 arg0, s32 fadeOutTime);
void audio_fade_in_sequence_player(s32 playerIndex, s32 fadeInTime);
void port_eu_init_queues(void);
void eu_audio_cmd_send_raw(s32, s32*);
void eu_audio_cmd_send_f32(u32, f32);
void eu_audio_cmd_send_u32(u32, u32);
void eu_audio_cmd_send_byte(u32, s8);
void eu_audio_cmd_flush(void);
void audio_process_mac_cmds(u32 arg0);
void port_eu_init(void);

extern OSMesgQueue gAudioSyncQueue;
extern OSMesgQueue gAudioCmdQueue;
extern OSMesgQueue gAudioResetQueue;
extern OSMesgQueue gAudioResetQueue2;

extern struct EuAudioCmd sAudioCmd[0x100];

extern OSMesg gAudioSyncMesgBuf[];
extern OSMesg gAudioCmdMesgBuf[];
extern OSMesg gAudioResetMesgBuf[];
extern OSMesg gAudioResetMesgBuf2[];

extern OSMesgQueue* gAudioSyncQueuePtr;
extern OSMesgQueue* gAudioCmdQueuePtr;
extern OSMesgQueue* gAudioResetQueuePtr;
extern OSMesgQueue* gAudioResetQueue2Ptr;
extern s32 gMaxAudioCmds_eu;
extern s32 gMaxAudioCmdLength;

#endif
