//
// Created by cprkan on 7/16/23.
//

#include <memory.h>
#include "camera.h"

void update_camera_direction(camera_t* camera) {
    // Calculate the direction vector components based on yaw and pitch.
    float cos_pitch = cos(camera->pitch);
    camera->direction[0] = cos(camera->yaw) * cos_pitch;
    camera->direction[1] = sin(camera->pitch);
    camera->direction[2] = sin(camera->yaw) * cos_pitch;

    // Normalize the direction vector to make it a unit vector.
    glm_normalize(camera->direction);
}

void set_up_projection(camera_t* camera, int width, int height) {
    float aspect_ratio = (float) ((width) / height) ; // Adjust this based on your screen size

    glm_perspective(glm_rad(FOV), aspect_ratio, NEAR, FAR, camera->projection);
}

void camera_init(camera_t* camera, float yaw, float pitch, int width, int height) {
    camera->yaw = glm_rad(yaw);
    camera->pitch = glm_rad(pitch);

    vec3 up = {0, 1, 0};
    vec3 right = {1, 0, 0};
    vec3 forward = {0, 0, -1};

    memcpy(camera->up, up, sizeof up);
    memcpy(camera->right, right, sizeof right);
    memcpy(camera->forward, forward, sizeof forward);

    float t = 4;
    // sets the projections for the window of view
    glm_ortho(-width / t, width / t, -height / t, height / t, -1000, 1000, camera->projection);

}

void update_view_matrix(camera_t* camera) {
    vec3 center;
    glm_vec3_add(camera->positions, camera->forward, center);
    glm_lookat(camera->positions, center, camera->up, camera->view);
}

void update_vectors(camera_t* camera) {
    camera->forward[0] = cos(camera->yaw) * cos(camera->pitch);
    camera->forward[1] = sin(camera->pitch);
    camera->forward[2] = sin(camera->yaw) * cos(camera->pitch);

    glm_normalize(camera->forward);
    vec3 t = {0, 1, 0};
    glm_cross(camera->forward, t, camera->right);
    glm_normalize(camera->right);

    glm_cross(camera->right, camera->forward, camera->up);
    glm_normalize(camera->up);
}

void rotate_pitch(camera_t* camera, float delta_y) {
    camera->pitch += delta_y;
    glm_clamp(camera->pitch, -PITCH_MAX, PITCH_MAX);
}

void rotate_yaw(camera_t* camera, float delta_x) {
    camera->yaw += delta_x;
    glm_clamp(camera->yaw, -PITCH_MAX, PITCH_MAX);
}

void move_left(camera_t* camera, float velocity) {
    vec3 movement;
    glm_vec3_mul(camera->right, (vec3){velocity, velocity, velocity}, movement);
    glm_vec3_sub(camera->positions, movement, camera->positions);
}

void move_right(camera_t* camera, float velocity) {
    vec3 movement;
    glm_vec3_mul(camera->right, (vec3){velocity, velocity, velocity}, movement);
    glm_vec3_add(camera->positions, movement, camera->positions);
}

void move_up(camera_t* camera, float velocity) {
    vec3 movement;
    glm_vec3_mul(camera->up, (vec3){velocity, velocity, velocity}, movement);
    glm_vec3_add(camera->positions, movement, camera->positions);
}

void move_down(camera_t* camera, float velocity) {
    vec3 movement;
    glm_vec3_mul(camera->up, (vec3){velocity, velocity, velocity}, movement);
    glm_vec3_sub(camera->positions, movement, camera->positions);
}

void move_forward(camera_t* camera, float velocity) {
    vec3 movement;
    glm_vec3_scale(camera->forward, velocity, movement);
    glm_vec3_add(camera->positions, movement, camera->positions);
}

void move_back(camera_t* camera, float velocity) {
    vec3 movement;
    glm_vec3_scale(camera->forward, velocity, movement);
    glm_vec3_sub(camera->positions, movement, camera->positions);
}
