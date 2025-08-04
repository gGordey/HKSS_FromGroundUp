#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "texture.h"
#include "shader.h"
#include "vertex.h"
#include "object.h"
#include "renderable.h"
#include "gl_wrapper.h"

const int res_x = 640 * 2;
const int res_y = 360 * 2;
static float time = 0.0f;

static void prepare_gl_buffers();
static void pass_uniforms(shader_program shader);

int main(int argc, char **argv) {
	printf("Hello, 'Silksong Form Grounnd Up'!\n");

	GLFWwindow *window = start_gl_glfw(res_x, res_y);
	get_gl_errors();

	const unsigned int id[6] = {
		0, 1, 2,
		1, 2, 3
	};
	GLuint ibo; 
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), id, GL_DYNAMIC_DRAW);

	
	object o = {0};
	o.height = 640.0f;
	o.width = 1500.0f;
	
	shader_program shader = create_shader_from_files("res/shaders/fragment.glsl","res/shaders/vertex.glsl");
	get_gl_errors();
//GET_FN_GL_ERRORS(glUseProgram, (shader));

	texture hornet = load_texture("res/hornet.png");
	const vertex points[4] = {
		(vertex){-0.5,-0.5, 0.0, 0.0},
		(vertex){-0.5, 0.5, 0.0, 1.0},
		(vertex){ 0.5,-0.5, 1.0, 0.0},
  		(vertex){ 0.5, 0.5, 1.0, 1.0} 
	};
	const float point[6] = {
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0 
	};

	renderable r = create_renderable(); 
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void *)0);
	glEnableVertexAttribArray(0);

	renderable_data(r, (void *)point);

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		time += 0.01f;
		//glClearColor(0.2, 0.6, 0.4, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

//		pass_uniforms(shader);

		draw_renderable(r);

//		draw_object(&o);
		
		glfwSwapBuffers(window);
		glfwPollEvents();

		get_gl_errors();
	}
	
	glfwTerminate();
}

void prepare_gl_buffers() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	const unsigned int id[6] = {
		0, 1, 2,
		1, 2, 3
	};
	GLuint ibo; 
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), id, GL_DYNAMIC_DRAW);

	GLuint buffer; 
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vertex), NULL, GL_DYNAMIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void *)(sizeof(float)*2));
}

void pass_uniforms(shader_program shader) {
		GET_FN_GL_ERRORS(shader_uniform_i, (shader, "u_res_x", res_x));
		GET_FN_GL_ERRORS(shader_uniform_i, (shader, "u_res_y", res_y));
		GET_FN_GL_ERRORS(shader_uniform_f, (shader, "u_time", time));
		GET_FN_GL_ERRORS(shader_uniform_i, (shader, "u_texture", 0));
}
