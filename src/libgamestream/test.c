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

int main() {
    char uuid[37];

    if (!gs_uuid_generate4_string(&uuid[0], sizeof(uuid))) {
        printf("error!\n");
        return 1;
    }

    printf("%s", uuid);

    return 0;
}
