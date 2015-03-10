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

	// 배경 텍스쳐
	if (!BGTexture.initialize(graphics, "..\\Resources\\bg.png")) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg texture"));
	}

	// 배경 이미지
	if (!BG.initialize(graphics, 0, 0, 0, &BGTexture)) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg"));
	}

	BG.setX(GAME_WIDTH*0.5f - BG.getWidth()*0.5f);
	BG.setY(GAME_HEIGHT*0.5f - BG.getHeight()*0.5f);

    return;
}

// 게임 루프 메세지
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
}

// AI
void MainGame::ai()
{}

// 충돌 처리
void MainGame::collisions()
{}

// 렌더링, 이미지 표시
void MainGame::render()
{
	graphics->spriteBegin();

	BG.draw();

	graphics->spriteEnd();
}

// 예약된 비디오 메모리 해제
void MainGame::releaseAll()
{
	BGTexture.onLostDevice();

    Game::releaseAll();
    return;
}

// 그래픽 디바이스 리셋
void MainGame::resetAll()
{
	BGTexture.onResetDevice();

    Game::resetAll();
    return;
}
