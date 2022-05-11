#pragma once
#include<SFML\Graphics.hpp>
#include"globals.h"

class Player
{
public:

	Player(sf::Vector2f pos, bool face);
	~Player();
	void collide(int floorLevel, sf::Vector2u windowSize);
	void draw(sf::RenderWindow& window);
	void look(float otherX);
	void move();
	void determine_direction();
	void specialAttack();
	void quickAttack(int otherXPos, int otherYPos, int otherHealth);
	void heavyAttack();
	void block();
	void healthBar(float x);
	sf::Vector2f getPos();
	bool keys[4] = { false, false, false, false };
	int health = 200;

private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;
	bool facing;
	float gravity = 1;
	int ticker = 0;
	int vx = 0;
	int vy = 1;
	int width = 173;
	int height = 300;
	bool onGround = true;
	int canAttack = 0;
	int specialCharge = 0;
	int direction = NONE;
	int reach = 120;
	sf::RectangleShape rect;//temp
};