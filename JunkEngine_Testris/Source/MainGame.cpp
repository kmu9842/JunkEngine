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

	b = new Block(graphics);

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

	if (timeCheck > 60) {
		timeCheck -= 60;
		std::cout << GameTime << "\n";

		// 맵 배열에서 값을 받아 아래가 2가 아닐 경우로 바뀔것
		if (b->getY() <= 32*18) {
			b->moveDown();
		}

		// 도착 할 경우 그 블록들이 위치한 칸 배열을 1(true)로 만듬
		else {
			
		}
	}

	// 그 칸이 전부 채워졌을 경우 한칸 비우기 //
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

// 렌더링, 이미지 표시
void MainGame::render()
{
	graphics->spriteBegin();

	// 추가할 이미지 선언
	//BackGround.draw();

	map->drawMap();
	b->draw();

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
