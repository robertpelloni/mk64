#include <ultra64.h>
#include <macros.h>
#include <PR/ucode.h>

#include "audio/synthesis.h"
#include "audio/seqplayer.h"
#include "audio/port_eu.h"
#include "audio/load.h"
#include "audio/heap.h"
#include "audio/data.h"

OSMesgQueue gAudioSyncQueue;
OSMesgQueue gAudioCmdQueue;
OSMesgQueue gAudioResetQueue;
OSMesgQueue gAudioResetQueue2;

struct EuAudioCmd sAudioCmd[0x100];

// Seems oversized by 1
OSMesg gAudioSyncMesgBuf[2];
OSMesg gAudioCmdMesgBuf[4];
OSMesg gAudioResetMesgBuf[1];
OSMesg gAudioResetMesgBuf2[1];

u8 gAudioCmdWriteIndex[] = { 0, 0, 0, 0 };

u8 gAudioCmdReadIndex[] = { 0, 0, 0, 0 };

OSMesgQueue* gAudioSyncQueuePtr = &gAudioSyncQueue;
OSMesgQueue* gAudioCmdQueuePtr = &gAudioCmdQueue;
OSMesgQueue* gAudioResetQueuePtr = &gAudioResetQueue;
OSMesgQueue* gAudioResetQueue2Ptr = &gAudioResetQueue2;

char port_eu_unused_string0[] = "DAC:Lost 1 Frame.\n";
char port_eu_unused_string1[] = "DMA: Request queue over.( %d )\n";
char port_eu_unused_string2[] = "DMA [ %d lines] TIMEOUT\n";
char port_eu_unused_string3[] = "Warning: WaveDmaQ contains %d msgs.\n";
char port_eu_unused_string4[] = "Audio:now-max tasklen is %d / %d\n";
char port_eu_unused_string5[] = "Audio:Warning:ABI Tasklist length over (%d)\n";

s32 gMaxAudioCmds_eu = 128;

char port_eu_unused_string6[] = "AudioSend: %d -> %d (%d)\n";

s32 gMaxAudioCmdLength = 0;

char port_eu_unused_string7[] = "Undefined Port Command %d\n";

struct SPTask* create_next_audio_frame_task(void) {
    u32 samplesRemainingInAI;
    s32 writtenCmds;
    s32 index;
    OSTask_t* task;
    s32 var_s0;
    s16* currAiBuffer;
    s32 oldDmaCount;
    OSMesg sp58;
    OSMesg sp54;
    s32 writtenCmdsCopy;

    gAudioFrameCount++;
    if ((gAudioFrameCount % gAudioBufferParameters.presetUnk4) != 0) {
        return NULL;
    }
    osSendMesg(gAudioSyncQueuePtr, (OSMesg) gAudioFrameCount, OS_MESG_NOBLOCK);

    gAudioTaskIndex ^= 1;
    gCurrAiBufferIndex++;
    gCurrAiBufferIndex %= NUMAIBUFFERS;
    index = (gCurrAiBufferIndex + 1) % NUMAIBUFFERS;
    samplesRemainingInAI = osAiGetLength() / 4;

    if (gAiBufferLengths[index] != 0) {
        osAiSetNextBuffer(gAiBuffers[index], gAiBufferLengths[index] * 4);
    }
    oldDmaCount = gCurrAudioFrameDmaCount;
    for (var_s0 = 0; var_s0 < gCurrAudioFrameDmaCount; var_s0++) {
        if (osRecvMesg(&gCurrAudioFrameDmaQueue, NULL, 0) == 0) {
            oldDmaCount -= 1;
        }
    }
    if (oldDmaCount != 0) {
        for (var_s0 = 0; var_s0 < oldDmaCount; var_s0++) {
            osRecvMesg(&gCurrAudioFrameDmaQueue, NULL, 1);
        }
    }
    oldDmaCount = gCurrAudioFrameDmaQueue.validCount;
    if (oldDmaCount != 0) {
        for (var_s0 = 0; var_s0 < oldDmaCount; var_s0++) {
            osRecvMesg(&gCurrAudioFrameDmaQueue, NULL, 0);
        }
    }
    gCurrAudioFrameDmaCount = 0;
    decrease_sample_dma_ttls();
    if (osRecvMesg(gAudioResetQueuePtr, &sp58, 0) != -1) {
        gAudioResetPresetIdToLoad = (u8) (u32) sp58;
        gAudioResetStatus = 5;
    }
    if (gAudioResetStatus != 0) {
        if (audio_shut_down_and_reset_step() == 0) {
            if (gAudioResetStatus == 0) {
                osSendMesg(gAudioResetQueue2Ptr, (OSMesg) (u32) gAudioResetPresetIdToLoad, OS_MESG_NOBLOCK);
            }
            return NULL;
        }
    }

    gAudioTask = &gAudioTasks[gAudioTaskIndex];
    gAudioCmd = gAudioCmdBuffers[gAudioTaskIndex];
    index = gCurrAiBufferIndex;
    currAiBuffer = gAiBuffers[index];
    gAiBufferLengths[index] =
        ((gAudioBufferParameters.samplesPerFrameTarget - samplesRemainingInAI + EXTRA_BUFFERED_AI_SAMPLES_TARGET) &
         ~0xF) +
        SAMPLES_TO_OVERPRODUCE;
    if (gAiBufferLengths[index] < gAudioBufferParameters.minAiBufferLength) {
        gAiBufferLengths[index] = gAudioBufferParameters.minAiBufferLength;
    }
    if (gAiBufferLengths[index] > gAudioBufferParameters.maxAiBufferLength) {
        gAiBufferLengths[index] = gAudioBufferParameters.maxAiBufferLength;
    }
    if (osRecvMesg(gAudioCmdQueuePtr, &sp54, 0) != -1) {
        audio_process_mac_cmds((u32) sp54);
    }
    gAudioCmd = synthesis_execute((Acmd*) gAudioCmd, &writtenCmds, currAiBuffer, gAiBufferLengths[index]);
    gAudioRandom = osGetCount() * (gAudioRandom + gAudioFrameCount);
    gAudioRandom = gAudioRandom + gAiBuffers[index][gAudioFrameCount & 0xFF];

    index = gAudioTaskIndex;
    gAudioTask->msgqueue = NULL;
    // wtf?
    writtenCmdsCopy += 0;
    gAudioTask->msg = NULL;

    task = &gAudioTask->task.t;
    task->type = M_AUDTASK;
    task->flags = 0;
    task->ucode_boot = rspF3DBootStart;
    task->ucode_boot_size = (u8*) rspF3DBootEnd - (u8*) rspF3DBootStart;
    task->ucode = rspAspMainStart;
    task->ucode_data = rspAspMainDataStart;
    task->ucode_size = 0x1000; // (This size is ignored (according to sm64))
    task->ucode_data_size = (rspAspMainDataEnd - rspAspMainDataStart) * sizeof(u64);
    task->dram_stack = NULL;
    task->dram_stack_size = 0;
    task->output_buff = NULL;
    task->output_buff_size = NULL;
    task->data_ptr = (u64*) gAudioCmdBuffers[index];
    task->data_size = writtenCmds * sizeof(u64);
    task->yield_data_ptr = NULL;
    task->yield_data_size = 0;
    writtenCmdsCopy = writtenCmds;
    if (gMaxAudioCmds_eu < writtenCmds) {
        gMaxAudioCmds_eu = writtenCmdsCopy;
    }
    return gAudioTask;
}

void eu_process_audio_cmd(struct EuAudioCmd* cmd) {
    s32 i;

    switch (cmd->u.s.op) {
        case 0x81:
            preload_sequence(cmd->u.s.arg2, 3);
            break;

        case 0x82:
        case 0x88:
            load_sequence(cmd->u.s.bankId, cmd->u.s.arg2, cmd->u.s.arg3);
            audio_fade_in_sequence_player(cmd->u.s.bankId, cmd->u2.as_s32);
            break;

        case 0x83:
            if (gSequencePlayers[cmd->u.s.bankId].enabled != false) {
                if (cmd->u2.as_s32 == 0) {
                    sequence_player_disable(&gSequencePlayers[cmd->u.s.bankId]);
                } else {
                    seq_player_fade_to_zero_volume(cmd->u.s.bankId, cmd->u2.as_s32);
                }
            }
            break;

        case 0xf0:
            gAudioLibSoundMode = cmd->u2.as_s32;
            break;

        case 0xf1:
            for (i = 0; i < 4; i++) {
                gSequencePlayers[i].muted = true;
                gSequencePlayers[i].recalculateVolume = true;
            }
            break;

        case 0xf2:
            for (i = 0; i < 4; i++) {
                gSequencePlayers[i].muted = false;
                gSequencePlayers[i].recalculateVolume = true;
            }
            break;
        case 0xF3:
            audio_preload_instrument(cmd->u.s.bankId, cmd->u.s.arg2, cmd->u.s.arg3);
            break;
    }
}

void seq_player_fade_to_zero_volume(s32 arg0, s32 fadeOutTime) {
    struct SequencePlayer* player;

    if (fadeOutTime == 0) {
        fadeOutTime = 1;
    }
    player = &gSequencePlayers[arg0];
    player->state = 2;
    player->fadeRemainingFrames = fadeOutTime;
    player->fadeVelocity = -(player->fadeVolume / fadeOutTime);
}

void audio_fade_in_sequence_player(s32 playerIndex, s32 fadeInTime) {
    struct SequencePlayer* player;

    if (fadeInTime != 0) {
        player = &gSequencePlayers[playerIndex];
        player->state = 1;
        player->fadeTimerUnkEu = fadeInTime;
        player->fadeRemainingFrames = fadeInTime;
        player->fadeVolume = 0.0f;
        player->fadeVelocity = 0.0f;
    }
}

void port_eu_init_queues(void) {
    gAudioCmdWriteIndex[0] = 0;
    gAudioCmdReadIndex[0] = 0;
    osCreateMesgQueue(gAudioSyncQueuePtr, gAudioSyncMesgBuf, 1);
    osCreateMesgQueue(gAudioCmdQueuePtr, gAudioCmdMesgBuf, 4);
    osCreateMesgQueue(gAudioResetQueuePtr, gAudioResetMesgBuf, 1);
    osCreateMesgQueue(gAudioResetQueue2Ptr, gAudioResetMesgBuf2, 1);
}

void eu_audio_cmd_send_raw(s32 arg0, s32* arg1) {
    struct EuAudioCmd* cmd = &sAudioCmd[gAudioCmdWriteIndex[0] & 0xff];
    cmd->u.first = arg0;
    cmd->u2.as_u32 = *arg1;
    gAudioCmdWriteIndex[0]++;
}

void eu_audio_cmd_send_f32(u32 arg0, f32 arg1) {
    eu_audio_cmd_send_raw(arg0, (s32*) &arg1);
}

void eu_audio_cmd_send_u32(u32 arg0, u32 arg1) {
    eu_audio_cmd_send_raw(arg0, (s32*) &arg1);
}

void eu_audio_cmd_send_byte(u32 arg0, s8 arg1) {
    s32 sp34 = arg1 << 24;
    eu_audio_cmd_send_raw(arg0, &sp34);
}

//! @todo clenanup, something's weird with the variables. gMaxAudioCmdLength is probably EuAudioCmd bc of the + 0x100
void eu_audio_cmd_flush(void) {
    s32 temp_t6;
    s32 test;
    OSMesg thing;
    temp_t6 = gAudioCmdWriteIndex[0] - gAudioCmdReadIndex[0];
    test = (u8) temp_t6;
    test = (test + 0x100) & 0xFF;
    do {
    } while (0);
    if (gMaxAudioCmdLength < test) {
        gMaxAudioCmdLength = test;
    }
    thing = (OSMesg) ((gAudioCmdWriteIndex[0] & 0xFF) | ((gAudioCmdReadIndex[0] & 0xFF) << 8));
    osSendMesg(gAudioCmdQueuePtr, thing, 0);
    gAudioCmdReadIndex[0] = gAudioCmdWriteIndex[0];
}

void audio_process_mac_cmds(u32 arg0) {
    struct EuAudioCmd* cmd;
    struct SequencePlayer* seqPlayer;
    struct SequenceChannel* chan;
    u8 end = arg0 & 0xff;
    u8 i = (arg0 >> 8) & 0xff;

    for (;;) {
        if (i == end) {
            break;
        }
        cmd = &sAudioCmd[i++ & 0xff];

        if ((cmd->u.s.op & 0xf0) == 0xf0) {
            eu_process_audio_cmd(cmd);
            goto why;
        }

        if (cmd->u.s.bankId < SEQUENCE_PLAYERS) {
            seqPlayer = &gSequencePlayers[cmd->u.s.bankId];
            if ((cmd->u.s.op & 0x80) != 0) {
                eu_process_audio_cmd(cmd);
            } else if ((cmd->u.s.op & 0x40) != 0) {
                switch (cmd->u.s.op) {
                    case 0x41:
                        seqPlayer->fadeVolumeScale = cmd->u2.as_f32;
                        seqPlayer->recalculateVolume = true;
                        break;

                    case 0x47:
                        seqPlayer->tempo = cmd->u2.as_s32 * TATUMS_PER_BEAT;
                        break;

                    case 0x48:
                        seqPlayer->transposition = cmd->u2.as_s8;
                        break;

                    case 0x46:
                        seqPlayer->seqVariationEu[cmd->u.s.arg3] = cmd->u2.as_s8;
                        break;
                }
            } else if (seqPlayer->enabled != false && cmd->u.s.arg2 < 0x10) {
                chan = seqPlayer->channels[cmd->u.s.arg2];
                if (IS_SEQUENCE_CHANNEL_VALID(chan)) {
                    switch (cmd->u.s.op) {
                        case 1:
                            chan->volumeScale = cmd->u2.as_f32;
                            chan->changes.as_bitfields.volume = true;
                            break;
                        case 2:
                            chan->volume = cmd->u2.as_f32;
                            chan->changes.as_bitfields.volume = true;
                            break;
                        case 3:
                            chan->newPan = cmd->u2.as_s8;
                            chan->changes.as_bitfields.pan = true;
                            break;
                        case 4:
                            chan->freqScale = cmd->u2.as_f32;
                            chan->changes.as_bitfields.freqScale = true;
                            break;
                        case 5:
                            chan->reverbVol = cmd->u2.as_s8;
                            break;
                        case 6:
                            if (cmd->u.s.arg3 < 8) {
                                chan->soundScriptIO[cmd->u.s.arg3] = cmd->u2.as_s8;
                            }
                            break;
                        case 8:
                            chan->stopSomething2 = cmd->u2.as_s8;
                    }
                }
            }
        }

    why:
        cmd->u.s.op = 0;
    }
}

void port_eu_init() {
    port_eu_init_queues();
}
