//
// Created by cprkan on 7/16/23.
//

#ifndef MINI_CRAFT_CHUNK_H
#define MINI_CRAFT_CHUNK_H

#include "shader.h"
#include "buffers.h"

#define CHUNK_SIZE 14
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
    GLfloat vertices[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * VERTEX_SIZE * 8];
    GLuint indices[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 6 * 6];
} chunk_mesh_t;

typedef struct {
   uint8_t map_data[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    chunk_mesh_t mesh;
} chunk_t;

void init_chunk(chunk_t* chunk);

#endif //MINI_CRAFT_CHUNK_H
