#include "shader.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <glad/glad.h>

#include "io.h"

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

char *read_file(const char *filename) {
	FILE *f = fopen_rel(filename, "r");

	if (f == NULL) {
		fprintf(stderr, "Could not read file %s\n", filename);	
		return NULL;
	} 
	fseek(f, 0, SEEK_END);
	int f_size = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	char *data = malloc((f_size+1) * sizeof(char));
	fread(data, f_size, 1, f);
	
	data[f_size] = 0;

	fclose(f);
	return data;
}
