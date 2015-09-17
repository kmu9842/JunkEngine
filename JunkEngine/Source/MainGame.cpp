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

	// 이미지 정보름 미리 선언
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

	if (input->isKeyUp(VK_RIGHT) && player.dontMoveRect[0] != 1) {
		//runner.setX(runner.getX() + frameTime * 120.0f);
		map->MoveMap(map->getMapX()-32,map->getMapY());
		//runner.setDegrees(45);
	}

	if (input->isKeyUp(VK_LEFT) && player.dontMoveRect[1] != 1) {
		map->MoveMap(map->getMapX() + 32, map->getMapY());
	}

	if (input->isKeyUp(VK_UP) && player.dontMoveRect[2] != 1) {
		map->MoveMap(map->getMapX(), map->getMapY() + 32);
	}

	if (input->isKeyUp(VK_DOWN) && player.dontMoveRect[3] != 1) {
		map->MoveMap(map->getMapX(), map->getMapY() - 32);
	}
	
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
	player.Junk2DSprite::draw();

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
