//
// Created by cprkan on 7/17/23.
//

#include "../glfw/include/glfw3.h"
#include <../vulkan/vulkan.h>

void make_vk_instance() {

}

int main(int argc, char** argv) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan", NULL, NULL);

    make_vk_instance();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}