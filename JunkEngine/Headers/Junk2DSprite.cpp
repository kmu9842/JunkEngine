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
	// ��� �ؽ���
	if (!Texture.initialize(g, filename)) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg texture"));
	}

	// ��� �̹���
	if (!Image.initialize(g, 0, 0, 0, &Texture)) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg"));
	}
}

void Junk2DSprite::onLostDevice() {
	Texture.onLostDevice();
}

void Junk2DSprite::onResetDevice() {
	Texture.onResetDevice();
}

