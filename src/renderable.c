#include "renderable.h"

void unbind_renderable() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void bind_renderable(renderable target) {
	glBindBuffer(GL_ARRAY_BUFFER, target.vbo);
}

void draw_renderable(renderable target) {
	bind_renderable(target);
	glDrawArrays(GL_TRIANGLES, 0, 3);
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
//	unbind_renderable();
}

renderable create_renderable() {
	renderable rend = {0};
	glGenBuffers(1, &rend.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, rend.vbo);
	//glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
	return rend;
}

void renderable_data(renderable target, void *data) {
	bind_renderable(target);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), data, GL_DYNAMIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(vertex), data);
}

void push_vertex_atrib(renderable target, int size_bytes) {
	glEnableVertexAttribArray(target.vertex_atrib_generic);
	glVertexAttribPointer(target.vertex_atrib_generic, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (const void *)(target.vertex_atrib_size));
	++target.vertex_atrib_generic;
	target.vertex_atrib_size += size_bytes;
}

