#version 460 core

in vec3 voxel_color;
out vec4 fragColor;

void main() {
    fragColor = vec4(voxel_color, 1.0f);
//    fragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
}
