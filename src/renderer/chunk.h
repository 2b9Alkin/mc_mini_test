//
// Created by cprkan on 7/16/23.
//

#ifndef MINI_CRAFT_CHUNK_H
#define MINI_CRAFT_CHUNK_H

#include "shader.h"
#include "buffers.h"

#define CHUNK_SIZE 12
#define BLOCK_SIZE 32
#define CHUNK_AREA CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE
#define FACE_SIZE_VALUES VERTEX_SIZE_VALUES * 4
#define BLOCK_SIZE_VALUES FACE_SIZE_VALUES * 6

// FACES
#define RIGHT_FACE_VERTICES(x, y, z) x * BLOCK_SIZE,         (y + 1) * BLOCK_SIZE,       z * BLOCK_SIZE, \
                                     (x + 1) * BLOCK_SIZE,   (y + 1) * BLOCK_SIZE,       z * BLOCK_SIZE, \
                                     (x + 1) * BLOCK_SIZE,   (y + 1) * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE, \
                                     x * BLOCK_SIZE,         (y + 1) * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,
#define LEFT_FACE_VERTICES(x, y, z) x * BLOCK_SIZE,         (y + 0) * BLOCK_SIZE,       z * BLOCK_SIZE, \
                                    (x + 1) * BLOCK_SIZE,   (y + 0) * BLOCK_SIZE,       z * BLOCK_SIZE, \
                                    (x + 1) * BLOCK_SIZE,   (y + 0) * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE, \
                                    x * BLOCK_SIZE,         (y + 0) * BLOCK_SIZE,       (z + 1) * BLOCK_SIZE,

#define TOP_FACE_VERTICES
#define BOTTOM_FACE_VERTICES
#define FRONT_FACE_VERTICES
#define BACK_FACE_VERTICES

#define INDICES_IN(index) 0 + index, 1 + index, 2 + index, \
                          0 + index, 2 + index, 3 + index

enum tiles {
    EMPTY_BLOCK = 0,
    GRASS_BLOCK = 1,
    STONE_BLOCK = 2
};

typedef struct {
    shader_t shader;
    buffers_t buffers;
    int current_index;
    GLfloat vertices[CHUNK_AREA * FACE_SIZE_VALUES * 6];
    GLuint indices[CHUNK_AREA * 6 * 6 * 4];
} chunk_mesh_t;

typedef struct {
    uint8_t map_data[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    chunk_mesh_t mesh;
} chunk_t;

void chunk_init(chunk_t* chunk);
void chunk_rebuild(chunk_t *chunk, int x, int y, int z);
void chunk_render(chunk_t chunk);

#endif //MINI_CRAFT_CHUNK_H
