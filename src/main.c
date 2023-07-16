//
// Created by cprkan on 16/6/2023.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../glew/include/GL/glew.h"
#include "../glfw/include/glfw3.h"
#include "entity/player/player.h"
#include "renderer/chunk.h"

// goal -- create a minecraft clone within 48h and less than 10kb of space (keep it simple)
// started this jul 16 1am
// @cprkan (me) made this, hope you like it...
// ohh and don't mess too much with the files, or you might break something ;)

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 480
#define FPS 60

chunk_t test_chunk1;

uint_fast64_t get_current_time_nano_seconds() {
    struct timespec currentTime;
    if (clock_gettime(CLOCK_REALTIME, &currentTime) == -1) {
        exit(EXIT_FAILURE);
    }

    uint_fast64_t nanoseconds = currentTime.tv_sec * 1000000000ULL + currentTime.tv_nsec;
    return nanoseconds;
}

void screen_render(GLFWwindow* window) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(test_chunk1.mesh.shader.program_id);

    glDrawElements(GL_TRIANGLES, test_chunk1.mesh.current_index * 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwSwapInterval(0);
}

int main() {
    if (!glfwInit()) {
        glfwTerminate();
        printf("Failed to init glfw!");
        return -1;
    }
    // window config
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mini Craft", NULL, NULL);

    // create context
    glfwMakeContextCurrent(window);
    glewExperimental = true;
    glewInit();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // DEBUG (TEST):
    init_chunk(&test_chunk1);

    // player config
    player_t* player = malloc(sizeof(player_t));
    player->camera = malloc(sizeof(camera_t));
    player->player_speed = 2.1f;
    camera_init(player->camera, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    set_up_projection(player->camera, WINDOW_WIDTH, WINDOW_HEIGHT);

    // uploads the projection to the shader
    glUniformMatrix4fv(glGetUniformLocation(test_chunk1.mesh.shader.program_id, "uProjection"), 1, GL_FALSE,(const GLfloat*) player->camera->projection);


    // runs the game loop
    //  timer variables
    double draw_interval = 1000000000.0 / FPS;
    double delta = 0;
    uint_fast64_t last_time = get_current_time_nano_seconds();
    uint_fast64_t current_time;
    long timer = 0;
    int draw_count = 0;

    while (!glfwWindowShouldClose(window)) {
        current_time = get_current_time_nano_seconds();

        delta += (double)(current_time - last_time) / draw_interval;
        timer += (long)(current_time - last_time);

        last_time = current_time;

        if (delta >= 1) {
            glfwPollEvents();

            // update player
            keyboard_control(player, delta, window);
            mouse_control(player->camera, window);
            update_view_matrix(player->camera);
            update_vectors(player->camera);
            glUniformMatrix4fv(glGetUniformLocation(test_chunk1.mesh.shader.program_id, "uView"), 1, GL_FALSE,(const GLfloat*) player->camera->view);

            screen_render(window);
            // exit
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwWindowShouldClose(window);
                glfwTerminate();
                glfwDestroyWindow(window);
                break;
            }
            delta--;
            draw_count++;
        }

        // print the fps every second
        if (timer >= 1000000000ULL) {
            printf("FPS: %i\n", draw_count);
            draw_count = 0;
            timer = 0;
        }
    }

    return 0;
}
