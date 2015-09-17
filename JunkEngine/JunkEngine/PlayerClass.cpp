#include "..\\Headers\\PlayerClass.h"

Player::Player()
{
	Hp = 0;
	Mp = 0;
	Ability[PlayerAbility] = {0,};
	GameSW[100] = {0,};
}

Player::Player(int hp, int mp) 
{
	Hp = hp;
	Mp = mp;
	Ability[PlayerAbility] = { 0, };
	GameSW[100] = { 0, };
}

Player::Player(int hp, int mp, const char *filename, Graphics* g)
{
	Hp = hp;
	Mp = mp;
	Ability[PlayerAbility] = { 0, };
	GameSW[100] = { 0, };
}

Player::~Player() {
	
}

void Player::drawPlayer()
{
}

void Player::PlayMove(int dir)
{
	// map 위치 조정
	// 플레이어가 아니라 맵의 위치가 이동해야함
}

void Player::PlayerAttack(int damage) 
{
	// ?
}

void Player::PlayerStateCheck()
{
	if (PlayerState[0] == 1) {

	}
	if (PlayerState[1] == 1) {

	}
	if (PlayerState[2] == 1) {

	}
	if (PlayerState[3] == 1) {

	}
	if (PlayerState[4] == 1) {

	}
}