//
// Created by cprkan on 7/16/23.
//

#ifndef KOPE24_CAMERA_H
#define KOPE24_CAMERA_H

#include "cglm/cglm/include/cglm/cglm.h"
#include "../renderer/shader.h"

#define FOV 70.0f
#define NEAR 0.1f
#define FAR 4096.0f
#define PITCH_MAX glm_rad(89)
#define MOUSE_SENSITIVITY 0.0185f

typedef struct {
    mat4 projection;
    mat4 rotation;
    mat4 view;
    vec3 positions;
    vec3 up;
    vec3 right;
    vec3 forward;
    vec3 direction;
    float yaw;
    float pitch;
} camera_t;

void update_camera_direction(camera_t* camera);
void set_up_projection(camera_t* camera, int width, int height);
void camera_init(camera_t* camera, float yaw, float pitch, int width, int height);
void update_view_matrix(camera_t* camera);
void update_vectors(camera_t* camera);
void rotate_pitch(camera_t* camera, float delta_y);
void rotate_yaw(camera_t* camera, float delta_x);
void move_left(camera_t* camera, float velocity);
void move_right(camera_t* camera, float velocity);
void move_up(camera_t* camera, float velocity);
void move_down(camera_t* camera, float velocity);
void move_forward(camera_t* camera, float velocity);
void move_back(camera_t* camera, float velocity);

#endif //KOPE24_CAMERA_H
