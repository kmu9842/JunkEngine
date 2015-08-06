#ifndef _MAINGAME_H             
#define _MAINGAME_H             
#define WIN32_LEAN_AND_MEAN

#include "game.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class MainGame : public Game
{
private:	

	// ���� ��ҵ�
	Junk2DSprite BackGround;
	Junk2DEntity runner;
	Junk2DEntity runner2;
	
    // ����
	bool vibrate = true;

public:
	MainGame();
    virtual ~MainGame();

    // ���� �⺻ ���� �Լ���
    void initialize(HWND hwnd);
    void update();      // Game Ŭ�����κ��� �ݵ�� �������̵� �ؾ��ϴ� ���� �����Լ�
    void ai();          // "
    void render();      // "
    void releaseAll();
    void resetAll();

};

#endif
