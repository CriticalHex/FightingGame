#pragma once

class Player
{
public:
	Player(int x, int y, bool face);
	~Player();
	void collide(int floorLevel);

private:
	enum { UP, DOWN, LEFT, RIGHT, ULEFT, URIGHT, DLEFT, DRIGHT, NONE };
	int xpos;
	int ypos;
	bool facing;
	int vx = 0;
	int vy = 0;
	int height = 200;
	int width = 200;
	bool onGround = true;
	int canAttack = true;
	int health = 200;
	int specialCharge = 0;
	int direction = NONE;
};