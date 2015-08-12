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
	
	runner.initialize(graphics, "..\\Resources\\m-water001.png", 260, 264, 2);
	runner.setXY(GAME_WIDTH / 4-120, GAME_HEIGHT / 4);
	//runner.setAnimation(0, 3, 0, 0.1f);
	runner.setDegrees(0);
	runner.setScale(0.5f);
	runner.setCollisionType(Junk2DentityNS::COLLISION_TYPE::BOX);

	runner2.initialize(graphics, "..\\Resources\\m-water002.png", 260, 264, 1);
	runner2.setXY(GAME_WIDTH / 2  , GAME_HEIGHT / 4);
	runner2.setDegrees(0);
	runner2.setScale(0.5f);
	runner2.setCollisionType(Junk2DentityNS::COLLISION_TYPE::BOX); 

	runner3.initialize(graphics, "..\\Resources\\m-water002.png", 260, 264, 1);
	runner3.setXY(GAME_WIDTH / 5, GAME_HEIGHT -100);
	runner3.setDegrees(0);
	runner3.setScale(0.5f);
	runner3.setCollisionType(Junk2DentityNS::COLLISION_TYPE::BOX);


	addEntity(&runner); // 충돌 요소들이 모인 배열에 등록
	addEntity(&runner2);
	addEntity(&runner3);

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
	runner.gravityForce();

	if (input->isKeyDown(VK_RIGHT)) {
		runner.setX(runner.getX() + frameTime * 120.0f);
		if (runner.getX() > GAME_WIDTH) {
			runner.setX((float)-runner.getWidth() + frameTime * 120.0f);
		}
	}

	if (input->isKeyDown(VK_LEFT)) {
		runner.setX(runner.getX() - frameTime * 120.0f);
		if (runner.getX() < -runner.getWidth()) {
			runner.setX((float)GAME_WIDTH);
		}
	}

	if (input->isKeyDown(VK_UP)) {
		runner.setY(runner.getY() - frameTime * 120.0f);
		if (runner.getY() < -runner.getHeight()) {
			runner.setY((float)GAME_HEIGHT);
		}
	}

	if (input->isKeyDown(VK_DOWN)) {
		runner.setY(runner.getY() + frameTime * 120.0f);
		if (runner.getY() > GAME_HEIGHT) {
			runner.setY((float)-runner.getHeight());
		}
		
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
	BackGround.draw();
	runner.draw();
	runner2.draw();
	runner3.draw();

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
