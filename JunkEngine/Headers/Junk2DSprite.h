#ifndef _JUNK2DSPRITE_H             
#define _JUNK2DSPRITE_H           
#define WIN32_LEAN_AND_MEAN

#include "graphics.h"
#include "textureManager.h"
#include "image.h"
#include "Game.h"

class Junk2DSprite : public Image
{
public:
	Junk2DSprite();
	~Junk2DSprite();

	void draw();
	void settingTexture(Graphics *g, const char *filename);
	void settingTexture(Graphics *g, const char *filename, int width, int height, int nCols);
	void setScale(int x, int y);
	void Play(float frameTime);
	void setAnimation(float FrameStart,int FrameEnd,int currentFrame, float FrameDelay);
	void onLostDevice();
	void onResetDevice();

private:
	TextureManager Texture;
	Image Image;

	Graphics *g;
	const char *file;
	float x, y;
	float width, height;
};

#endif