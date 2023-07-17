//
// Created by cprkan on 7/17/23.
//

#include <memory.h>
#include "voxel_handler.h"

void ray_cast(camera_t camera, chunk_t* chunk, double mouse_x, double mouse_y, int screen_width, int screen_height) {

    vec3 temp_point;

    glm_vec3_copy(camera.positions, temp_point);

    ivec3 direction = {(int)(((camera.forward[0] * 360) + (MAX_RAY_DIST * BLOCK_SIZE)) / BLOCK_SIZE),
                       (int)(((camera.forward[1] * 360) + (MAX_RAY_DIST * BLOCK_SIZE)) / BLOCK_SIZE),
                       (int)(((camera.forward[2] * 360) + (MAX_RAY_DIST * BLOCK_SIZE)) / BLOCK_SIZE)};
    while (temp_point[0] != direction[0] &&
            temp_point[1] != direction[1] &&
            temp_point[2] != direction[2]) {

        if (temp_point[0] >= direction[0] &&
            temp_point[1] >= direction[1] &&
            temp_point[2] >= direction[2]) {
            printf("%d, %d, %d\n", (int)(temp_point[0] / 32) + direction[0] - 17, (
                    int)(temp_point[1] / 32) + direction[1] - 6, (int)(temp_point[2] / 32) + direction[2] - 6);

            int x = (int)(temp_point[0] / 32) + direction[0] - 17;
            int y = (int)(temp_point[1] / 32) + direction[1] - 6;
            int z = (int)(temp_point[2] / 32) + direction[2] - 6;

            int area = CHUNK_SIZE * CHUNK_SIZE;
            int offset = x + CHUNK_SIZE * z + area * y;
            chunk_rebuild(chunk, offset);
            break;
        }

        temp_point[0]++;
        temp_point[1]++;
        temp_point[2]++;
    }
}

