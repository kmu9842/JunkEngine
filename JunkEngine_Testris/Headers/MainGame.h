#ifndef _MAINGAME_H             
#define _MAINGAME_H             
#define WIN32_LEAN_AND_MEAN

#include "game.h"

// 메인 게임 클래스, Game클래스로 부터 상속 받음
class MainGame : public Game
{
private:

	// 게임 요소들
	Block* b[4];
	Map* map;

	float timeCheck = 0;

    // 변수
	bool vibrate = true;
	int cnt = 0;
	int blocktag = 0;
	int dir = 1;

public:
	MainGame();
    virtual ~MainGame();

    // 게임 기본 구성 함수들
    void initialize(HWND hwnd);
    void update();      // Game 클래스로부터 반드시 오버라이딩 해야하는 순수 가상함수
    void ai();          // "
    void render();      // "
    void releaseAll();
    void resetAll();
	void dirTetrisBlock();

	void SetTetrisBlock();

};

#endif
