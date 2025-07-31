cmake_minimum_required(VERSION 3.8)

project(HKSS_FromGroundUp)

find_package(OpenGL REQUIRED)

add_library(graphics STATIC glad/src/glad.c)
target_link_libraries(graphics OpenGL::GL glfw)
