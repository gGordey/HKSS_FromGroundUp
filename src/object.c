#include "object.h"
#include "vertex.h"
#include "gl_wrapper.h"

#include <stdlib.h>
#include <glad/glad.h>

static int res_x = 1;
static int res_y = 1;

void draw_object(object *obj) {
	const vertex points[4] = {
		(vertex){obj->posx, obj->posy, 0.0f, 0.0f}, // top-left
		(vertex){obj->posx + obj->width, obj->posy, 1.0f, 0.0f}, // top-right
		(vertex){obj->posx, obj->posy + obj->height, 0.0f, 1.0f}, // bot-left
  		(vertex){obj->posx + obj->width, obj->posy + obj->height, 1.0f, 1.0f} // bot-right
	};

	GET_FN_GL_ERRORS(glBufferSubData,(GL_ARRAY_BUFFER, 0, 4 * sizeof(vertex), points));
	GET_FN_GL_ERRORS(glDrawElements, (GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL)); 
}

void set_res(int rx, int ry) {
	res_x = rx;
	res_y = ry;
}
int get_resx() {return res_x;}
int get_resy() {return res_y;}
