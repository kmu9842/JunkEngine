#include "..\\Headers\\textureManager.h"

// 기본 생성자
TextureManager::TextureManager()
{
    texture = NULL;
    width = 0;
    height = 0;
    file = NULL;
    graphics = NULL;
    initialized = false;            
}

// 소멸자
TextureManager::~TextureManager()
{
    SAFE_RELEASE(texture);
}

// 텍스처 로드, 초기화, 실패시 false값 리턴
bool TextureManager::initialize(Graphics *g, const char *f)
{
    try{
        graphics = g;                       // graphics 객체
        file = f;                           // 텍스처 파일

											// 텍스처 로드
        hr = graphics->loadTexture(file, TRANSCOLOR, width, height, texture); 
        if (FAILED(hr))
        {
            SAFE_RELEASE(texture);
            return false;
        }
    }
    catch(...) {return false;}
    initialized = true;                    // 성공적으로 초기화 했을시 true로 설정
    return true;
}

// 그래픽 디바이스가 로스트 상태일 때 호출
void TextureManager::onLostDevice()
{
    if (!initialized)
        return;
    SAFE_RELEASE(texture);
}

// 그래픽 디바이스가 리셋됐을 때 호출
void TextureManager::onResetDevice()
{
    if (!initialized)
        return;
    graphics->loadTexture(file, TRANSCOLOR, width, height, texture);
}


