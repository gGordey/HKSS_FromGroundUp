#ifndef _HKSS_SHADER_h
#define _HKSS_SHADER_h

typedef unsigned int shader_program;

extern shader_program create_shader_program(const char *fragment_shader_src, const char *vertex_shader_src);

extern void shader_uniform_i(shader_program shader, const char *name, int value); 
extern void shader_uniform_f(shader_program shader, const char *name, float value); 

extern char *read_file(const char *filename);
extern shader_program create_shader_from_files(const char *vertex_filename, const char *fragment_shader_src);

#endif
