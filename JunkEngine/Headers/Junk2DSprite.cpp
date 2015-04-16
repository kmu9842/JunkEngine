/*
#include "Junk2DSprite.h"

Junk2DSprite::Junk2DSprite()
{
}

Junk2DSprite::~Junk2DSprite()
{
}

void Junk2DSprite::draw()
{
	Image.draw();
}

void Junk2DSprite::settingTexture(Graphics *g, const char *filename)
{
	// 배경 텍스쳐
	if (!Texture.initialize(g, filename)) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg texture"));
	}

	// 배경 이미지
	if (!Image.initialize(g, 0, 0, 0, &Texture)) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg"));
	}
}

void Junk2DSprite::settingTexture(Graphics *g, const char *filename, int width, int height, int nCols)
{
	// 배경 텍스쳐
	if (!Texture.initialize(g, filename)) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg texture"));
	}

	// 배경 이미지
	if (!Image.initialize(g, width, height, nCols, &Texture)) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg"));
	}
}

void Junk2DSprite::setScale(int x, int y)
{
	//Image.setX(x);
	//Image.setY(y);
}

void Junk2DSprite::setXY(int x, int y)
{
	Image.setX(x);
	Image.setY(y);
}

void Junk2DSprite::Play(float frameTime)
{
	Image.update(frameTime);
}

void Junk2DSprite::setAnimation(float FrameStart, int FrameEnd, int currentFrame, float FrameDelay)
{
	Image.setFrames(FrameStart, FrameEnd);
	Image.setCurrentFrame(currentFrame);
	Image.setFrameDelay(FrameDelay);
}

void Junk2DSprite::onLostDevice() {
	Texture.onLostDevice();
}

void Junk2DSprite::onResetDevice() {
	Texture.onResetDevice();
}

*/