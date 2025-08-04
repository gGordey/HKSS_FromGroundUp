#ifndef _HKSS_RENDERABLE_h
#define _HKSS_RENDERABLE_h

#include "gl_wrapper.h"
#include "shader.h"
#include "texture.h"
#include "vertex.h"

typedef struct renderable renderable; 
struct renderable {
	GLuint vbo;
	shader_program shader;
	texture texture;
	uint32_t vertex_atrib_generic;
	uint64_t vertex_atrib_size;
};

extern renderable create_renderable();
extern void draw_renderable(renderable target);
extern void push_vertex_atrib(renderable target, int size_bytes);
extern void bind_renderable(renderable target);
extern void unbind_renderable();
extern void renderable_data(renderable target, void *data);


#endif
