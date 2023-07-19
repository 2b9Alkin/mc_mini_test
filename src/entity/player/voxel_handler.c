//
// Created by cprkan on 7/17/23.
//

#include "voxel_handler.h"

// Function to find the nearest block to the player.
Vector3Int ray_cast(camera_t camera, chunk_t* chunk) {
	const float max_distance = MAX_RAY_DIST * BLOCK_SIZE;
	const float step_size = STEP_SIZE_RAY_CAST * BLOCK_SIZE;

	Vector3 ray_position = camera.position;
	Vector3 step_direction = Vector3Scale(camera.direction, step_size);

	for (float distanceTraveled = 0.0f; distanceTraveled < max_distance; distanceTraveled += step_size) {
        int voxelX = (int)floorf(ray_position.x / BLOCK_SIZE);
        int voxelY = (int)floorf(ray_position.y / BLOCK_SIZE);
        int voxelZ = (int)floorf(ray_position.z / BLOCK_SIZE);

        if (chunk->map_data[voxelX][voxelY][voxelZ] != EMPTY_BLOCK) {
			return (Vector3Int) {voxelX, voxelY, voxelZ};
        }

		ray_position = Vector3Add(ray_position, step_direction);
    }

	return Vector3IntZero();
}