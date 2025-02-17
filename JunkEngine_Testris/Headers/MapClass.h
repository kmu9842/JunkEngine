#ifndef _MAPCLASS_H              
#define _MAPCLASS_H
#define WIN32_LEAN_AND_MEAN

#include "Junk2Dentity.h"
#include "constants.h"
#include "game.h"

class Map : Junk2DEntity {
private : 
	UINT width, height;
	int mapX,mapY;

	int mapData[MapXY][MapXY];
	Junk2DEntity tiles[MapXY][MapXY];
	Junk2DEntity TileData;
	Junk2DEntity TileData2;

public :
	Map();
	Map(int x, int y, Graphics* g);
	~Map();

	virtual int getMapX() { return mapX; };
	virtual int getMapY() { return mapY; };
	virtual int getWidth() { return width; };
	virtual int getHeight() { return height; };

	virtual Junk2DEntity* getTiles(int x, int y) { return &tiles[x][y]; };

	virtual int getTileData(int x, int y) { 
		if (x < 0 || y < 0) return 0;
		return mapData[x][y]; 
	};
	virtual void setTileData(int x, int y, int data) { 
		mapData[x][y] = data; 
	};

	virtual void drawMap();
	virtual void MoveMap(int x, int y);
	virtual void placeItem();

	virtual void setNpc();
	virtual void setMonster();
};

#endif