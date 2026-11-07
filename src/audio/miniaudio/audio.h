#ifndef __AUDIO_MINIAUDIO_AUDIO_H
#define __AUDIO_MINIAUDIO_AUDIO_H

#include <inttypes.h>

#define MINIAUDIO_SUCCESS 0

int miniaudio_audio_open();
void miniaudio_audio_start_engine_loop(int object_index);
void miniaudio_audio_stop_engine_loop(int object_index);
void miniaudio_audio_set_engine_attributes(int object_index, uint32_t pitch,uint16_t pan,int32_t volume);
void miniaudio_audio_start_skidding_loop();
void miniaudio_audio_stop_skidding_loop();
void miniaudio_audio_set_skidding_loop_volume(int skidding_volume);
void miniaudio_audio_close();

#endif

