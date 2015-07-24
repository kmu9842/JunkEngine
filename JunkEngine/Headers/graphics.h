#ifndef _GRAPHICS_H            
#define _GRAPHICS_H             
#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif
#include <d3d9.h>
#include <d3dx9.h>
#include "constants.h"
#include "gameError.h"

// DirectX 포인터 타입
#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D       LPDIRECT3D9
#define LP_SPRITE	LPD3DXSPRITE
#define LP_TEXTURE  LPDIRECT3DTEXTURE9  // 
#define VECTOR2		D3DXVECTOR2 

// 색상 정의
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
    ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

namespace graphicsNS
{
	// 일부 공용 색상
	// 0 ~ 255, ARGB순
	const COLOR_ARGB ORANGE  = D3DCOLOR_ARGB(255,255,165,  0);
    const COLOR_ARGB BROWN   = D3DCOLOR_ARGB(255,139, 69, 19);
    const COLOR_ARGB LTGRAY  = D3DCOLOR_ARGB(255,192,192,192);
    const COLOR_ARGB GRAY    = D3DCOLOR_ARGB(255,128,128,128);
    const COLOR_ARGB OLIVE   = D3DCOLOR_ARGB(255,128,128,  0);
    const COLOR_ARGB PURPLE  = D3DCOLOR_ARGB(255,128,  0,128);
    const COLOR_ARGB MAROON  = D3DCOLOR_ARGB(255,128,  0,  0);
    const COLOR_ARGB TEAL    = D3DCOLOR_ARGB(255,  0,128,128);
    const COLOR_ARGB GREEN   = D3DCOLOR_ARGB(255,  0,128,  0);
    const COLOR_ARGB NAVY    = D3DCOLOR_ARGB(255,  0,  0,128);
    const COLOR_ARGB WHITE   = D3DCOLOR_ARGB(255,255,255,255);
    const COLOR_ARGB YELLOW  = D3DCOLOR_ARGB(255,255,255,  0);
    const COLOR_ARGB MAGENTA = D3DCOLOR_ARGB(255,255,  0,255);
    const COLOR_ARGB RED     = D3DCOLOR_ARGB(255,255,  0,  0);
    const COLOR_ARGB CYAN    = D3DCOLOR_ARGB(255,  0,255,255);
    const COLOR_ARGB LIME    = D3DCOLOR_ARGB(255,  0,255,  0);
    const COLOR_ARGB BLUE    = D3DCOLOR_ARGB(255,  0,  0,255);
    const COLOR_ARGB BLACK   = D3DCOLOR_ARGB(255,  0,  0,  0);
    const COLOR_ARGB FILTER  = D3DCOLOR_ARGB(  0,  0,  0,  0);  // use to specify drawing with colorFilter
    const COLOR_ARGB ALPHA25 = D3DCOLOR_ARGB( 64,255,255,255);  // AND with color to get 25% alpha
    const COLOR_ARGB ALPHA50 = D3DCOLOR_ARGB(128,255,255,255);  // AND with color to get 50% alpha
    const COLOR_ARGB BACK_COLOR = NAVY;                                           

	enum DISPLAY_MODE { TOGGLE, FULLSCREEN, WINDOW };
}

struct SpriteData
{
	int			width;			// 스프라이트의 폭, 높이 (단위는 픽셀)
	int			height;
	float		x;				// 화면 위치
	float		y;
	float		scale;			// 크기
	float		angle;			// 라디안 단위의 회전각도
	RECT		rect;			// 큰 텍스처에서 사용할 이미지 선택
	LP_TEXTURE	texture;		// 첵스처를 가리키는 포인터
	bool		flipHorizontal;	// true일 경우 스프라이트를 수평으로 뒤집음
	bool		flipVertical;	// true일 경우 스프라이트를 수직으로 뒤집음
};

class Graphics
{
private:
	// DirectX 포인터
	LP_3D       direct3d;
	LP_3DDEVICE device3d;
	LP_SPRITE	sprite;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE pMode;

	// 다른 변수들
	HRESULT     result;         // 윈도우 생성 결과
	HWND        hwnd;
	bool        fullscreen;
	int         width;
	int         height;
	COLOR_ARGB  backColor;      // 배경색

	// D3D 파라미터 수정
	void    initD3Dpp();

public:
	Graphics();
	virtual ~Graphics();

	void    releaseAll();

	// 텍스처를 불러오는 함수
	HRESULT loadTexture(const char *filename, COLOR_ARGB transcolor,
		UINT &width, UINT &height, LP_TEXTURE &Texture);
	// SpriteData 구조체의 정보를 토대로 스프라이트 그림
	void drawSprite(const SpriteData &spriteData, COLOR_ARGB color);

	// DirectX 그래픽 초기화
	// hw = handle to window
	void    initialize(HWND hw, int width, int height, bool fullscreen);

	// 화면에 백버퍼 표시
	HRESULT showBackbuffer();

	// 어뎁터가 호환되는지 체크함
	bool    isAdapterCompatible();

	// 그래픽디바이스 초기화
	HRESULT reset();

	// get함수들
	LP_3D   get3D() { return direct3d; } // LP_3D 타입 리턴
	LP_3DDEVICE get3Ddevice() { return device3d; } // LP_3DDEVICE 타입 리턴

	HDC     getDC() { return GetDC(hwnd); }

	// lost된 디바이스가 있는지 테스트
	HRESULT getDeviceState();

	//============================================
	// 실행 속도를 위한 인라인 함수.
	// 함수 호출 오버헤드를 없애 실행속도를 높임.
	//============================================

	// 화면 클리어
	void setBackColor(COLOR_ARGB c) { backColor = c; }

	// Sprite 그리기 시작
	void spriteBegin()
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
	}

	// Sprite 그리기 종료
	void spriteEnd()
	{
		sprite->End();
	}

	// Scene 시작, 백버퍼 클리어
	HRESULT beginScene() {
		result = E_FAIL;
		if (device3d == NULL)
			return result;
		// 백버퍼를 배경색으로 클리어
		device3d->Clear(0, NULL, D3DCLEAR_TARGET, backColor, 1.0F, 0);
		result = device3d->BeginScene();          // 씬 그리기 시작
		return result;
	}

	// Scene 종료
	HRESULT endScene() {
		result = E_FAIL;
		if (device3d)
			result = device3d->EndScene();
		return result;
	}

	float Vector2Length(const VECTOR2 *v) { return D3DXVec2Length(v); }
	static float Vector2Dot(const VECTOR2 *v1, const VECTOR2 *v2) {
		return D3DXVec2Dot(v1, v2);
	}
	static void Vector2Normalize(VECTOR2 *v) { D3DXVec2Normalize(v, v);  }
};

#endif

