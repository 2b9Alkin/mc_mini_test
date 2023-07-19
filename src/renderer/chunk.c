//
// Created by cprkan on 7/16/23.
//

#include <stdbool.h>
#include "chunk.h"

void process_data(chunk_t* chunk, GLfloat vi[12], int current_face) {
    GLuint indices[] = {
        INDICES_IN((chunk->mesh.current_index * 6 * 4) + (current_face * 4))
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

                // RIGHT FACE
                if (y + 1 >= CHUNK_SIZE) {
                    GLfloat vertices[FACE_SIZE_VALUES] = {
                        RIGHT_FACE_VERTICES(x, y, z)
                    };
                    process_data(chunk, vertices, current_face);
                    current_face++;
                }

                // LEFT FACE
                if (y - 1 < 0) {
                    GLfloat vertices[FACE_SIZE_VALUES] = {
                        LEFT_FACE_VERTICES(x, y, z)
                    };
                    process_data(chunk, vertices, current_face);
                    current_face++;
                }

                if (x + 1 >= CHUNK_SIZE) {
                    GLfloat verticesTemp[FACE_SIZE_VALUES] = {
                            (x + 1) * BLOCK_SIZE,     (y + 1) * BLOCK_SIZE, z * BLOCK_SIZE,
                            (x + 1) * BLOCK_SIZE,     y * BLOCK_SIZE,     z * BLOCK_SIZE,
                            (x + 1) * BLOCK_SIZE,     y * BLOCK_SIZE,     (z + 1) * BLOCK_SIZE,
                            (x + 1) * BLOCK_SIZE,     (y + 1) * BLOCK_SIZE, (z + 1) * BLOCK_SIZE,
                    };
                    process_data(chunk, verticesTemp, current_face);
                    current_face++;
                }

                if (x - 1 < 0) {
                    GLfloat verticesTemp[FACE_SIZE_VALUES] = {
                            (x + 0) * BLOCK_SIZE,     (y + 1) * BLOCK_SIZE, z * BLOCK_SIZE,
                            (x + 0) * BLOCK_SIZE,     y * BLOCK_SIZE,     z * BLOCK_SIZE,
                            (x + 0) * BLOCK_SIZE,     y * BLOCK_SIZE,     (z + 1) * BLOCK_SIZE,
                            (x + 0) * BLOCK_SIZE,     (y + 1) * BLOCK_SIZE, (z + 1) * BLOCK_SIZE,
                    };
                    process_data(chunk, verticesTemp, current_face);
                    current_face++;
                }

                if (z + 1 >= CHUNK_SIZE) {
                    GLfloat verticesTemp[FACE_SIZE_VALUES] = {
                            (x + 0) * BLOCK_SIZE,     (y + 1) * BLOCK_SIZE, (z + 1) * BLOCK_SIZE,
                            (x + 0) * BLOCK_SIZE,     y * BLOCK_SIZE,     (z + 1) * BLOCK_SIZE,
                            (x + 1) * BLOCK_SIZE,     y * BLOCK_SIZE,     (z + 1) * BLOCK_SIZE,
                            (x + 1) * BLOCK_SIZE,     (y + 1) * BLOCK_SIZE, (z + 1) * BLOCK_SIZE,
                    };
                    process_data(chunk, verticesTemp, current_face);
                    current_face++;
                }


                if (z - 1 < 0) {
                    GLfloat verticesTemp[FACE_SIZE_VALUES] = {
                            (x + 0) * BLOCK_SIZE,     (y + 1) * BLOCK_SIZE, (z + 0) * BLOCK_SIZE,
                            (x + 0) * BLOCK_SIZE,     y * BLOCK_SIZE,     (z + 0) * BLOCK_SIZE,
                            (x + 1) * BLOCK_SIZE,     y * BLOCK_SIZE,     (z + 0) * BLOCK_SIZE,
                            (x + 1) * BLOCK_SIZE,     (y + 1) * BLOCK_SIZE, (z + 0) * BLOCK_SIZE,
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

    GLfloat* vertices = calloc(BLOCK_SIZE_VALUES, sizeof(GLfloat));
    GLuint* indices = calloc(6 * 6, sizeof(GLuint));
    int current_index = 0;

    int area = CHUNK_SIZE * CHUNK_SIZE;
    int index = x + CHUNK_SIZE * y + area * z;

    if (chunk->map_data[x][y + 1][z] != STONE_BLOCK) {
        GLfloat temp_vertices[FACE_SIZE_VALUES] = {
                RIGHT_FACE_VERTICES(x, y, z)
        };

        GLuint temp_indices[6] = {
                INDICES_IN((current_index * 6) + (index * 6 * 6))
        };

        for (int i = 0; i < 6; i++) {
            indices[i] = temp_indices[i];
        }

        for (int v = 0; v < FACE_SIZE_VALUES; v++) {
            vertices[v] = temp_vertices[v];
        }

        current_index++;
    }

    for (int v = 0; v < BLOCK_SIZE_VALUES; v++) {
        chunk->mesh.vertices[(index * BLOCK_SIZE_VALUES) + v] = vertices[v];
    }

//    printf("%d, %d, %d, %d\n", x, y, z, index);

    for (int i = 0; i < 6 * 6; i++) {
        chunk->mesh.indices[(index * 6 * 6) + i] = indices[i];
    }

    bind_vbo(chunk->mesh.buffers.vbo);
    send_data_vbo(chunk->mesh.vertices, sizeof(GLfloat) * BLOCK_SIZE_VALUES * chunk->mesh.current_index);

    bind_ebo(chunk->mesh.buffers.ebo);
    send_data_ebo(chunk->mesh.indices, sizeof(GLuint) * 6 * 6 * chunk->mesh.current_index);
    
    free(vertices);
    free(indices);
}
