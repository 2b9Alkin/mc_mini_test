//
// Created by cprkan on 7/16/23.
//

#ifndef KOPE24_PLAYER_H
#define KOPE24_PLAYER_H

#include "../camera.h"
#include "../../../glfw/include/glfw3.h"
#include <math.h>

typedef struct {
    camera_t* camera;
    float_t player_speed;
} player_t;

void mouse_control(camera_t* camera, GLFWwindow* window);
void keyboard_control(player_t* player, double delta_time, GLFWwindow* window);

#endif //KOPE24_PLAYER_H
