//
// Created by cprkan on 7/17/23.
//

#ifndef MINI_CRAFT_VOXEL_HANDLER_H
#define MINI_CRAFT_VOXEL_HANDLER_H

#include "../camera.h"
#include "../../../include/cglm/cglm/include/cglm/cglm.h"
#include "../../../glfw/include/glfw3.h"
#include "../../renderer/chunk.h"

#define MAX_RAY_DIST 6

void ray_cast(camera_t camera, chunk_t* chunk, double mouse_x, double mouse_y, int screen_width, int screen_height);

#endif //MINI_CRAFT_VOXEL_HANDLER_H
