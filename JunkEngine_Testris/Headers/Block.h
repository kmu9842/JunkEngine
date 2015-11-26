#ifndef _BLOCK_H              
#define _BLOCK_H
#define WIN32_LEAN_AND_MEAN

#include "Junk2Dentity.h"
#include "constants.h"
#include "game.h"

class Block {
private:
	enum direction {
		right, left, up, down
	};
	enum shapeSet {
		_I,   // 체고 조넘
		_L,   // L 자형
		_4,   // 정사각형
		_22R, // 아래쪽이 내려간 22블록
		_22L, // 왼쪽이 내려간 22블록
		_Y    // ㅓ자형 블록
	};

	int x, y;

	Junk2DEntity* blocks[4];

public:
	Block() {};
	Block(int x, int y, Graphics *g);
	~Block() {};

	void turnRight();
	void turnLeft();

	void moveRight();
	void moveLeft();

	void draw();
};

#endif