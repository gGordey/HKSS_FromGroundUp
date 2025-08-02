#include "object.h"
#include "vertex.h"

#include <stdlib.h>
#include <glad/glad.h>

static int res_x = 1;
static int res_y = 1;

void draw_object(object *obj) {
	const vertex points[4] = {
		(vertex){obj->posx / res_x, obj->posy /res_y}, // top-left
		(vertex){(obj->posx + obj->width) / res_x, obj->posy / res_y}, // top-right
		(vertex){obj->posx / res_x, (obj->posy + obj->height) / res_y}, // bot-left
  		(vertex){(obj->posx + obj->width) / res_x, (obj->posy + obj->height) / res_y} // bot-right
	};

	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vertex), points, GL_DYNAMIC_DRAW);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

void set_res(int rx, int ry) {
	res_x = rx;
	res_y = ry;
}
int get_resx() {return res_x;}
int get_resy() {return res_y;}
