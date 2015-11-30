#include "..\\Headers\\MapClass.h"

Map::Map(int x, int y, Graphics* g)
{
	width = x;
	height = y;
	
	TileData.initialize(g, "..\\Resources\\block1.png", 30, 30, 1);
	TileData.setDegrees(0);
	TileData.setTrigger(true);
	TileData.setCollisionType(Junk2DentityNS::COLLISION_TYPE::BOX);
	
	TileData2.initialize(g, "..\\Resources\\block2.png", 30, 30, 1);
	TileData2.setDegrees(0);
	TileData2.setTrigger(false);
	TileData2.setCollisionType(Junk2DentityNS::COLLISION_TYPE::BOX);
	
	for (int i = 0;i<width;i++) {
		for (int j = 0;j<height;j++) {
			if ( i == 0 || i == width-1 || j == height-1) {
				mapData[i][j] = 1;
			}
			else {
				mapData[i][j] = 0;
			}
		}
	}

	for (int i = 0; i<width; i++) {
		for (int j = 0; j<height; j++) {
			if (mapData[i][j] == 1) {
				tiles[i][j] = TileData;
			}
			if (mapData[i][j] == 0) {
				tiles[i][j] = TileData2;
			}
			tiles[i][j].setXY(mapX + (i + 1) * 32, mapY + (j + 1) * 32);
		}
	}

	// 충돌체 등록 필요
}

Map::Map()
{
	width = 18;
	height = 12;

	for (int i = 0; i<width; i++) {
		for (int j = 0; j<height; j++) {
			mapData[i][j] = 1;
		}
	}

	for (int i = 0; i<width; i++) {
		for (int j = 0; j<height; j++) {
			if (mapData[i][j] != 0) {
				tiles[i][j] = TileData;
				tiles[i][j].setXY(mapX + i*32, mapY + j*32);
			}
		}
	}
}

Map::~Map() 
{
}

void Map::drawMap()
{
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (mapData[i][j] != 0) {
				tiles[i][j].draw();
			}
		}
	}
}

void Map::MoveMap(int x, int y)
{
	mapX = x;
	mapY = y;

	for (int i = 0; i<width; i++) {
		for (int j = 0; j<height; j++) {
			if (mapData[i][j] == 1) {
				//tiles[i][j] = TileData;
				tiles[i][j].setXY(mapX + (i+1) * 32, mapY + (j+1) * 32);
			}
		}
	}
}

void Map::placeItem()
{
}

void Map::setNpc()
{
}

void Map::setMonster()
{
}

