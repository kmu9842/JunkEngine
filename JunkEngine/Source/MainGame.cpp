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

	BackGround.settingTexture(graphics, "..\\Resources\\bg.png");
	
	runner.initialize(graphics, "..\\Resources\\spritesheet.png", 240, 210, 2);
	runner.setXY(GAME_WIDTH / 4, GAME_HEIGHT / 4);
	runner.setAnimation(0, 3, 0, 0.1f);
	runner.setDegrees(0);
	runner.setCollisionType(entityNS::COLLISION_TYPE::BOX);

	runner2.initialize(graphics, "..\\Resources\\spritesheet.png", 240, 210, 2);
	runner2.setXY(GAME_WIDTH / 2 + 100 , GAME_HEIGHT / 4);
	runner2.setAnimation(0, 3, 0, 0.1f);
	runner2.setDegrees(0);
	runner2.setCollisionType(entityNS::COLLISION_TYPE::BOX);

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


	if (!runner.collidesWith(runner2)) {
		if (input->isKeyDown(VK_RIGHT)) {
			runner.setX(runner.getX() + frameTime * 80.0f);
			if (runner.getX() > GAME_WIDTH) {
				runner.setX((float)-runner.getWidth() + frameTime * 80.0f);
			}
			runner.update(frameTime);
		}

		if (input->isKeyDown(VK_LEFT)) {
			runner.setX(runner.getX() - frameTime * 80.0f);
			if (runner.getX() < -runner.getWidth()) {
				runner.setX((float)GAME_WIDTH);
			}
			runner.update(frameTime);
		}

		if (input->isKeyDown(VK_UP)) {
			runner.setY(runner.getY() - frameTime * 80.0f);
			if (runner.getY() < -runner.getHeight()) {
				runner.setY((float)GAME_HEIGHT);
			}
			runner.update(frameTime);
		}

		if (input->isKeyDown(VK_DOWN)) {
			runner.setY(runner.getY() + frameTime * 80.0f);
			if (runner.getY() > GAME_HEIGHT) {
				runner.setY((float)-runner.getHeight());
			}
			runner.update(frameTime);
		}
	}
	
	runner2.update(frameTime);

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

	// 추가할 이미지 선언
	BackGround.draw();
	runner.draw();
	runner2.draw();

	graphics->spriteEnd();
}

// 예약된 비디오 메모리들 해제
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
