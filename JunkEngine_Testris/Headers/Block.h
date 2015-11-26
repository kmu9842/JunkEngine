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
		_I,   // ü�� ����
		_L,   // L ����
		_4,   // ���簢��
		_22R, // �Ʒ����� ������ 22���
		_22L, // ������ ������ 22���
		_Y    // ������ ���
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