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
	void quickAttack(sf::RenderWindow& window, sf::Vector2f otherPosTopLeft, sf::Vector2f otherPosBottemRight);
	void heavyAttack();
	void block();
	void collision(sf::Vector2f shoulder, sf::Vector2f fist, sf::Vector2f otherPosTopLeft, sf::Vector2f otherPosBottemRight);
	void healthBar(float x);
	sf::Vector2f getPos();
	int getWidth();
	int getHeight();
	bool keys[4] = { false, false, false, false };

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
	int reach = 120;
	bool onGround = true;
	int canAttack = 0;
	int health = 200;
	int specialCharge = 0;
	int direction = NONE;
	sf::RectangleShape AttackRect;
};