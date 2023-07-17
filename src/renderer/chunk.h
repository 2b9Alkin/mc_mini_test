//
// Created by cprkan on 7/16/23.
//

#ifndef MINI_CRAFT_CHUNK_H
#define MINI_CRAFT_CHUNK_H

#include "shader.h"
#include "buffers.h"

#define CHUNK_SIZE 32
#define BLOCK_SIZE 32

enum tiles {
    EMPTY_BLOCK = 0,
    GRASS_BLOCK = 1,
    STONE_BLOCK = 2
};


typedef struct {
    shader_t shader;
    buffers_t buffers;
    int current_index;
    GLfloat vertices[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * VERTEX_SIZE * 12];
    GLuint indices[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 6 * 12];
} chunk_mesh_t;

typedef struct {
    uint8_t map_data[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    chunk_mesh_t mesh;
} chunk_t;

void chunk_init(chunk_t* chunk);
void chunk_rebuild(chunk_t* chunk, int offset);

#endif //MINI_CRAFT_CHUNK_H
