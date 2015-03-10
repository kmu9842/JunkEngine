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

	// ��� �ؽ���
	if (!BGTexture.initialize(graphics, "..\\Resources\\bg.png")) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg texture"));
	}

	// ��� �̹���
	if (!BG.initialize(graphics, 0, 0, 0, &BGTexture)) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg"));
	}

	BG.setX(GAME_WIDTH*0.5f - BG.getWidth()*0.5f);
	BG.setY(GAME_HEIGHT*0.5f - BG.getHeight()*0.5f);

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

	BG.draw();

	graphics->spriteEnd();
}

// ����� ���� �޸� ����
void MainGame::releaseAll()
{
	BGTexture.onLostDevice();

    Game::releaseAll();
    return;
}

// �׷��� ����̽� ����
void MainGame::resetAll()
{
	BGTexture.onResetDevice();

    Game::resetAll();
    return;
}
