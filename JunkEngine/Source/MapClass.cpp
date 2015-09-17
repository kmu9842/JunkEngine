#include "..\\Headers\\MapClass.h"

Map::Map(int x, int y, Graphics* g)
{
	width = x;
	height = y;
	
	TileData.initialize(g, "..\\Resources\\tile01.png", 32, 32, 1);
	TileData.setDegrees(0);
	TileData.setTrigger(true);
	TileData.setCollisionType(Junk2DentityNS::COLLISION_TYPE::BOX);

	TileData2.initialize(g, "..\\Resources\\brick_gray0.png", 32, 32, 1);
	TileData2.setDegrees(0);
	TileData2.setTrigger(false);
	TileData2.setCollisionType(Junk2DentityNS::COLLISION_TYPE::BOX);
	
	// 임시 테스트용
	for (int i = 0;i<width;i++) {
		for (int j = 0;j<height;j++) {
			if (j == 0) {
				mapData[i][j] = 2;
			}
			else if (j == 1&& i % 3 == 0) {
				mapData[i][j] = 2;
			}
			else {
				mapData[i][j] = 1;
			}
		}
	}

	for (int i = 0; i<width; i++) {
		for (int j = 0; j<height; j++) {
			if (mapData[i][j] == 1) {
				tiles[i][j] = TileData;
			}
			if (mapData[i][j] == 2) {
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
			if (mapData[i][j] != 0) {
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

