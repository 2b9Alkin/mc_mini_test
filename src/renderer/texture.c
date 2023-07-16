//
// Created by cprkan on 7/16/23.
//

#include "texture.h"
#include "stbi/include/stbi.h"

GLuint load_texture(char *path, int slot) {
    int width, height, channels;

    stbi_set_flip_vertically_on_load(GL_TRUE);
    unsigned char* bytes = stbi_load(path, &width, &height, &channels, 4);
    unsigned int ID;

    // generate the buffer
    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, ID);

    // modify values/settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_NEARTED
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

//    float flat_color[] = {1.0f, 0.0f, 1.0f, 1.0f};
//    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flat_color);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, slot);

    return ID;
}
