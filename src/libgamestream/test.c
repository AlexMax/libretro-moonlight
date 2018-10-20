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

#include "client.h"
#include "errors.h"

#include <stdio.h>
#include <stdlib.h> // rand

int main() {
    SERVER_DATA server;
    int res = gs_init(&server, "127.0.0.1", ".", 0, false);
    if (res != GS_OK) {
        printf("gs_init: %d, %s\n", res, gs_error);
        return 1;
    }

    char pin[5];
    snprintf(pin, sizeof pin, "%d%d%d%d", rand() % 10, rand() % 10, rand() % 10, rand() % 10);

    printf("PIN: %s\n", pin);

    res = gs_pair(&server, &pin[0]);

    printf("gs_pair: %d, %s\n", res, gs_error);

    return 0;
}
