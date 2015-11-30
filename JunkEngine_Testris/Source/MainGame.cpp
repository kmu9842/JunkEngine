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

	b[0] = new Block(graphics);
	b[1] = new Block(graphics);
	b[2] = new Block(graphics);
	b[3] = new Block(graphics);

	b[1]->setXY(b[1]->getX(), b[1]->getY() - 32);
	b[2]->setXY(b[2]->getX(), b[2]->getY() - 32*2);
	b[3]->setXY(b[3]->getX(), b[3]->getY() - 32*3);

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

	if (input->isKeyUp(VK_RIGHT) && 
		b[0]->getX() <= 32 * 10 &&
		b[1]->getX() <= 32 * 10 &&
		b[2]->getX() <= 32 * 10 &&
		b[3]->getX() <= 32 * 10) {

		for (int i = 0; i < 4; i++) {
			b[i]->moveLeft();
		}
	}

	else if (input->isKeyUp(VK_LEFT) && 
		b[0]->getX() >= 32 * 3 && 
		b[1]->getX() >= 32 * 3 && 
		b[2]->getX() >= 32 * 3 && 
		b[3]->getX() >= 32 * 3) {

		for (int i = 0; i < 4; i++) {
			b[i]->moveRight();
		}
	}

	else if (input->isKeyUp(VK_RETURN)) {
		for (cnt = 1; cnt < 19; cnt++) {
			if ((map->getTileData(cnt, (b[0]->getX() - 2) / 32) != 0 ||
				map->getTileData(cnt, (b[1]->getX() - 2) / 32) != 0 ||
				map->getTileData(cnt, (b[2]->getX() - 2) / 32) != 0 ||
				map->getTileData(cnt, (b[3]->getX() - 2) / 32) != 0)) {
				break;
			}
		}
			
		b[0]->setXY(b[0]->getX(), 32 * (cnt));
		b[1]->setXY(b[1]->getX(), 32 * (cnt-1));
		b[2]->setXY(b[2]->getX(), 32 * (cnt-2));
		b[3]->setXY(b[3]->getX(), 32 * (cnt-3));

		for (int i = 0; i < 4; i++) {
			map->setTileData((b[i]->getY() - 2) / 32, (b[i]->getX() - 2) / 32, 1);
			b[i]->setXY(32 * 7, 32 * 2);
		}
		// ��������ְ� ��ġ �������ִ� �Լ� �ߵ�
		b[1]->setXY(b[1]->getX(), b[1]->getY() - 32);
		b[2]->setXY(b[2]->getX(), b[2]->getY() - 32 * 2);
		b[3]->setXY(b[3]->getX(), b[3]->getY() - 32 * 3);
	}

	if (timeCheck > 60) {

		// ���� ��ä�� ���� �μ���
		for (int i = 1; i < 19; i++) {
			cnt = 0;
			for (int j = 1; j < 11; j++) {
				if (map->getTileData(i, j) == 1) {
					cnt++;
				}
			}

			if (cnt>=10) {
				for (int j = 1; j < 11; j++) {
					map->setTileData(i, j, 0);
				}

				for (; i > 1; i--) {
					for (int j = 1; j < 11; j++) {
						map->setTileData(i, j, map->getTileData(i - 1, j));
					}
				}
			}
		}

		timeCheck -= 60;
		std::cout << GameTime << "\n";

		if (b[0]->getY() <= 32 * 18 &&
			b[1]->getY() <= 32 * 18 &&
			b[2]->getY() <= 32 * 18 &&
			b[3]->getY() <= 32 * 18 &&
			map->getTileData(b[0]->getY() / 32, (b[0]->getX() - 2) / 32) == 0 &&
			map->getTileData(b[1]->getY() / 32, (b[1]->getX() - 2) / 32) == 0 && 
			map->getTileData(b[2]->getY() / 32, (b[2]->getX() - 2) / 32) == 0 && 
			map->getTileData(b[3]->getY() / 32, (b[3]->getX() - 2) / 32) == 0) {

			for (int i = 0; i < 4; i++) {
				b[i]->moveDown();
			}
		}

		// ���� �� ��� �� ��ϵ��� ��ġ�� ĭ �迭�� 1(true)�� ����
		else {
			for (int i = 0; i < 4; i++) {
				map->setTileData((b[i]->getY() - 2) / 32, (b[i]->getX() - 2) / 32, 1);
				// �׸��� �ٽ� ���� ���� �÷���
				b[i]->setXY(32 * 7, 32 * 2);
			}
			// ��������ְ� ��ġ �������ִ� �Լ� �ߵ�
			b[1]->setXY(b[1]->getX(), b[1]->getY() - 32);
			b[2]->setXY(b[2]->getX(), b[2]->getY() - 32 * 2);
			b[3]->setXY(b[3]->getX(), b[3]->getY() - 32 * 3);
		}
	}

	// ���� ���� üũ
	/*if (map->getTileData(1, 6) == 1) {
		MessageBox(NULL, "YOU DIE", "Game Over", MB_OK);
		DestroyWindow(hwnd);
	}*/

	// �� ĭ�� ���� ä������ ��� ��ĭ ���� //
	//////////////////////////////////////////

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

	for (int i = 0; i < 4; i++) {
		b[i]->draw();
	}
	map->drawMap();

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
