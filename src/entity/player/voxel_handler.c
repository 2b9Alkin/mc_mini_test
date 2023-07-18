//
// Created by cprkan on 7/17/23.
//

#include <memory.h>
#include "voxel_handler.h"

// Function to find the nearest block to the player.
void ray_cast(camera_t camera, chunk_t* chunk) {
    vec3 check_position;
    glm_vec3_copy(camera.positions, check_position); //start at cam pos
    printf("Camera position: (%f, %f, %f)\n", check_position[0], check_position[1], check_position[2]);

    int cam_x = (int)(check_position[0] / BLOCK_SIZE);
    int cam_y = (int)(check_position[1] / BLOCK_SIZE);
    int cam_z = (int)(check_position[2] / BLOCK_SIZE);
    printf("Camera block: (%d, %d, %d)\n", cam_x, cam_y, cam_z);
    printf("voxel at camera position is: %d\n", chunk->map_data[cam_x][cam_y][cam_z]);
}