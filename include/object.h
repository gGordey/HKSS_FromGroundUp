#ifndef _HKSS_OBJECT_h
#define _HKSS_OBJECT_h

#include "renderable.h"

#ifndef OBJECT_CAP
	#define OBJECT_CAP 1024
#endif

typedef struct object object;
struct object {
	float posx;
	float posy;
	float velx;
	float vely;
	float width;
	float height;
	renderable rend; 
};
void set_res(int rx, int ry);
int get_resx();
int get_resy();

extern void draw_object(object *obj);
extern object create_object(float width, float height);
extern void destroy_object(object *obj);
extern void object_position(object *obj, float x, float y);
extern void object_add_texture(object *obj, texture texture);
extern object create_object_from_texture(float scale, const char *filename, shader_program shader);
extern void object_update(object *obj);

typedef struct object_system object_system;
struct object_system {
	object objects[OBJECT_CAP];
	unsigned int size;
};

extern object_system create_object_system();
extern void object_system_push(object_system *object_system, object object);

#endif
