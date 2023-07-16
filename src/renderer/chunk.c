//
// Created by cprkan on 7/16/23.
//

#include "chunk.h"

void init_chunk(chunk_t* chunk) {
    chunk->mesh.current_index = 0;

    // put the code here to save performance
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                chunk->map_data[x][y][z] = STONE_BLOCK;

                // checks if the block is empty (prevent bugs)
                if (chunk->map_data[x][y][z] == EMPTY_BLOCK) {
                    continue;
                }

                if (chunk->map_data[x][y + 1][z] == EMPTY_BLOCK &&
                    y + 1 >= CHUNK_SIZE) {
//                    printf("%d, %d, %d\n", x, y, z);

                    float voxel_id = x + CHUNK_SIZE * z + (CHUNK_SIZE * CHUNK_SIZE) * y;

                    GLfloat vertices[VERTEX_SIZE * 4] = {
                        x, y + BLOCK_SIZE, z,                   voxel_id, 0,
                        x + BLOCK_SIZE, y + BLOCK_SIZE, z,              voxel_id, 0,
                        x + BLOCK_SIZE, y + BLOCK_SIZE, z + BLOCK_SIZE,         voxel_id, 0,
                        x, y + BLOCK_SIZE, z + BLOCK_SIZE,              voxel_id, 0,
                    };

                    GLuint indices[] = {
                            0 + (chunk->mesh.current_index * 6), 1 + (chunk->mesh.current_index * 6), 2 + (chunk->mesh.current_index * 6),
                            0 + (chunk->mesh.current_index * 6), 2 + (chunk->mesh.current_index * 6), 3 + (chunk->mesh.current_index * 6)
                    };

                    for (int v = 0; v < VERTEX_SIZE * 4; v++) {
                        chunk->mesh.vertices[v + (chunk->mesh.current_index * VERTEX_SIZE * 4)] = vertices[v];
                    }

                    for (int i = 0; i < 6; i++) {
                        chunk->mesh.indices[i + (chunk->mesh.current_index * 6)] = indices[i];
                    }

                    chunk->mesh.current_index++;
                }
            }
        }
    }
    create_shader(&chunk->mesh.shader, VERT, FRAG);
    glUseProgram(chunk->mesh.shader.program_id);

    create_buffers(chunk->mesh.vertices, chunk->mesh.indices, &chunk->mesh.buffers);

}

