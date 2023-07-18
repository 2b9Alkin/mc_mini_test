//
// Created by cprkan on 7/16/23.
//

#ifndef MINI_CRAFT_CHUNK_H
#define MINI_CRAFT_CHUNK_H

#include "shader.h"
#include "buffers.h"

#define CHUNK_SIZE 3
#define BLOCK_SIZE 32
#define CHUNK_AREA CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE
#define FACE_SIZE_VALUES VERTEX_SIZE_VALUES * 4
#define BLOCK_SIZE_VALUES FACE_SIZE_VALUES * 6

enum tiles {
    EMPTY_BLOCK = 0,
    GRASS_BLOCK = 1,
    STONE_BLOCK = 2
};

enum faces {
    LEFT_FACE=0,
    RIGHT_FACE=1,
    FRONT_FACE=0,
    BACK_FACE=1,
    TOP_FACE=0,
    BOTTOM_FACE=1
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
