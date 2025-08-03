cmake_minimum_required(VERSION 3.6...4.0)

project(HKSS_FromGroundUp)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

add_library(graphics STATIC stb_impl.c glad/src/glad.c)
target_link_libraries(graphics OpenGL::GL glfw)
