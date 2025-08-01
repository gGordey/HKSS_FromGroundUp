#include <stdio.h>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "shader.h"
#include "vertex.h"

static const char *vertex_src = 
"\
#version 330 core\n\
layout(location = 0) in vec4 pos;\n\
void main() {\n\
	gl_Position = pos;\n\
}"; 

static const char *frag_src = 
"\
#version 330 core\n\
layout(location = 0) out vec4 color;\n\
void main() {\n\
	color = vec4(0.5, 0.0, 0.5, 1.0);\n\
}"; 

const int res_x = 640 * 2;
const int res_y = 360 * 2;

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
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(vertex), points, GL_DYNAMIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void *)0);

	shader_program shader = create_shader_program(vertex_src, frag_src);
	glUseProgram(shader);

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3); 

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shader);
	glfwTerminate();
}
