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

	map = new Map(11, 20, graphics);

	for (int i = 0; i < map->getWidth(); i++) {
		for (int j = 0; j < map->getHeight(); j++) {
//			addEntity(map->getTiles(i, j));
		}
	}

	// 이미지 정보름 미리 선언
	
	// addEntity(&player);

	// mapInput("//map.minfo");
	// LoadMap();

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
	std::cout << GameTime << "\n";

	// 그 칸이 전부 채워졌을 경우 한칸 비우기
	
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

// 렌더링, 이미지 표시
void MainGame::render()
{
	graphics->spriteBegin();

	// 추가할 이미지 선언
	//BackGround.draw();

	map->drawMap();
	//b.draw();

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
