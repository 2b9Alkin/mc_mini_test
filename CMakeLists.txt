cmake_minimum_required(VERSION 3.8)
project(mini_craft)

# Set the source files
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c" "src/*.h" "src/*.cpp")

# Create the executable
add_executable(mini_craft ${SOURCES} include/stbi/include/stbi.h include/stbi/src/stbi.c)

# Find OpenGL package
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



#
## Include directories
#target_include_directories(mini_craft PRIVATE include)
#target_include_directories(mini_craft PRIVATE include/stbi/include)
#target_link_libraries(mini_craft PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/glew/src/glew.a")
#target_include_directories(mini_craft PRIVATE glad/include)
#target_include_directories(mini_craft PRIVATE glfw/include)
#
#
## Link libraries
#set(OpenGL_GL_PREFERENCE "GLVND")  # Set OpenGL_GL_PREFERENCE to GLVND
#find_package(OpenGL REQUIRED)
#target_link_libraries(mini_craft PRIVATE OpenGL::GL)
#target_link_libraries(mini_craft PRIVATE glew::GLEW)
#target_link_libraries(mini_craft PRIVATE glad)
#target_link_libraries(mini_craft PRIVATE glfw)
#target_link_libraries(mini_craft PRIVATE fast_obj)

