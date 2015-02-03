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

// 색상 정의
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
    ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

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
    LP_3D   get3D()             { return direct3d; } // LP_3D 타입 리턴
    LP_3DDEVICE get3Ddevice()   { return device3d; } // LP_3DDEVICE 타입 리턴

    HDC     getDC()             { return GetDC(hwnd); }

    // lost된 디바이스가 있는지 테스트
    HRESULT getDeviceState();

    //=============================================================================
    // 실행 속도를 위한 인라인 함수.
    // 함수 호출 오버헤드를 없애 실행속도를 높임.
    //=============================================================================

    // 화면 클리어
    void setBackColor(COLOR_ARGB c) {backColor = c;}

	// Scene 시작, 백버퍼 클리어
    HRESULT beginScene() 
    {
        result = E_FAIL;
        if(device3d == NULL)
            return result;
        // 백버퍼를 배경색으로 클리어
        device3d->Clear(0, NULL, D3DCLEAR_TARGET, backColor, 1.0F, 0);
        result = device3d->BeginScene();          // 씬 그리기 시작
        return result;
    }

	// Scene 종료
    HRESULT endScene() 
    {
        result = E_FAIL;
        if(device3d)
            result = device3d->EndScene();
        return result;
    }
};

#endif

