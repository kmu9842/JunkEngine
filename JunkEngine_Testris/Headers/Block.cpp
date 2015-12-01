#include "Block.h"

Block::Block(Graphics *g)
{
	// ��ϵ� �׷��� ��ü �ʱ�ȭ
	blocks = new Junk2DEntity();

	blocks->initialize(g, "..\\Resources\\block2.png", 30, 30, 1);

	// ���� �� ��ġ ��� �ʿ�
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