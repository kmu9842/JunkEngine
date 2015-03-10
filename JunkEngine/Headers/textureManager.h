#ifndef _TEXTUREMANAGER_H       
#define _TEXTUREMANAGER_H      
#define WIN32_LEAN_AND_MEAN

#include "graphics.h"
#include "constants.h"

class TextureManager
{
    // TextureManager ����
  private:
    UINT       width;       // �ʺ�
    UINT       height;      // �ʺ�
    LP_TEXTURE texture;     // �ؽ�ó ������ �ּ�
    const char *file;       // �����̸�
    Graphics *graphics;     // graphics ������
    bool    initialized;    // �ʱ�ȭ ���� Ȯ��
    HRESULT hr;             // ���� Ÿ��

  public:
	  // ������, �Ҹ���
    TextureManager();
    virtual ~TextureManager();

    // �ؽ�ó�� ����Ű�� �����͸� ��ȯ
    LP_TEXTURE getTexture() const {return texture;}
    UINT getWidth() const {return width;}	// �ؽ�ó�� ���� ��ȯ
    UINT getHeight() const {return height;}	// �ؽ�ó�� ���̸� ��ȯ

    virtual bool initialize(Graphics *g, const char *file);
    virtual void onLostDevice();
    virtual void onResetDevice();
};

#endif

