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
	if (!runnerTexture.initialize(graphics, "..\\Resources\\spritesheet.png")) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg texture"));
	}
	if (!runner.initialize(graphics, 240, 210, 2, &runnerTexture)) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg"));
	}

	runner.setX(GAME_WIDTH/4);
	runner.setY(GAME_HEIGHT / 4);

	runner.setFrames(0,3);
	runner.setCurrentFrame(0);
	runner.setFrameDelay(0.1f);
	runner.setDegrees(0);

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

	runner.update(frameTime);
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
	runner.draw();

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
