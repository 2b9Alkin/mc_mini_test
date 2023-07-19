//
// Created by cprkan on 7/17/23.
//

#include <memory.h>
#include "voxel_handler.h"

// Function to find the nearest block to the player.
void ray_cast(camera_t camera, chunk_t* chunk) {
    vec3 player_position;
    glm_vec3_copy(camera.positions, player_position);
    vec3 player_direction;

    glm_vec3_copy(camera.direction, player_direction);

    vec3 ray_position;
    glm_vec3_copy(player_position, ray_position);

    float max_ray_distance = MAX_RAY_DIST * BLOCK_SIZE;

//    printf("%f, %f, %f\n", player_position[0], player_position[1], player_position[2]);

    for (float distance_traveled = 0.0f; distance_traveled < max_ray_distance; distance_traveled += STEP_SIZE_RAY_CAST) {
        vec3 ray_inc;
        glm_vec3_scale(player_direction, STEP_SIZE_RAY_CAST, ray_inc);
        glm_vec3_add(ray_position, ray_inc, ray_position);

        int voxelX = (int)floor(ray_position[0] / BLOCK_SIZE);
        int voxelY = (int)floor(ray_position[1] / BLOCK_SIZE);
        int voxelZ = (int)floor(ray_position[2] / BLOCK_SIZE);

//        printf("%d, %d, %d\n", voxelX, voxelY, voxelZ);
        if (chunk->map_data[voxelX][voxelY][voxelZ] != EMPTY_BLOCK) {
            // Break the block at the current position.
            chunk->map_data[voxelX][voxelY][voxelZ] = EMPTY_BLOCK;
            chunk_rebuild(chunk, voxelX, voxelY, voxelZ);

            break;
        }
    }
}