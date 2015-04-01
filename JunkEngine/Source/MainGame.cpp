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

	runner.settingTexture(graphics, "..\\Resources\\spritesheet.png",240,210,2);
	runner.setScale(GAME_WIDTH / 4, GAME_HEIGHT / 4);
	runner.setAnimation(0,3,0,0.1f);
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

	runner.Play(frameTime);

	if (input->isKeyDown(VK_RIGHT)) {
		runner.setX(runner.getX() + frameTime * 80.0f);
		if (runner.getX() > GAME_WIDTH) {
			runner.setX((float)-runner.getWidth());
		}
		runner.update(frameTime);
	}

	if (input->isKeyDown(VK_LEFT)) {
		runner.setX(runner.getX() - frameTime * 80.0f);
		if (runner.getX() < -runner.getWidth()) {
			runner.setX((float)GAME_WIDTH);
		}
		runner.update(frameTime);
	}

	if (input->isKeyDown(VK_UP)) {
		runner.setY(runner.getY() - frameTime * 80.0f);
		if (runner.getY() < -runner.getHeight()) {
			runner.setY((float)GAME_HEIGHT);
		}
		runner.update(frameTime);
	}

	if (input->isKeyDown(VK_DOWN)) {
		runner.setY(runner.getY() + frameTime * 80.0f);
		if (runner.getY() > GAME_HEIGHT) {
			runner.setY((float)-runner.getHeight());
		}
		runner.update(frameTime);
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
