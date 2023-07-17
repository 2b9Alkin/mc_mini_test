//
// Created by cprkan on 7/16/23.
//

#include <stdbool.h>
#include "chunk.h"

static void process_data(chunk_t* chunk, const float vertices[VERTEX_SIZE * 4]) {
    GLuint indices[] = {
            0 + (chunk->mesh.current_index * 4),
            1 + (chunk->mesh.current_index * 4),
            2 + (chunk->mesh.current_index * 4),
            2 + (chunk->mesh.current_index * 4),
            3 + (chunk->mesh.current_index * 4),
            0 + (chunk->mesh.current_index * 4)
    };

    for (int v = 0; v < VERTEX_SIZE * 4; v++) {
        chunk->mesh.vertices[v + (chunk->mesh.current_index * VERTEX_SIZE * 4)] = vertices[v];
    }
    for (int i = 0; i < 6; i++) {
        chunk->mesh.indices[i + (chunk->mesh.current_index * 6)] = indices[i];
    }
    chunk->mesh.current_index++;
}

bool is_void(int x, int y, int z, uint8_t voxel_data[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]) {
    if (0 <= x < CHUNK_SIZE && 0 <= y < CHUNK_SIZE && 0 <= z < CHUNK_SIZE) {
        if (voxel_data[x][y][z]) {
            return false;
        }
    }
    return true;
}

void chunk_init(chunk_t* chunk) {
    chunk->mesh.current_index = 0;

    // put the code here to save performance
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                chunk->map_data[x][y][z] = x + y + z;

                float voxel_id = chunk->map_data[x][y][z];

                if (chunk->map_data[x][y + 1][z] == EMPTY_BLOCK && y + 1 == CHUNK_SIZE) {
                    GLfloat vertices[VERTEX_SIZE * 4] = {
                        x * BLOCK_SIZE,         (y + 1) * BLOCK_SIZE,       z * BLOCK_SIZE,               voxel_id,     0,
                        (x + 1) * BLOCK_SIZE,   (y + 1) * BLOCK_SIZE,       z * BLOCK_SIZE,               voxel_id,     0,
                        (x + 1) * BLOCK_SIZE,   (y + 1) * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,         voxel_id,     0,
                        x * BLOCK_SIZE,         (y + 1) * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,         voxel_id,     0,
                    };
                    process_data(chunk, vertices);
                }
                if (chunk->map_data[x][y - 1][z] == EMPTY_BLOCK || y == 0) {
                    GLfloat vertices[VERTEX_SIZE * 4] = {
                            x * BLOCK_SIZE,         y * BLOCK_SIZE,       z * BLOCK_SIZE,               voxel_id,     0,
                            (x + 1) * BLOCK_SIZE,   y * BLOCK_SIZE,       z * BLOCK_SIZE,               voxel_id,     0,
                            (x + 1) * BLOCK_SIZE,   y * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,         voxel_id,     0,
                            x * BLOCK_SIZE,         y * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,         voxel_id,     0,
                    };
                    process_data(chunk, vertices);
                }

                if (x + 1 == CHUNK_SIZE) {
                    GLfloat vertices[VERTEX_SIZE * 4] = {
                            (x + 1) * BLOCK_SIZE,         y * BLOCK_SIZE,       z * BLOCK_SIZE,               voxel_id,     0,
                            (x + 1) * BLOCK_SIZE,   (y + 1) * BLOCK_SIZE,       z * BLOCK_SIZE,               voxel_id,     0,
                            (x + 1) * BLOCK_SIZE,   (y + 1) * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,         voxel_id,     0,
                            (x + 1) * BLOCK_SIZE,         y * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,         voxel_id,     0,
                    };

                    process_data(chunk, vertices);
                }


                if (chunk->map_data[x - 1][y][z] == EMPTY_BLOCK || x == 0) {
                    GLfloat vertices[VERTEX_SIZE * 4] = {
                            (x + 0) * BLOCK_SIZE,         y * BLOCK_SIZE,       z * BLOCK_SIZE,               voxel_id,     0,
                            (x + 0) * BLOCK_SIZE,   (y + 1) * BLOCK_SIZE,       z * BLOCK_SIZE,               voxel_id,     0,
                            (x + 0) * BLOCK_SIZE,   (y + 1) * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,         voxel_id,     0,
                            (x + 0) * BLOCK_SIZE,         y * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,         voxel_id,     0,
                    };

                    process_data(chunk, vertices);
                }


                if (chunk->map_data[x][y][z - 1] == EMPTY_BLOCK || z == 0) {
                    GLfloat vertices[VERTEX_SIZE * 4] = {
                            (x + 0) * BLOCK_SIZE,         y * BLOCK_SIZE,       (z + 0) * BLOCK_SIZE,               voxel_id,     0,
                            (x + 0) * BLOCK_SIZE,   (y + 1) * BLOCK_SIZE,       (z + 0) * BLOCK_SIZE,               voxel_id,     0,
                            (x + 1) * BLOCK_SIZE,   (y + 1) * BLOCK_SIZE,       (z + 0) * BLOCK_SIZE,         voxel_id,     0,
                            (x + 1) * BLOCK_SIZE,         y * BLOCK_SIZE,       (z + 0) * BLOCK_SIZE,         voxel_id,     0,
                    };

                    process_data(chunk, vertices);
                }

                if (chunk->map_data[x][y][z + 1] == EMPTY_BLOCK && z + 1 == CHUNK_SIZE) {
                    GLfloat vertices[VERTEX_SIZE * 4] = {
                            (x + 0) * BLOCK_SIZE,         y * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,               voxel_id,     0,
                            (x + 0) * BLOCK_SIZE,   (y + 1) * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,               voxel_id,     0,
                            (x + 1) * BLOCK_SIZE,   (y + 1) * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,         voxel_id,     0,
                            (x + 1) * BLOCK_SIZE,         y * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,         voxel_id,     0,
                    };

                    process_data(chunk, vertices);
                }
            }
        }
    }
    create_shader(&chunk->mesh.shader, VERT, FRAG);
    glUseProgram(chunk->mesh.shader.program_id);


    // create the chunk->mesh.bufferss
    create_vao(&chunk->mesh.buffers.vao);
    bind_vao(chunk->mesh.buffers.vao);

    create_vbo(&chunk->mesh.buffers.vbo);
    bind_vbo(chunk->mesh.buffers.vbo);
    send_data_vbo(chunk->mesh.vertices, sizeof(float) * VERTEX_SIZE * 4 * chunk->mesh.current_index);

    create_ebo(&chunk->mesh.buffers.ebo);
    bind_ebo(chunk->mesh.buffers.ebo);
    send_data_ebo(chunk->mesh.indices, sizeof(GLuint) * 6 * chunk->mesh.current_index);

    bind_vbo(chunk->mesh.buffers.vbo);
    bind_ebo(chunk->mesh.buffers.ebo);
    bind_vao(chunk->mesh.buffers.vao);

    add_attribute(0, POS_SIZE, 0);
    add_attribute(1, VOXEL_ID_SIZE, POS_SIZE);
    add_attribute(2, FACE_ID_SIZE, POS_SIZE + VOXEL_ID_SIZE);
}


void chunk_rebuild(chunk_t* chunk, int offset) {
    // Calculate the size of the data to update
    size_t data_size = VERTEX_SIZE * 4 * 6 * sizeof(GLfloat);

    // Bind the buffer
    bind_vbo(chunk->mesh.buffers.vbo);

    // Create an array of zeros with the size of the data to update
    GLfloat* zeros = calloc(data_size, sizeof(GLfloat));

    // Update the buffer data with the array of zeros
    glBufferSubData(GL_ARRAY_BUFFER, offset, data_size, zeros);

    // Free the allocated memory for zeros
    free(zeros);
}
