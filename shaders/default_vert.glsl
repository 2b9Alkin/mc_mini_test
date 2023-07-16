#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aVoxelId;
layout (location = 2) in float aFaceId;

uniform mat4 uProjection;
uniform mat4 uView;

out vec4 voxel_color;

vec4 hash_color(float p) {
    vec4 p3 = fract(vec4(p * 21.2) * vec4(0.205f, 0.1201f, 0.0896f, 1.0f));
    p3 += dot(p3, p3 + 33.33f);
    return fract((p3.xxyw + p3.yzzw) * p3.xyzw) + 0.05f;
}

void main() {
    voxel_color = hash_color(aVoxelId);
    mat4 model = mat4(1.0); // Identity matrix (no transformations applied)
    gl_Position = uProjection * uView * model * vec4(aPos, 1.0);
}
