#ifndef _BLOCK_H              
#define _BLOCK_H
#define WIN32_LEAN_AND_MEAN

#include <time.h>

#include "Junk2Dentity.h"
#include "constants.h"
#include "game.h"

class Block {
private:
	direction thisDir;
	shapeSet thisShape;

	int x, y;

	Junk2DEntity* blocks[4];

public:
	Block() {};
	Block(Graphics *g);
	~Block() {};

	int getX() { return x; };
	int getY() { return y; };

	void setXY(int x, int y) { 
		this->x = x; 
		this->y = y; 
	
		blocks[0]->setXY(x, y);
		blocks[1]->setXY(x, y);
		blocks[2]->setXY(x, y);
		blocks[3]->setXY(x, y);
	};

	void turnRight();
	void turnLeft();

	void moveRight();
	void moveLeft();

	void moveDown();

	void draw();
};

#endif