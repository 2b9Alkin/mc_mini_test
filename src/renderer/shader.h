//
// Created by cprkan on 7/16/23.
//

#ifndef KOPE24_SHADER_H
#define KOPE24_SHADER_H

#include "../glew/include/GL/glew.h"
#include "../util/utils.h"

typedef struct {
    GLuint program_id;
    GLuint vert;
    GLuint frag;
} shader_t;


#define FRAG "../shaders/default_frag.glsl"
#define VERT "../shaders/default_vert.glsl"

static int compile_shader(char* source, int type);
void create_shader(shader_t *shader, char *v, char *f);
void destroy_shader(shader_t shader);

#endif //KOPE24_SHADER_H
