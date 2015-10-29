#ifndef _IMAGE_H                 
#define _IMAGE_H               
#define WIN32_LEAN_AND_MEAN

#include "textureManager.h"
#include "constants.h"

class Junk2DSprite
{
	// Image ����
protected:
	Graphics *graphics;     // graphics ��ü�� ����Ű�� ������
	TextureManager *textureManager; // texture manager ��ü�� ����Ű�� ������
	TextureManager texture;

	SpriteData spriteData;  // Graphics::drawSprite() �Լ��� �䱸�ϴ� �����͸� ������ ����ü
	COLOR_ARGB colorFilter; // ��������Ʈ�� �׸� �� ���ͷ� ������ ����. �ƹ��� ��ȭ�� ������� WHITE����
	int     cols;           // ���� �������� ���� ��������Ʈ�� �� ��
	int     startFrame;     // ���� �������� ���� �ִϸ��̼��� ù��° ������ ��ȣ
	int     endFrame;       // ���� �������� ���� �ִϸ��̼��� ������ ������ ��ȣ
	int     currentFrame;   // �ִϸ��̼��� ���� ������ ��ȣ
	float   frameDelay;     // �ִϸ��̼��� �� �������� ������ �ð��̴�.
	float   animTimer;      // ���ϸ��̼��� �ð��� ���ϱ� ���� ����ϴ� ����
	HRESULT hr;             // ǥ�� ��ȯ��
	bool    loop;           // �ִϸ��̼� �ݺ� ����
	bool    visible;        // �̹����� ���̰� �� ��� true�� ��
	bool    initialized;    // �ʱ�ȭ ����
	bool    animComplete;   // �ִϸ��̼��� �Ϸ� �� ��� true�� ��

public:
	Junk2DSprite();			// ������
	virtual ~Junk2DSprite();	// �Ҹ���

	//-----------Get �Լ���---------------//

	// SpriteData ����ü�� �������� ��ȯ
	const virtual SpriteData& getSpriteInfo() { return spriteData; }
	// visible �Ű������� ��ȯ
	virtual bool  getVisible() { return visible; }

	virtual float getX() { return spriteData.x; }		// X ��ġ�� ��ȯ
	virtual float getY() { return spriteData.y; }		// Y ��ġ�� ��ȯ

	virtual float getScale() { return spriteData.scale; }	// scale �� ��ȯ
	virtual int   getWidth() { return spriteData.width; }	// ���� ��ȯ
	virtual int   getHeight() { return spriteData.height; }	// ���̸� ��ȯ

															// X�� �߽��� ��ȯ
	virtual float getCenterX() { return spriteData.x + spriteData.width / 2 * getScale(); }
	// Y�� �߽��� ��ȯ
	virtual float getCenterY() { return spriteData.y + spriteData.height / 2 * getScale(); }

	// ȸ�� ������ �������� ��ȯ
	virtual float getDegrees() { return spriteData.angle*(180.0f / (float)PI); }
	// ȸ�� ������ ���� ������ ��ȯ
	virtual float getRadians() { return spriteData.angle; }

	// �ִϸ��̼� ������ ������ ���� �ð��� ��ȯ
	virtual float getFrameDelay() { return frameDelay; }
	// ������ ���� ��ȣ�� ��ȯ
	virtual int   getStartFrame() { return startFrame; }
	// ������ �� ��ȣ�� ��ȯ
	virtual int   getEndFrame() { return endFrame; }
	// �������� ���� ��ȣ�� ��ȯ
	virtual int   getCurrentFrame() { return currentFrame; }

	// Image�� RECT ����ü�� ��ȯ
	virtual RECT  getSpriteDataRect() { return spriteData.rect; }

	// �ִϸ��̼� �Ϸ� ���¸� ��ȯ
	virtual bool  getAnimationComplete() { return animComplete; }

	// colorFilter ��ȯ
	virtual COLOR_ARGB getColorFilter() { return colorFilter; }
	//------------------------------------//

	////////////////////////////////////////
	//             Set  �Լ���            //
	////////////////////////////////////////

	// X ��ġ ����
	virtual void setX(float newX) { spriteData.x = newX; }
	// Y ��ġ ����
	virtual void setY(float newY) { spriteData.y = newY; }
	// X Y ��ġ ���� ����
	virtual void setXY(float newX, float newY) { spriteData.x = newX;  spriteData.y = newY; }
	// ũ�� ����
	virtual void setScale(float s) { spriteData.scale = s; }

	// ȸ�������� �� ������ �����Ѵ�. 0���� ����, ������ �ð� �������� ������.
	virtual void setDegrees(float deg) { spriteData.angle = deg*((float)PI / 180.0f); }
	// ȸ�������� ���� ������ �����Ѵ�. 0���� ����, ������ �ð� �������� ������.
	virtual void setRadians(float rad) { spriteData.angle = rad; }

	// visible �Ű������� ����
	virtual void setVisible(bool v) { visible = v; }

	// �ִϸ��̼� ������ ������ ���� �ð��� ����
	virtual void setFrameDelay(float d) { frameDelay = d; }
	// �������� ���� ��ȣ�� �� ��ȣ�� ����
	virtual void setFrames(int s, int e) { startFrame = s; endFrame = e; }
	// �������� ���� ��ȣ�� ����
	virtual void setCurrentFrame(int c);

	// spriteData.rect�� ���� currentFrame�� �׸��� ����
	virtual void setRect();

	// spriteData.rect�� r�� ����
	virtual void setSpriteDataRect(RECT r) { spriteData.rect = r; }

	// �ִϸ��̼� ������ ������. lp = true�� ��� ������ ����.
	virtual void setLoop(bool lp) { loop = lp; }
	// �ִϸ��̼� �Ϸ� ���¸� ����
	virtual void setAnimationComplete(bool a) { animComplete = a; };

	// colorFilter�� ����
	virtual void setColorFilter(COLOR_ARGB color) { colorFilter = color; }

	// Set TextureManager
	virtual void setTextureManager(TextureManager *textureM)
	{
		textureManager = textureM;
	}

	////////////////////////////////////////
	//            �ٸ� �Լ���             //
	////////////////////////////////////////

	// �ʱ�ȭ �Լ� (�ڼ��� ������ .cpp��)
	virtual bool Junk2DSprite::initialize(Graphics *g, int width, int height,
		int ncols, TextureManager *textureM);

	// �̹��� �������� ������
	virtual void flipHorizontal(bool flip) { spriteData.flipHorizontal = flip; }
	// �̹��� �������� ������
	virtual void flipVertical(bool flip) { spriteData.flipVertical = flip; }

	// �Լ� ������Ÿ��, �⺻ ������ ���
	virtual void draw(COLOR_ARGB color = graphicsNS::WHITE);

	virtual void setAnimation(float FrameStart, int FrameEnd, int currentFrame, float FrameDelay);

	// ��������Ʈ �����Ϳ� ���� ���� ��� �ش� �Լ� ȣ��,
	//	��������Ʈ �����͸� �̿��� �׸�
	virtual void draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE);

	virtual void update(float frameTime);

	virtual void settingTexture(Graphics *g, const char *filename);
	virtual void settingTexture(Graphics *g, const char *filename, int width, int height, int nCols);

	virtual void onLostDevice() { textureManager->onLostDevice(); };
	virtual void onResetDevice() { textureManager->onResetDevice(); };
};

#endif

