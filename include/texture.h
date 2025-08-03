#ifndef _HKSS_TEXTURE_h
#define _HKSS_TEXTURE_h

#include <stb_image.h>
#include <glad/glad.h>

typedef struct texture texture;
struct texture {
	GLuint id;
	unsigned char *data;
	const char *filename;
	int h, w;
	int bpp;
};

texture load_texture(const char *filename);

#endif
