#include"player.h"


Player::Player(int x, int y, bool face)
{
	xpos = x;
	ypos = y;
	facing = face;
}

Player::~Player()
{
}

void Player::collide(int floorLevel) {
	if (ypos >= floorLevel) {
		vy = 0;
		ypos = floorLevel + height;
	}
}