#ifndef _HKSS_OBJECT_h
#define _HKSS_OBJECT_h

typedef struct object object;
struct object {
	float posx;
	float posy;
	float width;
	float height;
};
void set_res(int rx, int ry);
int get_resx();
int get_resy();

void draw_object(object *obj);


#endif
