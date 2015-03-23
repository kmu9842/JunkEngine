#include "..\\Headers\\MainGame.h"

// ������
MainGame::MainGame()
{}

// �Ҹ���
MainGame::~MainGame()
{
    releaseAll();           
}

// ���� �ʱ�ȭ
void MainGame::initialize(HWND hwnd)
{
    Game::initialize(hwnd);

	BackGround.settingTexture(graphics,"..\\Resources\\bg.png");

    return;
}

// ���� ���� �޼���
void MainGame::update()
{
	if (vibrate) {
		input->gamePadVibrateLeft(0, 65535, 1.0);
		vibrate = false;
	}
	if (!vibrate) {
		input->gamePadVibrateRight(0, 65535, 1.0);
		vibrate = true;
	}
}

// AI
void MainGame::ai()
{}

// �浹 ó��
void MainGame::collisions()
{}

// ������, �̹��� ǥ��
void MainGame::render()
{
	graphics->spriteBegin();

	BackGround.draw();

	graphics->spriteEnd();
}

// ����� ���� �޸� ����
void MainGame::releaseAll()
{
	BackGround.onLostDevice();

    Game::releaseAll();
    return;
}

// �׷��� ����̽� ����
void MainGame::resetAll()
{
	BackGround.onResetDevice();

    Game::resetAll();
    return;
}
