//
// Created by cprkan on 7/16/23.
//

#ifndef KOPE24_CAMERA_H
#define KOPE24_CAMERA_H

#define RAYMATH_STATIC_INLINE
#include "raymath/raymath.h"

#include "../renderer/shader.h"

#define FOV 70.0f
#define NEAR 0.1f
#define FAR 4096.0f
#define PITCH_MAX (89 * DEG2RAD)
#define MOUSE_SENSITIVITY 0.0185f

typedef struct {
    Matrix projection;
    Matrix rotation;
    Matrix view;
    Vector3 position;
    Vector3 up;
    Vector3 right;
    Vector3 forward;
    Vector3 direction;
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
