#ifndef _HKSS_GL_WRAPPER_h
#define _HKSS_GL_WRAPPER_h

#include <stdio.h>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define GET_FN_GL_ERRORS(func, args) {func args; if(get_gl_errors()) { printf("called from " #func " (%s : %d)\n", __FILE__, __LINE__); }}

int get_gl_errors();

GLFWwindow *start_gl_glfw(int res_x, int res_y);

#endif
