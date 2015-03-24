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

	BackGround.settingTexture(graphics,"..\\Resources\\bg.png");
	if (!runnerTexture.initialize(graphics, "..\\Resources\\spritesheet.png")) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg texture"));
	}
	if (!runner.initialize(graphics, 240, 210, 2, &runnerTexture)) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg"));
	}

	runner.setX(GAME_WIDTH/4);
	runner.setY(GAME_HEIGHT / 4);

	runner.setFrames(0,3);
	runner.setCurrentFrame(0);
	runner.setFrameDelay(0.1f);
	runner.setDegrees(0);

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

	runner.update(frameTime);
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

	BackGround.draw();
	runner.draw();

	graphics->spriteEnd();
}

// 예약된 비디오 메모리 해제
void MainGame::releaseAll()
{
	BackGround.onLostDevice();

    Game::releaseAll();
    return;
}

// 그래픽 디바이스 리셋
void MainGame::resetAll()
{
	BackGround.onResetDevice();

    Game::resetAll();
    return;
}
