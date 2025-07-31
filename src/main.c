#include <stdio.h>

#include <GLFW/glfw3.h>

int main(int argc, char **argv) {
	printf("Hello, 'Silksong Form Grounnd Up'!\n");

    if (!glfwInit()) {
		char *ErrorLogBuf;
		int glfwErrorCode = glfwGetError((const char**)&ErrorLogBuf);

		fprintf(stderr, ErrorLogBuf);
		
		glfwTerminate();
		return 0;
	}

	GLFWwindow* window;
	window = glfwCreateWindow(640 * 2, 360 * 2, "Silksong Form Ground Up", NULL, NULL);
	if(window == NULL) {
		fprintf(stderr, "No GLFW window for you tooday, GIT GUT");
		return -1;
	}

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
