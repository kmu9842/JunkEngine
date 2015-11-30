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

	map = new Map(12, 20, graphics);

//	for (int i = 0; i < map->getWidth(); i++) {
//		for (int j = 0; j < map->getHeight(); j++) {
////			addEntity(map->getTiles(i, j));
//		}
//	}

	b = new Block(graphics);

	// �̹��� ������ �̸� ����
	
	// addEntity(&player);

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
	
	timeCheck += 1;

	if (timeCheck > 60) {
		timeCheck -= 60;
		std::cout << GameTime << "\n";

		// �� �迭���� ���� �޾� �Ʒ��� 2�� �ƴ� ���� �ٲ��
		if (b->getY() <= 32*18) {
			b->moveDown();
		}

		// ���� �� ��� �� ��ϵ��� ��ġ�� ĭ �迭�� 1(true)�� ����
		else {
			
		}
	}

	// �� ĭ�� ���� ä������ ��� ��ĭ ���� //
	//////////////////////////////////////////

	if (input->isKeyUp(VK_RIGHT) && b->getX() <= 32 * 10) {
		b->moveLeft();
	}

	if (input->isKeyUp(VK_LEFT) && b->getX() >= 32 * 3) {
		b->moveRight();
	}
	/*
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 12; j++) {
			std::cout << map->getTileData(i, j) << " ";
		}
		std::cout << "\n";
	}*/
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
	b->draw();

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
