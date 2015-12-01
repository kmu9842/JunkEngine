#ifndef _BLOCK_H              
#define _BLOCK_H
#define WIN32_LEAN_AND_MEAN

#include <time.h>

#include "Junk2Dentity.h"
#include "constants.h"
#include "game.h"

class Block {
private:

	int x, y;

	Junk2DEntity* blocks;

public:
	Block() {};
	Block(Graphics *g);
	~Block() {};

	int getX() { return x; };
	int getY() { return y; };

	void setXY(int x, int y) { 
		this->x = x; 
		this->y = y; 
	
		blocks->setXY(x, y);
	};

	void moveRight();
	void moveLeft();

	void moveDown();

	void draw();
};

#endif