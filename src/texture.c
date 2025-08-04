#include "texture.h" 
#include "gl_wrapper.h"

texture load_texture(const char *filename) {
	texture t = {0};
	t.filename = filename;
	stbi_set_flip_vertically_on_load(1);
	t.data = stbi_load(filename, &t.w, &t.h, &t.bpp, 4);

	GET_FN_GL_ERRORS(glGenTextures, (1, &t.id));
	GET_FN_GL_ERRORS(glBindTexture, (GL_TEXTURE_2D, t.id));

	GET_FN_GL_ERRORS(glTexParameteri, (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GET_FN_GL_ERRORS(glTexParameteri, (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GET_FN_GL_ERRORS(glTexParameteri, (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	GET_FN_GL_ERRORS(glTexParameteri, (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));

	GET_FN_GL_ERRORS(glTexImage2D, (GL_TEXTURE_2D, 0, GL_RGBA8, t.w, t.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, t.data));

	return t;
}
