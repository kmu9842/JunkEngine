#include "..\\Headers\\MainGame.h"

// ������
MainGame::MainGame()
{}

// �Ҹ���
MainGame::~MainGame()
{
	releaseAll();
}
// �� �����
void MainGame::SetTetrisBlock() {
	srand((int)time(NULL));
	blocktag = rand() % 7;

	if (blocktag == 0) {
		b[0]->setXY(b[0]->getX(), b[0]->getY());
		b[1]->setXY(b[0]->getX(), b[0]->getY() - 32);
		b[2]->setXY(b[0]->getX(), b[0]->getY() - 32 * 2);
		b[3]->setXY(b[0]->getX(), b[0]->getY() - 32 * 3);
	}
	else if (blocktag == 1) {
		b[0]->setXY(b[0]->getX(), b[0]->getY());
		b[1]->setXY(b[0]->getX(), b[0]->getY() - 32);
		b[2]->setXY(b[0]->getX() - 32, b[0]->getY() - 32);
		b[3]->setXY(b[0]->getX() - 32, b[0]->getY() - 32 * 2);
	}
	else if (blocktag == 2) {
		b[0]->setXY(b[0]->getX(), b[0]->getY());
		b[1]->setXY(b[0]->getX(), b[0]->getY() - 32);
		b[2]->setXY(b[0]->getX() + 32, b[0]->getY() - 32);
		b[3]->setXY(b[0]->getX() + 32, b[0]->getY() - 32 * 2);
	}
	else if (blocktag == 3) {
		b[0]->setXY(b[0]->getX(), b[0]->getY());
		b[1]->setXY(b[0]->getX()-32, b[0]->getY());
		b[2]->setXY(b[0]->getX()+32, b[0]->getY());
		b[3]->setXY(b[0]->getX(), b[0]->getY() - 32);
	}
	else if (blocktag == 4) {
		b[0]->setXY(b[0]->getX(), b[0]->getY());
		b[1]->setXY(b[0]->getX() - 32, b[0]->getY());
		b[2]->setXY(b[0]->getX() - 32, b[0]->getY() - 32);
		b[3]->setXY(b[0]->getX(), b[0]->getY() - 32);
	}
	else if (blocktag == 5) {
		b[0]->setXY(b[0]->getX(), b[0]->getY());
		b[1]->setXY(b[0]->getX() + 32, b[0]->getY());
		b[2]->setXY(b[0]->getX(), b[0]->getY() - 32 );
		b[3]->setXY(b[0]->getX(), b[0]->getY() - 32 * 2);
	}
	else if (blocktag == 6) {
		b[0]->setXY(b[0]->getX(), b[0]->getY());
		b[1]->setXY(b[0]->getX() - 32, b[0]->getY());
		b[2]->setXY(b[0]->getX(), b[0]->getY() - 32);
		b[3]->setXY(b[0]->getX(), b[0]->getY() - 32 * 2);
	}
}

// �� ������
void MainGame::dirTetrisBlock() {
	if (blocktag == 0) {
		switch (dir) {
		case 1:
			if (map->getTileData((b[0]->getY() / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData((b[0]->getY() / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0 &&
				map->getTileData((b[0]->getY() / 32) - 1, ((b[0]->getX() - 64) / 32)) == 0 &&
				map->getTileData((b[0]->getY() / 32) - 1, ((b[0]->getX() - 96) / 32)) == 0
				) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX() - 32, b[0]->getY());
				b[2]->setXY(b[0]->getX() - 32 * 2, b[0]->getY());
				b[3]->setXY(b[0]->getX() - 32 * 3, b[0]->getY());
			}
			dir++;
			break;
		case 2:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, (b[0]->getX() / 32) - 1) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, (b[0]->getX() / 32) - 1) == 0 &&
				map->getTileData(((b[0]->getY() - 64) / 32) - 1, (b[0]->getX() / 32) - 1) == 0 &&
				map->getTileData(((b[0]->getY() - 96) / 32) - 1, (b[0]->getX() / 32) - 1) == 0) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX(), b[0]->getY() - 32);
				b[2]->setXY(b[0]->getX(), b[0]->getY() - 32 * 2);
				b[3]->setXY(b[0]->getX(), b[0]->getY() - 32 * 3);
			}
			dir++;
			break;
		case 3:
			if (map->getTileData((b[0]->getY() / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData((b[0]->getY() / 32) - 1, ((b[0]->getX() + 32) / 32)) == 0 &&
				map->getTileData((b[0]->getY() / 32) - 1, ((b[0]->getX() + 64) / 32)) == 0 &&
				map->getTileData((b[0]->getY() / 32) - 1, ((b[0]->getX() + 96) / 32)) == 0) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX() + 32, b[0]->getY());
				b[2]->setXY(b[0]->getX() + 32 * 2, b[0]->getY());
				b[3]->setXY(b[0]->getX() + 32 * 3, b[0]->getY());
			}
			dir++;
			break;
		case 4:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, (b[0]->getX() / 32) - 1) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, (b[0]->getX() / 32) - 1) == 0 &&
				map->getTileData(((b[0]->getY() + 64) / 32) - 1, (b[0]->getX() / 32) - 1) == 0 &&
				map->getTileData(((b[0]->getY() + 96) / 32) - 1, (b[0]->getX() / 32) - 1) == 0) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX(), b[0]->getY() + 32);
				b[2]->setXY(b[0]->getX(), b[0]->getY() + 32 * 2);
				b[3]->setXY(b[0]->getX(), b[0]->getY() + 32 * 3);
			}
			dir=1;
			break;
		}
	}
	else if (blocktag == 1) {
		switch (dir) {

		case 1:
			if (map->getTileData(((b[0]->getY() ) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() ) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX() - 64) / 32)) == 0
				) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX() - 32, b[0]->getY());
				b[2]->setXY(b[0]->getX() - 32, b[0]->getY() + 32);
				b[3]->setXY(b[0]->getX() - 64, b[0]->getY() + 32);
			}
			dir++;
			break;
		case 2:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX() ) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 64) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX(), b[0]->getY() - 32);
				b[2]->setXY(b[0]->getX() - 32, b[0]->getY() - 32);
				b[3]->setXY(b[0]->getX() - 32, b[0]->getY() - 32 * 2);
			}
			dir++;
			break;
		case 3:
			if (map->getTileData((b[0]->getY() / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX() + 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX() + 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX() + 64) / 32)) == 0) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX() + 32, b[0]->getY());
				b[2]->setXY(b[0]->getX() + 32, b[0]->getY() - 32);
				b[3]->setXY(b[0]->getX() + 64, b[0]->getY() - 32);
			}
			dir++;
			break;
		case 4:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 64) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX(), b[0]->getY() - 32);
				b[2]->setXY(b[0]->getX() - 32, b[0]->getY() - 32);
				b[3]->setXY(b[0]->getX() - 32, b[0]->getY() - 32 * 2);
			}
			dir = 1;
			break;
		}
	}
	else if (blocktag == 2) {
		switch (dir) {

		case 1:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX() - 64) / 32)) == 0
				) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX() - 32, b[0]->getY());
				b[2]->setXY(b[0]->getX() - 32, b[0]->getY() - 32);
				b[3]->setXY(b[0]->getX() - 64, b[0]->getY() - 32);
			}
			dir++;
			break;
		case 2:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX() + 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 64) / 32) - 1, ((b[0]->getX() + 32) / 32)) == 0) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX(), b[0]->getY() - 32);
				b[2]->setXY(b[0]->getX() + 32, b[0]->getY() - 32);
				b[3]->setXY(b[0]->getX() + 32, b[0]->getY() - 32 * 2);
			}
			dir++;
			break;
		case 3:
			if (map->getTileData((b[0]->getY() / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX() + 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX() + 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX() + 64) / 32)) == 0) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX() + 32, b[0]->getY());
				b[2]->setXY(b[0]->getX() + 32, b[0]->getY() + 32);
				b[3]->setXY(b[0]->getX() + 64, b[0]->getY() + 32);
			}
			dir++;
			break;
		case 4:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX() + 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 64) / 32) - 1, ((b[0]->getX() + 32) / 32)) == 0) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX(), b[0]->getY() - 32);
				b[2]->setXY(b[0]->getX() + 32, b[0]->getY() - 32);
				b[3]->setXY(b[0]->getX() + 32, b[0]->getY() - 32 * 2);
			}
			dir = 1;
			break;
		}
	}
	else if (blocktag == 3) {
		switch (dir) {

		case 1:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX()) / 32)) == 0
				) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX(), b[0]->getY() + 32);
				b[2]->setXY(b[0]->getX() - 32, b[0]->getY());
				b[3]->setXY(b[0]->getX(), b[0]->getY() - 32);
			}
			dir++;
			break;
		case 2:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX() + 32) / 32)) == 0) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX() - 32, b[0]->getY());
				b[2]->setXY(b[0]->getX() + 32, b[0]->getY());
				b[3]->setXY(b[0]->getX(), b[0]->getY() - 32);
			}
			dir++;
			break;
		case 3:
			if (map->getTileData((b[0]->getY() / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX() + 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX()) / 32)) == 0) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX() + 32, b[0]->getY());
				b[2]->setXY(b[0]->getX(), b[0]->getY() + 32);
				b[3]->setXY(b[0]->getX(), b[0]->getY() - 32);
			}
			dir++;
			break;
		case 4:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX() + 32) / 32)) == 0) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX() - 32, b[0]->getY());
				b[2]->setXY(b[0]->getX() + 32, b[0]->getY());
				b[3]->setXY(b[0]->getX(), b[0]->getY() + 32);
			}
			dir = 1;
			break;
		}
	}
	else if (blocktag == 5) {
		switch (dir) {

		case 1:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX() ) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX() - 64) / 32)) == 0
				) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX() , b[0]->getY() + 32);
				b[2]->setXY(b[0]->getX() - 32, b[0]->getY() + 32);
				b[3]->setXY(b[0]->getX() - 64, b[0]->getY() + 32);
			}
			dir++;
			break;
		case 2:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX() - 64) / 32)) == 0) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX() + 32, b[0]->getY());
				b[2]->setXY(b[0]->getX(), b[0]->getY() - 32);
				b[3]->setXY(b[0]->getX(), b[0]->getY() - 32 * 2);
			}
			dir++;
			break;
		case 3:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX() - 64) / 32)) == 0
				) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX(), b[0]->getY() - 32);
				b[2]->setXY(b[0]->getX() + 32, b[0]->getY() - 32);
				b[3]->setXY(b[0]->getX() + 64, b[0]->getY() - 32);
			}
			dir++;
			break;
		case 4:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX() + 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX() + 64) / 32)) == 0) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX() + 32, b[0]->getY());
				b[2]->setXY(b[0]->getX() + 32, b[0]->getY() + 32);
				b[3]->setXY(b[0]->getX() + 32, b[0]->getY() + 32 * 2);
			}
			dir = 1;
			break;
		}
	}
	else if (blocktag == 6) {
		switch (dir) {

		case 1:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX() - 64) / 32)) == 0
				) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX(), b[0]->getY() - 32);
				b[2]->setXY(b[0]->getX() - 32, b[0]->getY() - 32);
				b[3]->setXY(b[0]->getX() - 64, b[0]->getY() - 32);
			}
			dir++;
			break;
		case 2:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX() - 64) / 32)) == 0) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX() - 32, b[0]->getY());
				b[2]->setXY(b[0]->getX(), b[0]->getY() - 32);
				b[3]->setXY(b[0]->getX(), b[0]->getY() - 32 * 2);
			}
			dir++;
			break;
		case 3:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX() - 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() - 32) / 32) - 1, ((b[0]->getX() - 64) / 32)) == 0
				) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX(), b[0]->getY() + 32);
				b[2]->setXY(b[0]->getX() + 32, b[0]->getY() + 32);
				b[3]->setXY(b[0]->getX() + 64, b[0]->getY() + 32);
			}
			dir++;
			break;
		case 4:
			if (map->getTileData(((b[0]->getY()) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX()) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX() + 32) / 32)) == 0 &&
				map->getTileData(((b[0]->getY() + 32) / 32) - 1, ((b[0]->getX() + 64) / 32)) == 0) {

				b[0]->setXY(b[0]->getX(), b[0]->getY());
				b[1]->setXY(b[0]->getX() - 32, b[0]->getY());
				b[2]->setXY(b[0]->getX() - 32, b[0]->getY() + 32);
				b[3]->setXY(b[0]->getX() - 32, b[0]->getY() + 32 * 2);
			}
			dir = 1;
			break;
		}
	}
}

// ���� �ʱ�ȭ
void MainGame::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	map = new Map(12, 20, graphics);

	b[0] = new Block(graphics);
	b[1] = new Block(graphics);
	b[2] = new Block(graphics);
	b[3] = new Block(graphics);

	SetTetrisBlock();
	// �̹��� ������ �̸� ����
	
	// addEntity(&player);

	return;
}

// ���� ���� �޼���
void MainGame::update()
{
	/*if (vibrate) {
		input->gamePadVibrateLeft(0, 65535, 1.0);
		vibrate = false;
	}
	if (!vibrate) {
		input->gamePadVibrateRight(0, 65535, 1.0);
		vibrate = true;
	}*/

	//runner.Play(frameTime);
	
	//collisions();

	//runner.collidesWith(runner2);	

	// ���� �ð����� ��� �Ʒ��� �ϰ�, �Ʒ��� ����� ���� ��� ����
	
 	timeCheck += 1;

	if (input->isKeyUp(VK_RIGHT) && 
		map->getTileData((b[0]->getY() / 32) - 1, (b[0]->getX()) / 32) == 0 &&
		map->getTileData((b[1]->getY() / 32) - 1, (b[1]->getX()) / 32) == 0 &&
		map->getTileData((b[2]->getY() / 32) - 1, (b[2]->getX()) / 32) == 0 &&
		map->getTileData((b[3]->getY() / 32) - 1, (b[3]->getX()) / 32) == 0) {

		for (int i = 0; i < 4; i++) {
			b[i]->moveRight();
		}
	}

	else if (input->isKeyUp(VK_LEFT) &&
		map->getTileData((b[0]->getY() / 32) - 1, (b[0]->getX() / 32)-2) == 0 &&
		map->getTileData((b[1]->getY() / 32) - 1, (b[1]->getX() / 32)-2) == 0 &&
		map->getTileData((b[2]->getY() / 32) - 1, (b[2]->getX() / 32)-2) == 0 &&
		map->getTileData((b[3]->getY() / 32) - 1, (b[3]->getX() / 32)-2) == 0) {

		for (int i = 0; i < 4; i++) {
			b[i]->moveLeft();
		}
	}

	if (input->isKeyUp(VK_UP) &&
		b[0]->getX() <= 32 * 10 &&
		b[1]->getX() <= 32 * 10 &&
		b[2]->getX() <= 32 * 10 &&
		b[3]->getX() <= 32 * 10) {

		dirTetrisBlock();
	}

	else if (input->isKeyUp(VK_SPACE)) {
		for (;;) {
			if (b[0]->getY() <= 32 * 18 &&
				b[1]->getY() <= 32 * 18 &&
				b[2]->getY() <= 32 * 18 &&
				b[3]->getY() <= 32 * 18 &&
				map->getTileData(b[0]->getY() / 32, (b[0]->getX() - 2) / 32) == 0 &&
				map->getTileData(b[1]->getY() / 32, (b[1]->getX() - 2) / 32) == 0 &&
				map->getTileData(b[2]->getY() / 32, (b[2]->getX() - 2) / 32) == 0 &&
				map->getTileData(b[3]->getY() / 32, (b[3]->getX() - 2) / 32) == 0) {
				for (int i = 0; i < 4; i++) {
					b[i]->moveDown();
				}
			}
			else {
				break;
			}
		}

		/*for (int i = 0; i < 4; i++) {
			map->setTileData((b[i]->getY() - 2) / 32, (b[i]->getX() - 2) / 32, 1);
			b[i]->setXY(32 * 7, 32 * 2);
		}

		SetTetrisBlock();*/
	}

	// ���� ��ä�� ���� �μ���
	for (int i = 1; i < 19; i++) {
		cnt = 0;
		for (int j = 1; j < 11; j++) {
			if (map->getTileData(i, j) == 1) {
				cnt++;
			}
		}

		if (cnt >= 10) {
			for (int j = 1; j < 11; j++) {
				map->setTileData(i, j, 0);
			}

			for (; i > 1; i--) {
				for (int j = 1; j < 11; j++) {
					map->setTileData(i, j, map->getTileData(i - 1, j));
				}
			}
		}
	}

	if (timeCheck > 60) {

		timeCheck -= 60;
		std::cout << GameTime << "\n";

		if (b[0]->getY() <= 32 * 18 &&
			b[1]->getY() <= 32 * 18 &&
			b[2]->getY() <= 32 * 18 &&
			b[3]->getY() <= 32 * 18 &&
			map->getTileData(b[0]->getY() / 32, (b[0]->getX() - 2) / 32) == 0 &&
			map->getTileData(b[1]->getY() / 32, (b[1]->getX() - 2) / 32) == 0 &&
			map->getTileData(b[2]->getY() / 32, (b[2]->getX() - 2) / 32) == 0 &&
			map->getTileData(b[3]->getY() / 32, (b[3]->getX() - 2) / 32) == 0) {

			for (int i = 0; i < 4; i++) {
				b[i]->moveDown();
			}
		}

		// ���� �� ��� �� ��ϵ��� ��ġ�� ĭ �迭�� 1(true)�� ����
		else {
			for (int i = 0; i < 4; i++) {
				map->setTileData((b[i]->getY() - 2) / 32, (b[i]->getX() - 2) / 32, 1);
				// �׸��� �ٽ� ���� ���� �÷���
				b[i]->setXY(32 * 7, 32 * 2);
			}
			// ��������ְ� ��ġ �������ִ� �Լ� �ߵ�
			SetTetrisBlock();
		}
		
		
	}

	// ���� ���� üũ
	if (map->getTileData(1, 6) == 1) {
		MessageBox(NULL, "Game Over", "Game Over", MB_OK);
		DestroyWindow(hwnd);
	}

	/*
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 12; j++) {
			std::cout << map->getTileData(i, j) << " ";
		}
		std::cout << "\n";
	}*/
	//runner.update(frameTime);

}

// AI
void MainGame::ai()
{}

// ������, �̹��� ǥ��
void MainGame::render()
{
	graphics->spriteBegin();

	// �߰��� �̹��� ����
	//BackGround.draw();

	for (int i = 0; i < 4; i++) {
		b[i]->draw();
	}
	map->drawMap();

	graphics->spriteEnd();
}

// ����� ���� �޸𸮵� ����
void MainGame::releaseAll()
{
	Game::releaseAll();
	return;
}

// �׷��� ����̽� ����
void MainGame::resetAll()
{
	Game::resetAll();
	return;
}
