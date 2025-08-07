#ifndef _HKSS_OBJECT_h
#define _HKSS_OBJECT_h

#include "renderable.h"

typedef struct object object;
struct object {
	float posx;
	float posy;
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

#endif
