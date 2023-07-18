//
// Created by cprkan on 7/17/23.
//

#include <memory.h>
#include "voxel_handler.h"

// Function to find the nearest block to the player.
void ray_cast(camera_t camera, chunk_t* chunk) {
    ivec3 player_direction = {(int)roundf(camera.direction[0]),
                              (int)roundf(camera.direction[1]),
                              (int)roundf(camera.direction[2])};

    vec3 temp_point_loc = {camera.positions[0], camera.positions[1], camera.positions[2]};
    vec3 range = {player_direction[0] * MAX_RAY_DIST, player_direction[1] * MAX_RAY_DIST, player_direction[2] * MAX_RAY_DIST};

    while (temp_point_loc[0] <= temp_point_loc[0] + range[0] &&
            temp_point_loc[1] <= temp_point_loc[1] + range[1]) {
        int voxel_x = (int)temp_point_loc[0];
        int voxel_y = (int)temp_point_loc[1];
        int voxel_z = (int)temp_point_loc[2];


        int nearest_x = (int)(voxel_x / BLOCK_SIZE);
        int nearest_y = (int)(voxel_y / BLOCK_SIZE);
        int nearest_z = (int)(voxel_z / BLOCK_SIZE);

        printf("%d, %d, %d\n", nearest_x, nearest_y, nearest_z);

        if (chunk->map_data[voxel_x][voxel_y][voxel_z]) {

            chunk_rebuild(chunk, nearest_x, nearest_y, nearest_z);

            break;
        }

        temp_point_loc[0] += STEP_SIZE_RAY_CAST;
        temp_point_loc[1] += STEP_SIZE_RAY_CAST;
        temp_point_loc[2] += STEP_SIZE_RAY_CAST;
    }


}
