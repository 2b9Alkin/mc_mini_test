//
// Created by cprkan on 7/16/23.
//

#include "utils.h"

char* read_file(const char* filepath) {
    FILE* file = fopen(filepath, "rb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filepath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(fileLength + 1);
    if (buffer == NULL) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    fread(buffer, 1, fileLength, file);
    buffer[fileLength] = '\0';

    fclose(file);
    return buffer;
}