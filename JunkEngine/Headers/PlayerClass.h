

#include "Junk2Dentity.h"
#include "constants.h"

class Player : public Junk2DEntity {
private:
	enum direction {
		right, left, up, down
	};

	int Hp;
	int Mp;
	int Ability[PlayerAbility];
	int GameSW[100];

	int PlayerState[5];
	//ITEM* Inventory[100];

public:
	Player();
	Player(int hp, int mp);
	Player(int hp, int mp, const char *filename, Graphics* g);
	~Player();

	// 겟셋끼들
	virtual int getHp() { return Hp; };
	virtual int getMp() { return Hp; };
	virtual int getAbility(int a) { return Ability[a]; };
	virtual int getGameSW(int a) { return GameSW[a]; };

	virtual void setHp(int Hp) { this->Hp = Hp; };
	virtual void setMp(int Mp) { this->Mp = Mp; };
	virtual void setAbility(int Num, int ab) { Ability[Num] = ab; };
	virtual void setGameSW(int Num, int sw) { GameSW[Num] = sw; };

	// 데이터 관련 함수들
	// virtual void PlayDataSave(); ?
	virtual void drawPlayer();

	// 행동 관련 함수들 
	virtual void PlayMove(int dir);
	virtual void PlayerAttack(int damage);
	virtual void PlayerStateCheck();
	//virtual void PlayerGetItem(ITEM* it);
};
