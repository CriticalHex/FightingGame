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
	void quickAttack(sf::RenderWindow& window, Player player);
	void heavyAttack();
	void block();
	void damage(int damage);
	void healthBar();
	bool collision(sf::Vector2f shoulder, sf::Vector2f fist, sf::Vector2f otherPosTopLeft, sf::Vector2f otherPosBottemRight);
	bool keys[4] = { false, false, false, false };
	int getHealth();
	int getWidth();
	int getHeight();
	sf::Vector2f getPos();

private:
	sf::Vector2f position;
	sf::Texture PlayerTexture;
	sf::Sprite PlayerSprite;
	sf::Texture HealthBarTexture;
	sf::Sprite HealthBarSprite;
	sf::Texture HealthBarEmptyTexture;
	sf::Sprite HealthBarEmptySprite;
	bool playerOne;
	bool facing;
	float gravity = 1;
	int ticker = 0;
	int vx = 0;
	int vy = 1;
	int width = 162;
	int height = 280;
	int hbWidth = 800;
	int hbHeight = 62;
	bool onGround = true;
	int canAttack = 0;
	int maxHealth = 200;
	int health = 200;
	int specialCharge = 0;
	int direction = NONE;
	int reach = 120;
	bool attacking = false;
	sf::RectangleShape AttackRect;
	sf::RectangleShape rect;//temp
};