#include "..\\Headers\\textureManager.h"

// �⺻ ������
TextureManager::TextureManager()
{
    texture = NULL;
    width = 0;
    height = 0;
    file = NULL;
    graphics = NULL;
    initialized = false;            
}

// �Ҹ���
TextureManager::~TextureManager()
{
    SAFE_RELEASE(texture);
}

// �ؽ�ó �ε�, �ʱ�ȭ, ���н� false�� ����
bool TextureManager::initialize(Graphics *g, const char *f)
{
    try{
        graphics = g;                       // graphics ��ü
        file = f;                           // �ؽ�ó ����

											// �ؽ�ó �ε�
        hr = graphics->loadTexture(file, TRANSCOLOR, width, height, texture); 
        if (FAILED(hr))
        {
            SAFE_RELEASE(texture);
            return false;
        }
    }
    catch(...) {return false;}
    initialized = true;                    // ���������� �ʱ�ȭ ������ true�� ����
    return true;
}

// �׷��� ����̽��� �ν�Ʈ ������ �� ȣ��
void TextureManager::onLostDevice()
{
    if (!initialized)
        return;
    SAFE_RELEASE(texture);
}

// �׷��� ����̽��� ���µ��� �� ȣ��
void TextureManager::onResetDevice()
{
    if (!initialized)
        return;
    graphics->loadTexture(file, TRANSCOLOR, width, height, texture);
}


