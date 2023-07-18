//
// Created by cprkan on 7/16/23.
//

#include <stdbool.h>
#include "chunk.h"

void process_data(chunk_t* chunk, GLfloat vi[12], int current_face) {
    GLuint indices[] = {
            0 + (chunk->mesh.current_index * 6 * 4) + (current_face * 4),
            1 + (chunk->mesh.current_index * 6 * 4) + (current_face * 4),
            2 + (chunk->mesh.current_index * 6 * 4) + (current_face * 4),
            2 + (chunk->mesh.current_index * 6 * 4) + (current_face * 4),
            3 + (chunk->mesh.current_index * 6 * 4) + (current_face * 4),
            0 + (chunk->mesh.current_index * 6 * 4) + (current_face * 4)
    };

    for (int v = 0; v < FACE_SIZE_VALUES; v++) {
        chunk->mesh.vertices[v + (chunk->mesh.current_index * BLOCK_SIZE_VALUES) + (current_face * FACE_SIZE_VALUES)] = vi[v];
    }
    for (int i = 0; i < 6; i++) {
        chunk->mesh.indices[i + (chunk->mesh.current_index * 6 * 6) + (current_face * 6)] = indices[i];
    }
}

void chunk_render(chunk_t chunk) {
    glUseProgram(chunk.mesh.shader.program_id);
    glDrawElements(GL_TRIANGLES, chunk.mesh.current_index * BLOCK_SIZE_VALUES, GL_UNSIGNED_INT, NULL);
}


void chunk_init(chunk_t* chunk) {
    chunk->mesh.current_index = 0;

    // Initialize the chunk data and generate mesh
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                int current_face = 0;
                chunk->map_data[x][y][z] = STONE_BLOCK;

                // LEFT face
                if (y + 1 == CHUNK_SIZE || chunk->map_data[x][y + 1][z] == STONE_BLOCK) {
                    GLfloat vertices[FACE_SIZE_VALUES] = {
                            x * BLOCK_SIZE,         (y + 1) * BLOCK_SIZE,       z * BLOCK_SIZE,
                            (x + 1) * BLOCK_SIZE,   (y + 1) * BLOCK_SIZE,       z * BLOCK_SIZE,
                            (x + 1) * BLOCK_SIZE,   (y + 1) * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,
                            x * BLOCK_SIZE,         (y + 1) * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,
                    };
                    process_data(chunk, vertices, current_face);
                    current_face++;
                }

                if (y - 1 < 0 || chunk->map_data[x][y - 1][z] == STONE_BLOCK) {
                    GLfloat vertices[FACE_SIZE_VALUES] = {
                            x * BLOCK_SIZE,         (y + 0) * BLOCK_SIZE,       z * BLOCK_SIZE,
                            (x + 1) * BLOCK_SIZE,   (y + 0) * BLOCK_SIZE,       z * BLOCK_SIZE,
                            (x + 1) * BLOCK_SIZE,   (y + 0) * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,
                            x * BLOCK_SIZE,         (y + 0) * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,
                    };
                    process_data(chunk, vertices, current_face);
                    current_face++;
                }

                // RIGHT face
                if (x + 1 >  CHUNK_SIZE - 1 || chunk->map_data[x + 1][y][z] == STONE_BLOCK) {
                    GLfloat verticesTemp[FACE_SIZE_VALUES] = {
                            (x + 1) * BLOCK_SIZE,     (y + 1) * BLOCK_SIZE, z * BLOCK_SIZE,
                            (x + 1) * BLOCK_SIZE,     y * BLOCK_SIZE,     z * BLOCK_SIZE,
                            (x + 1) * BLOCK_SIZE,     y * BLOCK_SIZE,     (z + 1) * BLOCK_SIZE,
                            (x + 1) * BLOCK_SIZE,     (y + 1) * BLOCK_SIZE, (z + 1) * BLOCK_SIZE,
                    };
                    process_data(chunk, verticesTemp, current_face);
                    current_face++;
                }

                chunk->mesh.current_index++;
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
    send_data_vbo(chunk->mesh.vertices, sizeof(GLfloat) * BLOCK_SIZE_VALUES * chunk->mesh.current_index);

    create_ebo(&chunk->mesh.buffers.ebo);
    bind_ebo(chunk->mesh.buffers.ebo);
    send_data_ebo(chunk->mesh.indices, sizeof(GLuint) * 6 * 6 * chunk->mesh.current_index);

    bind_vbo(chunk->mesh.buffers.vbo);
    bind_ebo(chunk->mesh.buffers.ebo);
    bind_vao(chunk->mesh.buffers.vao);

    add_attribute(0, POS_SIZE, 0);
}


void chunk_rebuild(chunk_t *chunk, int x, int y, int z) {
    glUseProgram(chunk->mesh.shader.program_id);

    if (chunk->map_data[x + 1][y][z] != EMPTY_BLOCK &&
        x >= 0 && x < CHUNK_SIZE &&
        y >= 0 && y < CHUNK_SIZE &&
        z >= 0 && z < CHUNK_SIZE) {
        int area = CHUNK_SIZE * CHUNK_SIZE;
        int index = z + CHUNK_SIZE * x + area * y;


        GLfloat vertices_temp[FACE_SIZE_VALUES] = {
                x * BLOCK_SIZE,         (y + 1) * BLOCK_SIZE,       z * BLOCK_SIZE,
                (x + 1) * BLOCK_SIZE,   (y + 1) * BLOCK_SIZE,       z * BLOCK_SIZE,
                (x + 1) * BLOCK_SIZE,   (y + 1) * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,
                x * BLOCK_SIZE,         (y + 1) * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,
        };

        GLuint indices_temp[] = {
                0 + (index * 6 * 6), 1 + (index * 6 * 6), 2 + (index * 6 * 6),
                0 + (index * 6 * 6), 2 + (index * 6 * 6), 3 + (index * 6 * 6)
        };

        printf("%i\n", index);

        for (int i = 0; i < 6; i++) {
            chunk->mesh.indices[(index * 6 * 6) + i] = indices_temp[i];
        }

        for (int v = 0; v < FACE_SIZE_VALUES; v++) {
            chunk->mesh.vertices[(index * BLOCK_SIZE_VALUES) + v] = vertices_temp[v];
        }

        bind_vbo(chunk->mesh.buffers.vbo);
        send_data_vbo(chunk->mesh.vertices, sizeof(GLfloat) * BLOCK_SIZE_VALUES * chunk->mesh.current_index);

        bind_ebo(chunk->mesh.buffers.ebo);
        send_data_ebo(chunk->mesh.indices, sizeof(GLuint) * 6 * 6 * chunk->mesh.current_index);
    }
}
