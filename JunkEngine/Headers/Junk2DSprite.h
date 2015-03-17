#ifndef _JUNK2DSPRITE_H             
#define _JUNK2DSPRITE_H           
#define WIN32_LEAN_AND_MEAN

#include "graphics.h"

class Junk2DSprite
{
public:
	Junk2DSprite();
	~Junk2DSprite();

	void drawSprite();

private:
	Graphics *g;
	const char *file;
	float x, y;
	float width, height;
};

#endif