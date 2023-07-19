cmake_minimum_required(VERSION 3.8)
project(mini_craft)

# Set the source files
#file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c" "src/*.h" "src/*.cpp")
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c" "src/*.h")

# Create the executable
add_executable(mini_craft ${SOURCES} include/stbi/include/stbi.h include/stbi/src/stbi.c)

# Find OpenGL package
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# Find GLEW library
find_library(GLEW_LIBRARY NAMES GLEW PATHS /path/to/glew/lib)

# Check if GLEW library was found
if (GLEW_LIBRARY)
    target_link_libraries(mini_craft PRIVATE ${GLEW_LIBRARY})
else()
    message(FATAL_ERROR "GLEW library not found")
endif()

# Link OpenGL libraries
target_link_libraries(mini_craft PRIVATE OpenGL::GL)

# Include directories
include_directories(include)
include_directories(glew/include)
include_directories(glad/include)
include_directories(glfw/include)

target_link_libraries(mini_craft PRIVATE m)

# Link GLFW and fast_obj libraries
target_link_libraries(mini_craft PRIVATE glfw)

