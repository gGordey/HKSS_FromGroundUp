#include "gl_wrapper.h"
#include <glad/glad.h>

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
