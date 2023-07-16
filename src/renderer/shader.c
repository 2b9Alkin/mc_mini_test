//
// Created by cprkan on 7/16/23.
//

#include "shader.h"

static int compile_shader(char* source, int type) {
    int id = glCreateShader(type);

    // creates the shader from the source (shader file)
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    return id;
}

void create_shader(shader_t *shader, char *v, char *f) {
    // create the program for the shader to use
    shader->program_id = glCreateProgram();

    // creates the shaders from the method
    shader->vert = compile_shader(read_file(v), GL_VERTEX_SHADER);
    shader->frag = compile_shader(read_file(f), GL_FRAGMENT_SHADER);


    // attach the shader to the program (group them up)
    glAttachShader(shader->program_id, shader->vert);
    glAttachShader(shader->program_id, shader->frag);

    glLinkProgram(shader->program_id);
    glValidateProgram(shader->program_id);

    // delete shaders to save memory
    glDeleteShader(shader->vert);
    glDeleteShader(shader->frag);
}

void destroy_shader(shader_t shader) {
    glDeleteShader(shader.vert);
    glDeleteShader(shader.frag);
}