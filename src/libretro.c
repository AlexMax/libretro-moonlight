#include <string.h>

#include "libretro.h"

RETRO_API void retro_set_environment(retro_environment_t cb) {
    bool no_rom = true;
    cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_rom);
}

RETRO_API void retro_set_video_refresh(retro_video_refresh_t cb) {

}

RETRO_API void retro_set_audio_sample(retro_audio_sample_t cb) {

}

RETRO_API void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) {

}

RETRO_API void retro_set_input_poll(retro_input_poll_t cb) {

}

RETRO_API void retro_set_input_state(retro_input_state_t cb) {

}

RETRO_API void retro_init(void) {
    return;
}

RETRO_API void retro_deinit(void) {
    return;
}

RETRO_API unsigned retro_api_version(void) {
    return RETRO_API_VERSION;
}

RETRO_API void retro_get_system_info(struct retro_system_info *info) {
    memset(info, 0, sizeof(*info));
    info->library_name = "Moonlight";
    info->library_version = "0.1.0";
    info->valid_extensions = "";
    info->need_fullpath = false;
    info->block_extract = false;
}

RETRO_API void retro_get_system_av_info(struct retro_system_av_info *info) {
    memset(info, 0, sizeof(*info));
    info->geometry.base_width = 1280;
    info->geometry.base_height = 720;
    info->geometry.max_width = 1280;
    info->geometry.max_height = 720;
    info->geometry.aspect_ratio = 0.0;
    info->timing.fps = 60;
    info->timing.sample_rate = 44100;
}

RETRO_API void retro_set_controller_port_device(unsigned port, unsigned device) {

}

RETRO_API void retro_reset(void) {

}

RETRO_API void retro_run(void) {

}

RETRO_API size_t retro_serialize_size(void) {
    return 0;
}

RETRO_API bool retro_serialize(void *data, size_t size) {
    return false;
}

RETRO_API bool retro_unserialize(const void *data, size_t size) {
    return false;
}

RETRO_API void retro_cheat_reset(void) {
    return;
}

RETRO_API void retro_cheat_set(unsigned index, bool enabled, const char *code) {
    return;
}

RETRO_API bool retro_load_game(const struct retro_game_info *game) {
    return true;
}

RETRO_API bool retro_load_game_special(
    unsigned game_type,
    const struct retro_game_info *info, size_t num_info
) {
    return true;
}

RETRO_API void retro_unload_game(void) {
    return;
}

RETRO_API unsigned retro_get_region(void) {
    return RETRO_REGION_NTSC;
}

RETRO_API void *retro_get_memory_data(unsigned id) {
    return NULL;
}

RETRO_API size_t retro_get_memory_size(unsigned id) {
    return 0;
}
