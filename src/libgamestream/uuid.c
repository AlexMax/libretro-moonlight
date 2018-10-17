/*
 * This file is part of Moonlight Embedded.
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

#include "uuid.h"

#include <stdio.h>
#include <string.h>

#include <openssl/rand.h>

typedef struct {
    uint32_t time_low;
    uint16_t time_mid;
    uint16_t time_hi_and_version;
    uint8_t clock_seq_hi_and_reserved;
    uint8_t clock_seq_low;
    uint8_t node[6];
} uuid_t;

#define UUID_BYTES 16
#define UUID_STRING_LEN (UUID_BYTES * 2 + 4 + 1)

/**
 * Generate a UUIDv4 string - the only kind this library needs
 */
bool gs_uuid_generate4_string(char *buffer, size_t length) {
    // Sanity check, make sure the destination buffer is the proper size
    if (length < UUID_STRING_LEN) {
        return false;
    }

    // Generate random bytes for UUID
    unsigned char random_buffer[UUID_BYTES];
    if (!RAND_bytes(&random_buffer[0], sizeof random_buffer)) {
        return false;
    }

    // Fill the uuid struct using bytes from secure RNG
    uuid_t uuid = { 0 };
    memcpy(&uuid.time_low, &random_buffer[0], sizeof uuid.time_low);
    memcpy(&uuid.time_mid, &random_buffer[4], sizeof uuid.time_mid);
    memcpy(&uuid.time_hi_and_version, &random_buffer[6], sizeof uuid.time_hi_and_version);
    memcpy(&uuid.clock_seq_hi_and_reserved, &random_buffer[8], sizeof uuid.clock_seq_hi_and_reserved);
    memcpy(&uuid.clock_seq_low, &random_buffer[9], sizeof uuid.clock_seq_low);
    memcpy(&uuid.node[0], &random_buffer[10], sizeof uuid.node);

    // These bytes designate the UUID string as v4
    uuid.time_hi_and_version = (uuid.time_hi_and_version & 0x0fff) | 0x4000;
    uuid.clock_seq_hi_and_reserved = (uuid.clock_seq_hi_and_reserved & 0x3f) | 0x40;

    // Turn the UUID bytes into a string
    int written = snprintf(buffer, length, "%08x-%04x-%04x-%04x-%02x%02x%02x%02x%02x%02x",
        uuid.time_low, uuid.time_mid, uuid.time_hi_and_version,
        uuid.clock_seq_hi_and_reserved, uuid.clock_seq_low,
        uuid.node[0], uuid.node[1], uuid.node[2],
        uuid.node[3], uuid.node[4], uuid.node[5]);
    if (written < UUID_STRING_LEN - 1) {
        return false;
    }

    return true;
}
