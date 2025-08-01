#ifndef _HKSS_SHADER_h
#define _HKSS_SHADER_h

typedef unsigned int shader_program;

extern shader_program create_shader_program(const char *fragment_shader_src, const char *vertex_shader_src);

#endif
