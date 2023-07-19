//
// Created by cprkan on 7/16/23.
//

#include "camera.h"

void update_camera_direction(camera_t* camera) {
    // Calculate the direction vector components based on yaw and pitch.
    float cos_pitch = cosf(camera->pitch);
    camera->direction.x = cosf(camera->yaw) * cos_pitch;
    camera->direction.y = sinf(camera->pitch);
    camera->direction.z = sinf(camera->yaw) * cos_pitch;

    // Normalize the direction vector to make it a unit vector.
	camera->direction = Vector3Normalize(camera->direction);
}

void set_up_projection(camera_t* camera, int width, int height) {
    float aspect_ratio = (float) ((width) / height) ; // Adjust this based on your screen size

	camera->projection = MatrixPerspective(FOV * DEG2RAD, aspect_ratio, NEAR, FAR);
}

void camera_init(camera_t* camera, float yaw, float pitch, int width, int height) {
    camera->yaw = yaw * DEG2RAD;
    camera->pitch = pitch * DEG2RAD;

    camera->up = (Vector3){0, 1, 0};
    camera->right = (Vector3){1, 0, 0};
    camera->forward = (Vector3){0, 0, -1};

    float t = 4;
    // sets the projections for the window of view
	camera->projection = MatrixOrtho(-width / t, width / t, -height / t, height / t, -1000, 1000);
}

void update_view_matrix(camera_t* camera) {
    Vector3 center = Vector3Add(camera->position, camera->forward);
	camera->view = MatrixLookAt(camera->position, center, camera->up);
}

void update_vectors(camera_t* camera) {
    camera->forward.x = cosf(camera->yaw) * cosf(camera->pitch);
    camera->forward.y = sinf(camera->pitch);
    camera->forward.z = sinf(camera->yaw) * cosf(camera->pitch);

	camera->forward = Vector3Normalize(camera->forward);
    Vector3 t = {0, 1, 0};
	camera->right = Vector3CrossProduct(camera->forward, t);
	camera->right = Vector3Normalize(camera->right);

	camera->up = Vector3CrossProduct(camera->right, camera->forward);
	camera->up = Vector3Normalize(camera->up);
}

void rotate_pitch(camera_t* camera, float delta_y) {
    camera->pitch += delta_y;
    camera->pitch = Clamp(camera->pitch, -PITCH_MAX, PITCH_MAX);
}

void rotate_yaw(camera_t* camera, float delta_x) {
    camera->yaw += delta_x;
	camera->yaw = Clamp(camera->yaw, -PITCH_MAX, PITCH_MAX);
}

void move_left(camera_t* camera, float velocity) {
    Vector3 movement = Vector3Scale(camera->right, velocity);
	camera->position = Vector3Subtract(camera->position, movement);
}

void move_right(camera_t* camera, float velocity) {
    Vector3 movement = Vector3Scale(camera->right, velocity);
	camera->position = Vector3Add(camera->position, movement);

}

void move_up(camera_t* camera, float velocity) {
    Vector3 movement = Vector3Scale(camera->up, velocity);
	camera->position = Vector3Add(camera->position, movement);
}

void move_down(camera_t* camera, float velocity) {
    Vector3 movement = Vector3Scale(camera->up, velocity);
	camera->position = Vector3Subtract(camera->position, movement);
}

void move_forward(camera_t* camera, float velocity) {
    Vector3 movement = Vector3Scale(camera->forward, velocity);
	camera->position = Vector3Add(camera->position, movement);
}

void move_back(camera_t* camera, float velocity) {
    Vector3 movement = Vector3Scale(camera->forward, velocity);
	camera->position = Vector3Subtract(camera->position, movement);
}
