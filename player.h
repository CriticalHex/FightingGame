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
	void move(int floorLevel);
	void determine_direction();
	void specialAttack();
	void quickAttack(sf::RenderWindow& window, Player* player);
	void heavyAttack();
	void block();
	void damage(int damage);
	void healthBar();
	bool collision(sf::Vector2f shoulder, sf::Vector2f fist, sf::Vector2f otherPosTopLeft, sf::Vector2f otherPosBottemRight);
	bool keys[4] = { false, false, false, false };
	int getHealth();
	int getWidth();
	int getHeight();
	int getStun();
	int getAttackDelay();
	void setAttackDelay(int value);
	bool getPlayer();
	bool getDevMode();
	sf::Vector2f getPlayerPos();
	sf::Vector2f getPos();
	void setVel(float x, float y);
	void checkOnGround();
	void setOnGround(bool x);
	void setStun(int stunAmmount);
	void hitbox(int xPos, int yPos, int width, int height);
	void setDevMode(bool x);

private:
	sf::Vector2f position;
	sf::Vector2f playerXY;
	sf::Vector2f playerWH;
	sf::Texture PlayerTexture;
	sf::Sprite PlayerSprite;
	sf::Texture HealthBarTexture;
	sf::Sprite HealthBarSprite;
	sf::Texture HealthBarEmptyTexture;
	sf::Sprite HealthBarEmptySprite;
	bool playerOne;
	bool facing = true;
	float gravity = 1;
	int ticker = 0;
	int xFrame = 0;
	int yFrame = 0;
	float vx = 0;
	float vy = 1;
	int psWidthOffset = 75;
	int psHeightOffset = 0;
	int width = 237;
	int height = 297;
	int hbWidth = 800;
	int hbHeight = 62;
	bool onGround = true;
	int attackDelay = 0;
	int maxHealth = 800;
	int health = 800;
	int specialCharge = 0;
	int direction = NONE;
	int reach = 120;
	bool attacking = false;
	int shoulderPos = 75;
	int stun = 0;
	bool devMode = false;
	sf::RectangleShape AttackRect;
	sf::RectangleShape pHitbox;
};