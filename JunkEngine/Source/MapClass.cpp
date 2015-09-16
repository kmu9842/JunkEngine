#include "..\\Headers\\MapClass.h"

Map::Map(int x, int y, Graphics* g)
{
	width = x;
	height = y;
	
	TileData.initialize(g, "..\\Resources\\tile01.png", 32, 32, 2);
	TileData.setDegrees(0);
	TileData.setTrigger(true);
	TileData.setCollisionType(Junk2DentityNS::COLLISION_TYPE::BOX);
	
	// 임시 테스트용
	for (int i = 0;i<width;i++) {
		for (int j = 0;j<height;j++) {
			mapData[i][j] = 1;
		}
	}

	for (int i = 1; i<=width; i++) {
		for (int j = 1; j<=height; j++) {
			if (mapData[i-1][j-1] == 1) {
				tiles[i-1][j-1] = TileData;
				tiles[i-1][j-1].setXY(mapX + i * 32, mapY + j * 32);
			}
		}
	}
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
			if (mapData[i][j] == 1) {
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
			if (mapData[i][j] == 1) {
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
				tiles[i][j] = TileData;
				tiles[i][j].setXY(mapX + i * 32, mapY + j * 32);
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

