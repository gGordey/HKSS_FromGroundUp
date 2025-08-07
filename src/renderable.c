#include "renderable.h"

void unbind_renderable() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void bind_renderable(renderable target) {
	glBindBuffer(GL_ARRAY_BUFFER, target.vbo);
	glBindVertexArray(target.vao);
}

void draw_renderable(renderable target) {
	bind_renderable(target);
  	renderable_use_shader(target);	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
  	unbind_renderable();
}

static const unsigned int id[6] = {
	0, 1, 2,
	1, 2, 3
};
renderable create_renderable() {
	renderable rend = {0};
	glGenVertexArrays(1, &rend.vao);
	glBindVertexArray(rend.vao);

	glGenBuffers(1, &rend.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, rend.vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vertex), NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &rend.ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rend.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), id, GL_DYNAMIC_DRAW);
	unbind_renderable();
	return rend;
}

void renderable_data(renderable target, void *data) {
	bind_renderable(target);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(vertex), data);
	unbind_renderable();
}

void renderable_set_shader(renderable *target, shader_program shader) {
	target->shader = shader;
}

void push_vertex_atrib(renderable *target, int elements_count, int element_size_bytes) {
	bind_renderable(*target);

	glVertexAttribPointer(target->vertex_atrib_generic, elements_count, GL_FLOAT, GL_FALSE, sizeof(vertex), (const void *)(target->vertex_atrib_size));
	glEnableVertexAttribArray(target->vertex_atrib_generic);
	++target->vertex_atrib_generic;
	target->vertex_atrib_size += element_size_bytes * elements_count;

	unbind_renderable();
}

void renderable_use_shader(renderable target) {
	glUseProgram(target.shader);
}
