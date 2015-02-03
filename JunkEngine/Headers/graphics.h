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

// DirectX ������ Ÿ��
#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D       LPDIRECT3D9
#define LP_SPRITE	LPD3DXSPRITE

// ���� ����
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
    ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

class Graphics
{
private:
    // DirectX ������
    LP_3D       direct3d;
    LP_3DDEVICE device3d;
	LP_SPRITE	sprite;
    D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE pMode;

    // �ٸ� ������
    HRESULT     result;         // ������ ���� ���
    HWND        hwnd;
    bool        fullscreen;
    int         width;
    int         height;
    COLOR_ARGB  backColor;      // ����

    // D3D �Ķ���� ����
    void    initD3Dpp();

public:
    Graphics();
    virtual ~Graphics();

    void    releaseAll();

    // DirectX �׷��� �ʱ�ȭ
    // hw = handle to window
    void    initialize(HWND hw, int width, int height, bool fullscreen);

    // ȭ�鿡 ����� ǥ��
    HRESULT showBackbuffer();

    // ��Ͱ� ȣȯ�Ǵ��� üũ��
    bool    isAdapterCompatible();

	// �׷��ȵ���̽� �ʱ�ȭ
    HRESULT reset();

    // get�Լ���
    LP_3D   get3D()             { return direct3d; } // LP_3D Ÿ�� ����
    LP_3DDEVICE get3Ddevice()   { return device3d; } // LP_3DDEVICE Ÿ�� ����

    HDC     getDC()             { return GetDC(hwnd); }

    // lost�� ����̽��� �ִ��� �׽�Ʈ
    HRESULT getDeviceState();

    //=============================================================================
    // ���� �ӵ��� ���� �ζ��� �Լ�.
    // �Լ� ȣ�� ������带 ���� ����ӵ��� ����.
    //=============================================================================

    // ȭ�� Ŭ����
    void setBackColor(COLOR_ARGB c) {backColor = c;}

	// Scene ����, ����� Ŭ����
    HRESULT beginScene() 
    {
        result = E_FAIL;
        if(device3d == NULL)
            return result;
        // ����۸� �������� Ŭ����
        device3d->Clear(0, NULL, D3DCLEAR_TARGET, backColor, 1.0F, 0);
        result = device3d->BeginScene();          // �� �׸��� ����
        return result;
    }

	// Scene ����
    HRESULT endScene() 
    {
        result = E_FAIL;
        if(device3d)
            result = device3d->EndScene();
        return result;
    }
};

#endif

