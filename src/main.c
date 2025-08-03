#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "texture.h"
#include "shader.h"
#include "vertex.h"
#include "object.h"
#include "gl_wrapper.h"

const int res_x = 640 * 2;
const int res_y = 360 * 2;
static float time = 0.0f;

static void prepare_gl_buffers();
static void pass_uniforms(shader_program shader);
int a(){return 0;}
int main(int argc, char **argv) {
	printf("Hello, 'Silksong Form Grounnd Up'!\n");

    if (!glfwInit()) {
		char *ErrorLogBuf;
		int glfwErrorCode = glfwGetError((const char**)&ErrorLogBuf);
	
		fprintf(stderr,"Not init glfw for some reason, here is an error btw: %s\n", ErrorLogBuf);
		
		glfwTerminate();
		return -1;
	}

	GLFWwindow* window;
	window = glfwCreateWindow(res_x, res_y, "Silksong Form Ground Up", NULL, NULL);
	if(window == NULL) {
		fprintf(stderr, "No GLFW window for you tooday, GIT GUT");
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		fprintf(stderr, "Looks like you are not getting GLAD today, but tommorow for shaw!\n");
		return -1;
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	GET_FN_GL_ERRORS(prepare_gl_buffers, ());
	
	object o = {0};
	o.height = 640.0f;
	o.width = 500.0f;
	
	char *frag_src = read_file("res/shaders/fragment.glsl");
	char *vertex_src = read_file("res/shaders/vertex.glsl");

	shader_program shader = create_shader_program(vertex_src, frag_src); 
	GET_FN_GL_ERRORS(glUseProgram, (shader));

	texture hornet = load_texture("res/hornet.png");
	GET_FN_GL_ERRORS(a, ())

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		time += 0.01f;
		glClearColor(0.2, 0.6, 0.4, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		pass_uniforms(shader);

		draw_object(&o);
		
		glfwSwapBuffers(window);
		glfwPollEvents();

		get_gl_errors();
	}
	
	free(frag_src);
	free(vertex_src);
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
		const int loc_res_x= glGetUniformLocation(shader, "res_x");
		if (loc_res_x != -1) 
			GET_FN_GL_ERRORS(glUniform1i, (loc_res_x, res_x));
		
		const int loc_res_y= glGetUniformLocation(shader, "res_y");
		if (loc_res_y != -1) 
			GET_FN_GL_ERRORS(glUniform1i, (loc_res_y, res_y)); 
		
		const int loc_time = glGetUniformLocation(shader, "time");
		if (loc_time != -1) 
			GET_FN_GL_ERRORS(glUniform1f, (loc_time, time));

		const int loc_sample = glGetUniformLocation(shader, "u_texture");
		if (loc_sample != -1) 
			GET_FN_GL_ERRORS(glUniform1i, (loc_sample, 0));
}
