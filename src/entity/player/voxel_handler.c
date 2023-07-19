//
// Created by cprkan on 7/17/23.
//

#include <memory.h>
#include "voxel_handler.h"

// Function to find the nearest block to the player.
void ray_cast(camera_t camera, chunk_t* chunk) {
    vec3 playerPosition = {camera.positions[0], camera.positions[1], camera.positions[2]};
    vec3 playerDirection;

    glm_vec3_copy(camera.direction, playerDirection);

    vec3 ray_position;
    glm_vec3_copy(playerPosition, ray_position);

    float maxRayDistance = MAX_RAY_DIST * BLOCK_SIZE;

    for (float distanceTraveled = 0.0f; distanceTraveled < maxRayDistance; distanceTraveled += STEP_SIZE_RAY_CAST) {
        vec3 rayIncrement;
        glm_vec3_scale(playerDirection, STEP_SIZE_RAY_CAST, rayIncrement);
        glm_vec3_add(ray_position, rayIncrement, ray_position);

        int voxelX = (int)floor(ray_position[0] / BLOCK_SIZE);
        int voxelY = (int)floor(ray_position[1] / BLOCK_SIZE);
        int voxelZ = (int)floor(ray_position[2] / BLOCK_SIZE);

        if (chunk->map_data[voxelX][voxelY][voxelZ] != EMPTY_BLOCK) {
            // Break the block at the current position.
            chunk->map_data[voxelX][voxelY][voxelZ] = EMPTY_BLOCK;
            chunk_rebuild(chunk, voxelX, voxelY, voxelZ);

            break;
        }
    }
}