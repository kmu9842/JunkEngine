#include "Block.h"

Block::Block(Graphics *g)
{
	// 블록들 그래픽 객체 초기화
	blocks = new Junk2DEntity();

	blocks->initialize(g, "..\\Resources\\block2.png", 30, 30, 1);

	// 차후 블럭 위치 계산 필요
	x = 32*7;
	y = 32*2;

	blocks->setXY(x, y);
}

void Block::moveLeft()
{
	x -= 32;

	blocks->setX(blocks->getX() - 32);
	
}

void Block::moveRight()
{
	x += 32;

	blocks->setX(blocks->getX() + 32);
	
}

void Block::moveDown()
{
	y += 32;

	blocks->setY(blocks->getY() + 32);
	
}


void Block::draw() {
	blocks->draw();
	
}