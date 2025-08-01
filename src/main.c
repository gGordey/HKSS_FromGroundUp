#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "shader.h"
#include "vertex.h"

const int res_x = 640 * 2;
const int res_y = 360 * 2;
const float step = 0.02;

void proc_input(GLFWwindow *w, float *ox, float *oy) {
	if (glfwGetKey(w, GLFW_KEY_LEFT)) {
		*ox -= step;
	}
	if (glfwGetKey(w, GLFW_KEY_RIGHT)) {
		*ox += step;
	}
	if (glfwGetKey(w, GLFW_KEY_DOWN)) {
		*oy -= step;
	}
	if (glfwGetKey(w, GLFW_KEY_UP)) {
		*oy += step;
	}
}

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
	
	vertex points[3] =  {
		(vertex){-0.5f, -0.5f},
		(vertex){ 0.0f,  0.5f},
		(vertex){ 0.5f, -0.5f},
	};

	GLuint buffer; 
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void *)0);
	
	char *frag_src = read_file("res/fragment.glsl");
	char *vertex_src = read_file("res/vertex.glsl");
	shader_program shader = create_shader_program(vertex_src, frag_src);
	glUseProgram(shader);
	
	float ox = 0, oy = 0;
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		glClear(GL_COLOR_BUFFER_BIT);

		proc_input(window, &ox, &oy);
		vertex buf[3] = {
			(vertex){points[0].x + ox, points[0].y + oy},
			(vertex){points[1].x + ox, points[1].y + oy},
			(vertex){points[2].x + ox, points[2].y + oy},
		};
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(vertex), buf, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, 3); 


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(shader);
	free(frag_src);
	free(vertex_src);
	glfwTerminate();
}
