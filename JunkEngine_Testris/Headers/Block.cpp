#include "Block.h"

Block::Block(Graphics *g)
{
	srand((int)time(NULL));

	// ��ϵ� �׷��� ��ü �ʱ�ȭ
	blocks[0] = new Junk2DEntity();
	blocks[1] = new Junk2DEntity();
	blocks[2] = new Junk2DEntity();
	blocks[3] = new Junk2DEntity();

	blocks[0]->initialize(g, "..\\Resources\\block2.png", 30, 30, 1);
	blocks[1]->initialize(g, "..\\Resources\\block2.png", 30, 30, 1);
	blocks[2]->initialize(g, "..\\Resources\\block2.png", 30, 30, 1);
	blocks[3]->initialize(g, "..\\Resources\\block2.png", 30, 30, 1);

	// ���� �� ��ġ ��� �ʿ�
	x = 32*7;
	y = 32*2;

	blocks[0]->setXY(x, y);
	blocks[1]->setXY(x, y);
	blocks[2]->setXY(x, y);
	blocks[3]->setXY(x, y);

	thisDir = direction::up;

	// ���� ������ ��� ����
}

void Block::moveRight()
{
	x -= 32;

	for (int i = 0; i < 4; i++) {
		blocks[i]->setX(blocks[i]->getX() - 32);
	}
}

void Block::moveLeft()
{
	x += 32;

	for (int i = 0; i < 4; i++) {
		blocks[i]->setX(blocks[i]->getX() + 32);
	}
}

void Block::moveDown()
{
	y += 32;

	for (int i = 0; i < 4; i++) {
		blocks[i]->setY(blocks[i]->getY() + 32);
	}
}


void Block::draw() {
	for (int i = 0; i < 4; i++) {
		blocks[i]->draw();
	}
}