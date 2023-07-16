//
// Created by cprkan on 7/16/23.
//

#include "player.h"

static bool mouse_moved = false;
static double prev_mouse_x = 0.0;
static double prev_mouse_y = 0.0;
static double delta_x = 0.0f;
static double delta_y = 0.0f;

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    if (!mouse_moved) {
        prev_mouse_x = xPos;
        prev_mouse_y = yPos;
        mouse_moved = true;
    }

    double dx = xPos - prev_mouse_x;
    double dy = yPos - prev_mouse_y;

    delta_y = dy;
    delta_x = dx;

    prev_mouse_x = xPos;
    prev_mouse_y = yPos;
}
void mouse_control(camera_t* camera, GLFWwindow* window) {
    glfwSetCursorPosCallback(window, mouse_callback);

    if (mouse_moved) {
        rotate_yaw(camera, delta_x * MOUSE_SENSITIVITY);
    }
    if (mouse_moved) {
        rotate_pitch(camera, delta_y * MOUSE_SENSITIVITY);
    }
    mouse_moved = false;
}

void keyboard_control(player_t* player, double delta_time, GLFWwindow* window) {
    float velocity = player->player_speed * delta_time;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        move_forward(player->camera, velocity);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        move_back(player->camera, velocity);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        move_right(player->camera, velocity);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        move_left(player->camera, velocity);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        move_up(player->camera, velocity);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        move_down(player->camera, velocity);
    }


}
