/*
 * This file is part of libretro-moonlight.
 *
 * Copyright (C) 2018 Alex Mayfield
 *
 * Moonlight is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Moonlight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Moonlight; if not, see <http://www.gnu.org/licenses/>.
 */

#include "client.h"
#include "errors.h"

#include "video/ffmpeg.h"

#include <stdio.h>
#include <stdlib.h> // rand

void stage_starting(int stage) {
    printf("%s, %d\n", __FUNCTION__, stage);
}

void stage_complete(int stage) {
    printf("%s %d\n", __FUNCTION__, stage);
}

void stage_failed(int stage, long errorCode) {
    printf("%s %d %d\n", __FUNCTION__, stage, errorCode);
}

void connection_started(void) {
    printf("%s\n", __FUNCTION__);
}

void connection_terminated(long errorCode) {
    printf("%s %d\n", __FUNCTION__, errorCode);
}

void display_message(const char* message) {
    printf("%s %s\n", __FUNCTION__, message);
}

void display_transient_message(const char* message) {
    printf("%s %s\n", __FUNCTION__, message);
}

void log_message(const char* format, ...) {
    char buffer[8192];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    printf("%s %s\n", __FUNCTION__, buffer);
}

CONNECTION_LISTENER_CALLBACKS connection_callbacks_libretro = {
    stage_starting, // stageStarting
    stage_complete, // stageComplete
    stage_failed, // stageFailed
    connection_started, // connectionStarted
    connection_terminated, // connectionTerminated
    display_message, // displayMessage
    display_transient_message, // displayTransientMessage
    log_message // logMessage
};

int decoder_setup(int videoFormat, int width, int height, int redrawRate, void* context, int drFlags) {
    printf("%s\n", __FUNCTION__);

    int avc_flags = SLICE_THREADING;
    if (ffmpeg_init(videoFormat, width, height, avc_flags, 2, 1) != 0) {
        printf("ffmpeg_init failure\n");
        return -1;
    }

    return 0;
}

void decoder_start(void) {
    printf("%s\n", __FUNCTION__);
}

void decoder_stop(void) {
    printf("%s\n", __FUNCTION__);
}

void decoder_cleanup(void) {
    printf("%s\n", __FUNCTION__);
    ffmpeg_destroy();
}

int decoder_submit_decode_unit(PDECODE_UNIT decodeUnit) {
    printf("%s\n", __FUNCTION__);
}

DECODER_RENDERER_CALLBACKS decoder_callbacks_libretro = {
    decoder_setup, // setup
    decoder_start, // start
    decoder_stop, // stop
    decoder_cleanup, // cleanup
    decoder_submit_decode_unit, // submitDecodeUnit
    CAPABILITY_SLICES_PER_FRAME(4) // capabilities
};

int main() {
    bool config_sops;
    bool config_localaudio;

    SERVER_DATA server;
    int res = gs_init(&server, "127.0.0.1", ".", 2, false);
    if (res != GS_OK) {
        printf("gs_init: %d, %s\n", res, gs_error);
        return 1;
    }

    char pin[5];
    snprintf(pin, sizeof pin, "%d%d%d%d", rand() % 10, rand() % 10, rand() % 10, rand() % 10);

    printf("PIN: %s\n", pin);

    res = gs_pair(&server, &pin[0]);
    if (res != GS_OK) {
        printf("gs_pair: %d, %s\n", res, gs_error);
        //return 1;
    }

    PAPP_LIST list = NULL;
    res = gs_applist(&server, &list);
    if (res != GS_OK) {
        printf("gs_applist: %d, %s\n", res, gs_error);
        return 1;
    }

    for (int i = 1; list != NULL; i++) {
        printf("%d. %s\n", list->id, list->name);
        list = list->next;
    }

    STREAM_CONFIGURATION config_stream;
    LiInitializeStreamConfiguration(&config_stream);
    config_stream.width = 1920;
    config_stream.height = 1080;
    config_stream.fps = 60;

    // AppID 1088017781 is Steam on my PC - start it
    res = gs_start_app(&server, &config_stream, 1088017781, config_sops, config_localaudio, 1);
    if (res != GS_OK) {
        printf("gs_start_app: %d, %s\n", res, gs_error);
        return 1;
    }

    CONNECTION_LISTENER_CALLBACKS connection_callbacks;
    LiInitializeConnectionCallbacks(&connection_callbacks);
    memcpy(&connection_callbacks, &connection_callbacks_libretro, sizeof(connection_callbacks));

    DECODER_RENDERER_CALLBACKS decoder_callbacks;
    LiInitializeVideoCallbacks(&decoder_callbacks);
    memcpy(&decoder_callbacks, &decoder_callbacks_libretro, sizeof(decoder_callbacks));

    AUDIO_RENDERER_CALLBACKS audio_callbacks;
    LiInitializeAudioCallbacks(&audio_callbacks);

    // Start the gamestream connection
    LiStartConnection(&server.serverInfo, &config_stream, &connection_callbacks,
        &decoder_callbacks, &audio_callbacks, NULL, 0, NULL, 0);

    while(true) {
        _sleep(1);
    }

    return 0;
}
