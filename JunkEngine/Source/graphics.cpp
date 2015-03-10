#include "..\\Headers\\graphics.h"

Graphics::Graphics(){
    direct3d = NULL;
    device3d = NULL;
    fullscreen = false;
    width = GAME_WIDTH;    // ���� ���� ����ũ�� �ʱ�ȭ
    height = GAME_HEIGHT;
    backColor = SETCOLOR_ARGB(255,0,0,128); // ����
}

Graphics::~Graphics(){
    releaseAll();
}

void Graphics::releaseAll(){
    SAFE_RELEASE(device3d);
    SAFE_RELEASE(direct3d);
}

// DirectX �ʱ�ȭ
void Graphics::initialize(HWND hw, int w, int h, bool full)
{
    hwnd = hw;
    width = w;
    height = h;
    fullscreen = full;

    // Direct3D �ʱ�ȭ
    direct3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (direct3d == NULL)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Direct3D"));

    initD3Dpp();        // D3D ���������̼� �Ķ���� �ʱ�ȭ
    if(fullscreen){		// Ǯ��ũ�� ����� ���
        if(isAdapterCompatible())   // ��� ȣȯ���� �˻�

            d3dpp.FullScreen_RefreshRateInHz = pMode.RefreshRate;
        else
            throw(GameError(gameErrorNS::FATAL_ERROR, 
            "The graphics device does not support the specified resolution and/or format."));
    }

    D3DCAPS9 caps;
    DWORD behavior;
    result = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
    if( (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
            caps.VertexShaderVersion < D3DVS_VERSION(1,1) )
        behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;  
    else
        behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING; 

    //Direct3D ����̽� ����
    result = direct3d->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hwnd,
        behavior,
        &d3dpp, 
        &device3d);

    if (FAILED(result))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D device"));

	result = D3DXCreateSprite(device3d,&sprite);

	if (FAILED(result))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D sprite"));
 
}

// D3D ���������̼� �Ķ���� �ʱ�ȭ
void Graphics::initD3Dpp(){
    try{
        ZeroMemory(&d3dpp, sizeof(d3dpp));     
		
        d3dpp.BackBufferWidth   = width;
        d3dpp.BackBufferHeight  = height;
        if(fullscreen)                                  // Ǯ��ũ�� ����
            d3dpp.BackBufferFormat  = D3DFMT_X8R8G8B8;  // 24��Ʈ ����
        else
            d3dpp.BackBufferFormat  = D3DFMT_UNKNOWN;   // ����ũ�鿡 ���� ����
        d3dpp.BackBufferCount   = 1;
        d3dpp.SwapEffect        = D3DSWAPEFFECT_DISCARD;
        d3dpp.hDeviceWindow     = hwnd;
        d3dpp.Windowed          = (!fullscreen);
        d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;
    } 
	catch(...){
        throw(GameError(gameErrorNS::FATAL_ERROR, 
                "Error initializing D3D presentation parameters"));

    }
}

void Graphics::drawSprite(const SpriteData &spriteData, COLOR_ARGB color){	
	if (spriteData.texture == NULL) // �ؽ�ó�� ������� �׳� ����
		return;

	// ��������Ʈ�� �߽��� ã��
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2(
		(float)(spriteData.width/2 * spriteData.scale),
		(float)(spriteData.height/2 * spriteData.scale));

	// ��������Ʈ�� ȭ�� ��ġ
	D3DXVECTOR2 translate = D3DXVECTOR2((float)spriteData.x, (float)spriteData.y);

	// x, y ũ�� ����
	D3DXVECTOR2 scaling(spriteData.scale, spriteData.scale);

	// �������� ������
	if (spriteData.flipHorizontal) {
		scaling.x *= -1;
		// ������ �̹����� �߽��� ������
		spriteCenter.x -= (float)(spriteData.width / 2 * spriteData.scale);
		// ������ �̹����� ���������� �̵����� ���� ��ġ�� �ְ���
		translate.x += (float)(spriteData.width * spriteData.scale);
	}

	// �������� ������
	if (spriteData.flipHorizontal) {
		scaling.y *= -1;
		spriteCenter.y -= (float)(spriteData.height / 2 * spriteData.scale);
		translate.y += (float)(spriteData.height * spriteData.scale);
	}

	// ��������Ʈ�� ȸ��, ũ�� ����, ��ġ�ϱ� ���� ����� �����Ѵ�.
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,					// ���
		NULL,						// �������� ���� ������� ����
		0.0f,						// ũ�� ���� ȸ�� ����
		&scaling,					// ũ�� ���� ��
		&spriteCenter,				// ȸ�� �߽�
		(float)(spriteData.angle),	// ȸ�� ����
		&translate					// X, Y ��ġ
	);

	// ��������Ʈ���� ��Ŀ� ���� �˷��ش�.
	sprite->SetTransform(&matrix);

	// ��������Ʈ�� �׸���.
	sprite->Draw(spriteData.texture, &spriteData.rect, NULL, NULL, color);

	// ------------------------------------------------------------------ //
	// �׷��Ƚ� �� ���� -> ��������Ʈ ���� -> ����� ���� ��������Ʈ ��ȯ // 
	// -> ��������Ʈ �׸���(�Ǵ� ����� ���� ��������Ʈ ��ȯ���� �ݺ�) -> //
	// ��������Ʈ ���� -> �׷��Ƚ� �� ����		                          //
	// ------------------------------------------------------------------ //
}

HRESULT Graphics::loadTexture(const char *filename, COLOR_ARGB transcolor,
								UINT &width, UINT &height, LP_TEXTURE &texture){
	
	// ���� ������ �б� ���� ����ü
	D3DXIMAGE_INFO info;
	result = E_FAIL;

	try {
		if (filename == NULL) { // ������ ������� ���� ȣ��
			texture = NULL;
			return D3DERR_INVALIDCALL;
		}

		// ���Ϸκ��� ���� ���̸� ��
		result = D3DXGetImageInfoFromFile(filename,&info);
		if (result != D3D_OK) {
			return result;
		}
		width = info.Width;
		height = info.Height;
		
		// ������ �ҷ��� �� �ý�ó ����
		result = D3DXCreateTextureFromFileEx(
			device3d,			// 3D ����̽�			
			filename,			// �̹��� ���ϸ�
			info.Width,			// �ؽ�ó ��, ����
			info.Height,
			1,					// �Ӹ� ����(�������� ���� �� 1���)
			0,					// ����Ұ� (DWORD Usage)
			D3DFMT_UNKNOWN,		// ǥ������
			D3DPOOL_DEFAULT,	// �ؽ�ó�� ���� �޸� Ŭ����
			D3DX_DEFAULT,		// �̹��� ����
			D3DX_DEFAULT,		// �� ����
			transcolor,			// ������ ���� ���� Ű
			&info,				// ��Ʈ�� ���� ����
			NULL,				// ���� �ȷ�Ʈ
			&texture			// �ؽ�ó
			);
	}
	catch (...) {
		throw (GameError(gameErrorNS::FATAL_ERROR, "ERROR in Graphics::loadTexture"));
	}

	return result;
}

// ���÷��� �����
HRESULT Graphics::showBackbuffer(){
    result = E_FAIL;    // ��ҿ��� FAIL��, �����ϸ� ��ȯ
    // ����� ��ũ�� ����
    result = device3d->Present(NULL, NULL, NULL, NULL);
    return result;
}

// ��Ͱ� ȣȯ�Ǵ��� üũ
bool Graphics::isAdapterCompatible(){
    UINT modes = direct3d->GetAdapterModeCount(D3DADAPTER_DEFAULT, 
                                            d3dpp.BackBufferFormat);
    for(UINT i=0; i<modes; i++){
        result = direct3d->EnumAdapterModes( D3DADAPTER_DEFAULT, 
                                        d3dpp.BackBufferFormat,
                                        i, &pMode);
        if( pMode.Height == d3dpp.BackBufferHeight &&
            pMode.Width  == d3dpp.BackBufferWidth &&
            pMode.RefreshRate >= d3dpp.FullScreen_RefreshRateInHz)
            return true;
    }
    return false;
}

// �ν�Ʈ ���µ� ����̽� Ȯ��
HRESULT Graphics::getDeviceState(){ 
    result = E_FAIL;   // ��ҿ��� FAIL��, �����ϸ� ��ȯ
    if (device3d == NULL)
        return  result;
    result = device3d->TestCooperativeLevel(); 
    return result;
}

// �׷��� ����̽� ����
HRESULT Graphics::reset(){
    result = E_FAIL;    
    initD3Dpp();                        
    result = device3d->Reset(&d3dpp);   // �׷��� ����̽� ������ ����
    return result;
}

