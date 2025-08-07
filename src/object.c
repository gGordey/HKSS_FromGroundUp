#include "object.h"
#include "vertex.h"
#include "gl_wrapper.h"

#include <stdlib.h>
#include <glad/glad.h>

void draw_object(object *obj) {
	const vertex points[4] = {
		(vertex){obj->posx, obj->posy, 0.0f, 0.0f}, // top-left
		(vertex){obj->posx + obj->width, obj->posy, 1.0f, 0.0f}, // top-right
		(vertex){obj->posx, obj->posy + obj->height, 0.0f, 1.0f}, // bot-left
  		(vertex){obj->posx + obj->width, obj->posy + obj->height, 1.0f, 1.0f} // bot-right
	};

	renderable_data(obj->rend, (void *)points);
	draw_renderable(obj->rend);
}

object create_object(float width, float height) {
	object obj = {0};
	obj.width = width;
	obj.height = height;
	obj.rend = create_renderable();

	push_vertex_atrib(&obj.rend, 2, sizeof(float)); // pos.xy
	push_vertex_atrib(&obj.rend, 2, sizeof(float)); // uv.xy

	return obj;
}

void destroy_object(object *obj);

void object_position(object *obj, float x, float y) {
	obj->posx = x;
	obj->posy = y;
}
