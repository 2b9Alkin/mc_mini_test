//
// Created by cprkan on 7/16/23.
//

#include <stdio.h>
#include "buffers.h"
#include "chunk.h"

void create_vao(GLuint* vao) {
    glGenVertexArrays(1, vao);
}

void bind_vao(GLuint vao) {
    glBindVertexArray(vao);
}

void add_attribute(int layout, int size, int offset) {
    // add vertex attrib pointers (va)
    size_t vertex_size_int_bytes = VERTEX_SIZE_VALUES * sizeof(float);

    glEnableVertexAttribArray(layout);
    glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, vertex_size_int_bytes, (const void*)(sizeof(float) * offset));
}

void create_vbo(GLuint* vbo) {
    glGenBuffers(1, vbo);
}

void bind_vbo(GLuint vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void send_data_vbo(const GLfloat* vertices, size_t size) {
    // sends the vertices data to the GPU
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

void create_ebo(GLuint* ebo) {
    glGenBuffers(1, ebo);
}

void bind_ebo(GLuint ebo) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void send_data_ebo(const GLuint* indices, size_t size) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_DYNAMIC_DRAW);
}

void create_buffers(const GLfloat *vertices, const GLuint *indices, buffers_t *buffer) {
    create_vao(&buffer->vao);
    bind_vao(buffer->vao);

    create_vbo(&buffer->vbo);
    bind_vbo(buffer->vbo);
    send_data_vbo(vertices, sizeof(float) * VERTEX_SIZE_VALUES * 4 * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 4);

    create_ebo(&buffer->ebo);
    bind_ebo(buffer->ebo);
    send_data_ebo(indices, 6 * (sizeof indices  * sizeof(GLuint)) * 1036);

    bind_vbo(buffer->vbo);
    bind_ebo(buffer->ebo);
    bind_vao(buffer->vao);

    add_attribute(0, POS_SIZE, 0);
    add_attribute(1, VOXEL_ID_SIZE, POS_SIZE);
    add_attribute(2, FACE_ID_SIZE, POS_SIZE + VOXEL_ID_SIZE);
}
