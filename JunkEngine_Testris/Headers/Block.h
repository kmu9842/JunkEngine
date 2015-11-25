#ifndef _BLOCK_H              
#define _BLOCK_H
#define WIN32_LEAN_AND_MEAN

#include "Junk2Dentity.h"
#include "constants.h"
#include "game.h"

class block {
private:
	int shape;
	enum direction {
		right, left, up, down
	};

	int x, y;

	Junk2DEntity blocks[4];

public:
	block();
	block(int x, int y, Graphics *g);
	~block() {};

	void turnRight();
	void turnLeft();

	void moveRight();
	void moveLeft();

	void draw();
};

#endif