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

	// �̹��� ������ �̸� ����
	player.initialize(graphics, "..\\Resources\\player.png", 32, 32, 1);
	player.setDegrees(0);
	player.setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2+16);
	addEntity(&player);
	map = new Map(32, 32, graphics);

	for (int i = 0; i < map->getWidth(); i++) {
		for (int j = 0; j < map->getHeight(); j++) {
			addEntity(map->getTiles(i,j));
		}
	}

	// mapInput("//map.minfo");
	// LoadMap();

	return;
}

// ���� ���� �޼���
void MainGame::update()
{
	/*if (vibrate) {
		input->gamePadVibrateLeft(0, 65535, 1.0);
		vibrate = false;
	}
	if (!vibrate) {
		input->gamePadVibrateRight(0, 65535, 1.0);
		vibrate = true;
	}*/

	//runner.Play(frameTime);
	
	//collisions();

	//runner.collidesWith(runner2);

	if (input->isKeyDown(VK_RIGHT)) {
		if (player.dontMoveRect[0] != 1) {
			map->MoveMap(map->getMapX() - 1, map->getMapY());
		}	
	}

	if (input->isKeyDown(VK_LEFT) && player.dontMoveRect[1] != 1) {
		map->MoveMap(map->getMapX() + 1, map->getMapY());
	}

	if (input->isKeyDown(VK_UP)) {
		if (player.dontMoveRect[2] != 1) {
			map->MoveMap(map->getMapX(), map->getMapY() + 1);
		}	
	}

	if (input->isKeyDown(VK_DOWN) && player.dontMoveRect[3] != 1) {
		map->MoveMap(map->getMapX(), map->getMapY() - 1);
	}
	
	//runner.update(frameTime);
}

// AI
void MainGame::ai()
{}

// ������, �̹��� ǥ��
void MainGame::render()
{
	graphics->spriteBegin();

	// �߰��� �̹��� ����
	//BackGround.draw();

	map->drawMap();
	player.Junk2DSprite::draw();

	graphics->spriteEnd();
}

// ����� ���� �޸𸮵� ����
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
