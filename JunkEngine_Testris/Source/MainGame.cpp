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

	map = new Map(11, 20, graphics);

	for (int i = 0; i < map->getWidth(); i++) {
		for (int j = 0; j < map->getHeight(); j++) {
//			addEntity(map->getTiles(i, j));
		}
	}

	// �̹��� ������ �̸� ����
	
	// addEntity(&player);

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

	// ���� �ð����� ��� �Ʒ��� �ϰ�, �Ʒ��� ����� ���� ��� ����
	std::cout << GameTime << "\n";

	// �� ĭ�� ���� ä������ ��� ��ĭ ����
	
	if (input->isKeyUp(VK_RIGHT)) {
		//b.moveLeft();
	}

	if (input->isKeyUp(VK_LEFT)) {
		//b.moveRight();
	}


	std::cout << "";
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
	//b.draw();

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
