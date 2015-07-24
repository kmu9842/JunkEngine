#ifndef _IMAGE_H                 
#define _IMAGE_H               
#define WIN32_LEAN_AND_MEAN

#include "textureManager.h"
#include "constants.h"

class Junk2DSprite
{
	// Image 설정
protected:
	Graphics *graphics;     // graphics 객체를 가리키는 포인터
	TextureManager *textureManager; // texture manager 객체를 가리키는 포인터
	TextureManager texture;

	SpriteData spriteData;  // Graphics::drawSprite() 함수가 요구하는 데이터를 포함한 구조체
	COLOR_ARGB colorFilter; // 스프라이트를 그릴 때 필터로 적용할 색상. 아무런 변화가 없을경우 WHITE지정
	int     cols;           // 여러 프레임을 갖는 스프라이트의 행 수
	int     startFrame;     // 여러 프레임을 갖는 애니메이션의 첫번째 프레임 번호
	int     endFrame;       // 여러 프레임을 갖는 애니메이션의 마지막 프레임 번호
	int     currentFrame;   // 애니메이션의 현재 프레임 번호
	float   frameDelay;     // 애니메이션의 각 프레임을 보여줄 시간이다.
	float   animTimer;      // 에니메이션의 시간을 정하기 위해 사용하는 변수
	HRESULT hr;             // 표준 반환형
	bool    loop;           // 애니메이션 반복 여부
	bool    visible;        // 이미지가 보이게 될 경우 true가 됨
	bool    initialized;    // 초기화 여부
	bool    animComplete;   // 애니메이션이 완료 될 경우 true가 됨

public:
	Junk2DSprite();			// 생성자
	virtual ~Junk2DSprite();	// 소멸자

	//-----------Get 함수들---------------//

	// SpriteData 구조체의 참조형을 반환
	const virtual SpriteData& getSpriteInfo() { return spriteData; }
	// visible 매개변수를 반환
	virtual bool  getVisible() { return visible; }

	virtual float getX() { return spriteData.x; }		// X 위치를 반환
	virtual float getY() { return spriteData.y; }		// Y 위치를 반환

	virtual float getScale() { return spriteData.scale; }	// scale 값 반환
	virtual int   getWidth() { return spriteData.width; }	// 폭을 반환
	virtual int   getHeight() { return spriteData.height; }	// 높이를 반환

															// X의 중심을 반환
	virtual float getCenterX() { return spriteData.x + spriteData.width / 2 * getScale(); }
	// Y의 중심을 반환
	virtual float getCenterY() { return spriteData.y + spriteData.height / 2 * getScale(); }

	// 회전 각도를 도단위로 반환
	virtual float getDegrees() { return spriteData.angle*(180.0f / (float)PI); }
	// 회전 각도를 라디안 단위로 반환
	virtual float getRadians() { return spriteData.angle; }

	// 애니메이션 프레임 사이의 지연 시간을 반환
	virtual float getFrameDelay() { return frameDelay; }
	// 프레임 시작 번호를 반환
	virtual int   getStartFrame() { return startFrame; }
	// 프레임 끝 번호를 반환
	virtual int   getEndFrame() { return endFrame; }
	// 프레임의 현재 번호를 반환
	virtual int   getCurrentFrame() { return currentFrame; }

	// Image의 RECT 구조체를 반환
	virtual RECT  getSpriteDataRect() { return spriteData.rect; }

	// 애니메이션 완료 상태를 반환
	virtual bool  getAnimationComplete() { return animComplete; }

	// colorFilter 반환
	virtual COLOR_ARGB getColorFilter() { return colorFilter; }
	//------------------------------------//

	////////////////////////////////////////
	//             Set  함수들            //
	////////////////////////////////////////

	// X 위치 설정
	virtual void setX(float newX) { spriteData.x = newX; }
	// Y 위치 설정
	virtual void setY(float newY) { spriteData.y = newY; }
	// X Y 위치 동시 설정
	virtual void setXY(float newX, float newY) { spriteData.x = newX;  spriteData.y = newY; }
	// 크기 설정
	virtual void setScale(float s) { spriteData.scale = s; }

	// 회전각도를 도 단위로 설정한다. 0도는 위쪽, 각도는 시계 방향으로 움직임.
	virtual void setDegrees(float deg) { spriteData.angle = deg*((float)PI / 180.0f); }
	// 회전각도를 라디안 단위로 설정한다. 0도는 위쪽, 각도는 시계 방향으로 움직임.
	virtual void setRadians(float rad) { spriteData.angle = rad; }

	// visible 매개변수를 설정
	virtual void setVisible(bool v) { visible = v; }

	// 애니메이션 프레임 사이의 지연 시간을 설정
	virtual void setFrameDelay(float d) { frameDelay = d; }
	// 프레임의 시작 번호와 끝 번호를 설정
	virtual void setFrames(int s, int e) { startFrame = s; endFrame = e; }
	// 프레임의 현재 번호를 설정
	virtual void setCurrentFrame(int c);

	// spriteData.rect를 통해 currentFrame을 그리게 설정
	virtual void setRect();

	// spriteData.rect을 r로 설정
	virtual void setSpriteDataRect(RECT r) { spriteData.rect = r; }

	// 애니메이션 루프를 설정함. lp = true일 경우 루프를 실행.
	virtual void setLoop(bool lp) { loop = lp; }
	// 애니메이션 완료 상태를 설정
	virtual void setAnimationComplete(bool a) { animComplete = a; };

	// colorFilter를 설정
	virtual void setColorFilter(COLOR_ARGB color) { colorFilter = color; }

	// Set TextureManager
	virtual void setTextureManager(TextureManager *textureM)
	{
		textureManager = textureM;
	}

	////////////////////////////////////////
	//            다른 함수들             //
	////////////////////////////////////////

	// 초기화 함수 (자세한 설명은 .cpp에)
	virtual bool Junk2DSprite::initialize(Graphics *g, int width, int height,
		int ncols, TextureManager *textureM);

	// 이미지 수평으로 뒤집기
	virtual void flipHorizontal(bool flip) { spriteData.flipHorizontal = flip; }
	// 이미지 수직으로 뒤집기
	virtual void flipVertical(bool flip) { spriteData.flipVertical = flip; }

	// 함수 프로토타입, 기본 색상은 흰색
	virtual void draw(COLOR_ARGB color = graphicsNS::WHITE);

	virtual void setAnimation(float FrameStart, int FrameEnd, int currentFrame, float FrameDelay);

	// 스프라이트 데이터에 값이 들어올 경우 해당 함수 호출,
	//	스프라이트 데이터를 이용해 그림
	virtual void draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE);

	virtual void update(float frameTime);

	virtual void settingTexture(Graphics *g, const char *filename);
	virtual void settingTexture(Graphics *g, const char *filename, int width, int height, int nCols);

	virtual void onLostDevice() { textureManager->onLostDevice(); };
	virtual void onResetDevice() { textureManager->onResetDevice(); };
};

#endif

