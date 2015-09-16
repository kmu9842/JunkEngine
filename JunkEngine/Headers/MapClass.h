#ifndef _PLAYERCLASS_H              
#define _PLAYERCLASS_H
#define WIN32_LEAN_AND_MEAN

#include "Junk2Dentity.h"
#include "constants.h"

class Map : Junk2DEntity {
private : 
	UINT width, height;
	int mapX,mapY;

	int mapData[MapXY][MapXY];
	Junk2DEntity tiles[MapXY][MapXY];
	Junk2DEntity TileData;

public :
	Map();
	Map(int x, int y, Graphics* g);
	~Map();

	virtual void drawMap();
	virtual void MoveMap(int x, int y);
	virtual void placeItem();

	virtual void setNpc();
	virtual void setMonster();
};

#endif