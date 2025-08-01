#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>

static GLuint compile_shader(unsigned int type, const char *src) {
	GLuint id = glCreateShader(type);
	glShaderSource(id, 1, &src, NULL); 
	glCompileShader(id);

	int result = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int len = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
		char msg[len];
		glGetShaderInfoLog(id, len, &len, msg);
		fprintf(stderr, "Failed to compile shader(%s), here is an error: %s\n", 
				type == GL_VERTEX_SHADER ? "vertex" : "fragment", msg
			   );
		return 0;
	}

	return id;
}

shader_program create_shader_program(const char *vertex_shader_src, const char *fragment_shader_src) {
	shader_program prog = glCreateProgram(); 
	GLuint vertex = compile_shader(GL_VERTEX_SHADER, vertex_shader_src);
	GLuint fragment = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_src);
	if (vertex == 0 || fragment == 0) {
		exit(1);
	}

	glAttachShader(prog, vertex);	
	glAttachShader(prog, fragment);
	glLinkProgram(prog);
	glValidateProgram(prog);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
	return prog;
}
