#ifndef _HKSS_GL_WRAPPER_h
#define _HKSS_GL_WRAPPER_h

#include <stdio.h>

#define GET_FN_GL_ERRORS(func, args) {func args; if(get_gl_errors()) { printf("called from " #func "\n"); }}

int get_gl_errors();

#endif
