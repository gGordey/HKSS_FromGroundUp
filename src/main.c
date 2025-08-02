#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "shader.h"
#include "vertex.h"
#include "object.h"

const int res_x = 640 * 2;
const int res_y = 360 * 2;

void prepare_gl_buffers();

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
	prepare_gl_buffers();
	set_res(res_x, res_y); // for object to render reletive to global coordinates, not opengl ones
	
	object o = {0};
	o.height = 100.0f;
	o.width = 100.0f;

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		glClear(GL_COLOR_BUFFER_BIT);

		draw_object(&o);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void prepare_gl_buffers() {
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
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void *)0);
}
