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
{}

// ����� ���� �޸� ����
void MainGame::releaseAll()
{
    Game::releaseAll();
    return;
}

// �׷��� ����̽� ����
void MainGame::resetAll()
{
    Game::resetAll();
    return;
}
