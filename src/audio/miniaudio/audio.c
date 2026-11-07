#include "audio/miniaudio/audio.h"
extern "C" {
#define MA_NO_MP3
#define MA_NO_FLAC
#define MA_NO_ENCODING
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
}

#define ENGINE_SOUND_COUNT 8

static ma_engine engine;
static ma_sound engine_sounds[ENGINE_SOUND_COUNT];
static ma_sound skidding_sound;

int miniaudio_audio_open() {
	int i;
	const char *path;
	ma_result result;
	
	result = ma_engine_init(NULL, &engine);
	if (result != MA_SUCCESS) {
		fprintf(stderr, "ma_engine_init(): exited with code %d\n", result);
		return 1;
	}
	
	path = "sounds/f1sound1.wav";
	for (i = 0; i < ENGINE_SOUND_COUNT; i++) {
		result = ma_sound_init_from_file(&engine, path, MA_SOUND_FLAG_STREAM | MA_SOUND_FLAG_LOOPING, NULL, NULL, &engine_sounds[i]);
		if (result != MA_SUCCESS) {
			fprintf(stderr, "ma_sound_init_from_file(\"%s\"): exited with code %d\n", path, result);
			return 1;
		}
	}

	path = "sounds/skidding.wav";
	result = ma_sound_init_from_file(&engine, path, MA_SOUND_FLAG_STREAM | MA_SOUND_FLAG_LOOPING, NULL, NULL, &skidding_sound);
	if (result != MA_SUCCESS) {
		fprintf(stderr, "ma_sound_init_from_file(\"%s\"): exited with code %d\n", path, result);
		return 1;
	}

	return MINIAUDIO_SUCCESS;
}

void miniaudio_audio_start_engine_loop(int object_index) {
	ma_sound_start(&engine_sounds[object_index]);
}

void miniaudio_audio_stop_engine_loop(int object_index) {
	ma_sound_stop(&engine_sounds[object_index]);
	ma_sound_seek_to_pcm_frame(&engine_sounds[object_index], 0);
}

void miniaudio_audio_set_engine_attributes(int object_index, uint32_t pitch, uint16_t pan, int32_t volume) {
	ma_sound *sound = &engine_sounds[object_index];
	ma_sound_set_pitch(sound, (float)(pitch / 65536) / 128.0f);
	ma_sound_set_pan(sound, (float)pan / 32768.0f);
	ma_sound_set_volume(sound, (float)volume / 256.0f);
}

void miniaudio_audio_start_skidding_loop() {
	ma_sound_start(&skidding_sound);
}

void miniaudio_audio_stop_skidding_loop() {
	ma_sound_stop(&skidding_sound);
	ma_sound_seek_to_pcm_frame(&skidding_sound, 0);
}

void miniaudio_audio_set_skidding_loop_volume(int skidding_volume) {
	ma_sound_set_volume(&skidding_sound, (float)skidding_volume / 8.0f);
}

void miniaudio_audio_close() {
	int i;
	for (i = 0; i < ENGINE_SOUND_COUNT; i++) {
		ma_sound_uninit(&engine_sounds[i]);
	}
	ma_sound_uninit(&skidding_sound);
	ma_engine_uninit(&engine);
}
