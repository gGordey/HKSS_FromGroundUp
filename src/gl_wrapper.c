#include "gl_wrapper.h"

#define MAKE_ERR_CASE(err) case err: printf("OpenGL error: "#err" (err_code: %d)\n",  err_code); break;
int get_gl_errors() {
	unsigned int err_code = 0;
	int errors = 0;
	while ((err_code = glGetError())) {
		++errors;
		switch (err_code) {
			MAKE_ERR_CASE(GL_INVALID_ENUM)
			MAKE_ERR_CASE(GL_INVALID_VALUE)
			MAKE_ERR_CASE(GL_INVALID_OPERATION)
			MAKE_ERR_CASE(GL_INVALID_FRAMEBUFFER_OPERATION)
			MAKE_ERR_CASE(GL_OUT_OF_MEMORY)
			MAKE_ERR_CASE(GL_STACK_UNDERFLOW)
			MAKE_ERR_CASE(GL_STACK_OVERFLOW)
		}
	}
	return errors;
}

GLFWwindow *start_gl_glfw(int res_x, int res_y) {
    if (!glfwInit()) {
		char *ErrorLogBuf;
		int glfwErrorCode = glfwGetError((const char**)&ErrorLogBuf);
	
		fprintf(stderr,"Not init glfw for some reason, here is an error btw: %s\n", ErrorLogBuf);
		
		glfwTerminate();
		return NULL;
	}

	GLFWwindow* window;
	window = glfwCreateWindow(res_x, res_y, "Silksong Form Ground Up", NULL, NULL);
	if(window == NULL) {
		fprintf(stderr, "No GLFW window for you tooday, GIT GUT");
		return NULL;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		fprintf(stderr, "Looks like you are not getting GLAD today, but tommorow for shaw!\n");
		return NULL;
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	return window;
}
