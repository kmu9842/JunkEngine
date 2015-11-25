#include "Block.h"

block::block(int x, int y, Graphics *g)
{
	blocks[0].initialize(g, "..\\Resources\\player.png", 14, 14, 1);
	blocks[0].setDegrees(0);
	blocks[0].setXY(x,y);
}
