#include "..\\Headers\\MainGame.h"

// 생성자
MainGame::MainGame()
{}

// 소멸자
MainGame::~MainGame()
{
	releaseAll();
}

// 게임 초기화
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

	// 이미지 정보름 미리 선언
	
	// addEntity(&player);

	return;
}

// 게임 루프 메세지
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

	// 일정 시간마다 블록 아래로 하강, 아래에 블록이 있을 경우 중지
	
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
		// 모양정해주고 위치 설정해주는 함수 발동
		b[1]->setXY(b[1]->getX(), b[1]->getY() - 32);
		b[2]->setXY(b[2]->getX(), b[2]->getY() - 32 * 2);
		b[3]->setXY(b[3]->getX(), b[3]->getY() - 32 * 3);
	}

	if (timeCheck > 60) {

		// 한줄 다채운 블럭들 부수기
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

		// 도착 할 경우 그 블록들이 위치한 칸 배열을 1(true)로 만듬
		else {
			for (int i = 0; i < 4; i++) {
				map->setTileData((b[i]->getY() - 2) / 32, (b[i]->getX() - 2) / 32, 1);
				// 그리고 다시 제일 위로 올려줌
				b[i]->setXY(32 * 7, 32 * 2);
			}
			// 모양정해주고 위치 설정해주는 함수 발동
			b[1]->setXY(b[1]->getX(), b[1]->getY() - 32);
			b[2]->setXY(b[2]->getX(), b[2]->getY() - 32 * 2);
			b[3]->setXY(b[3]->getX(), b[3]->getY() - 32 * 3);
		}
	}

	// 게임 오버 체크
	/*if (map->getTileData(1, 6) == 1) {
		MessageBox(NULL, "YOU DIE", "Game Over", MB_OK);
		DestroyWindow(hwnd);
	}*/

	// 그 칸이 전부 채워졌을 경우 한칸 비우기 //
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

// 렌더링, 이미지 표시
void MainGame::render()
{
	graphics->spriteBegin();

	// 추가할 이미지 선언
	//BackGround.draw();

	for (int i = 0; i < 4; i++) {
		b[i]->draw();
	}
	map->drawMap();

	graphics->spriteEnd();
}

// 예약된 비디오 메모리들 해제
void MainGame::releaseAll()
{
	Game::releaseAll();
	return;
}

// 그래픽 디바이스 리셋
void MainGame::resetAll()
{
	Game::resetAll();
	return;
}
