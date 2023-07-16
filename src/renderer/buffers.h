//
// Created by cprkan on 7/16/23.
//

#ifndef KOPE24_BUFFERS_H
#define KOPE24_BUFFERS_H

#include "GL/glew.h"

#define POS_SIZE 3
#define VOXEL_ID_SIZE 1
#define FACE_ID_SIZE 1
#define VERTEX_SIZE (POS_SIZE + VOXEL_ID_SIZE + FACE_ID_SIZE)

typedef struct {
    GLuint vbo;
    GLuint ebo;
    GLuint vao;
} buffers_t;

void create_vao(GLuint* vao);
void bind_vao(GLuint vao);
void add_attribute(int layout, int size, int offset);
void create_vbo(GLuint* vbo);
void bind_vbo(GLuint vbo);
void send_data_vbo(const GLfloat* vertices, size_t size);
void create_ebo(GLuint* ebo);
void bind_ebo(GLuint ebo);
void send_data_ebo(const GLuint* indices, size_t size);
void create_buffers(const GLfloat *vertices, const GLuint *indices, buffers_t *buffer);

#endif //KOPE24_BUFFERS_H
