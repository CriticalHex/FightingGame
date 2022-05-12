#include<SFML\Graphics.hpp>
#include "player.h"
#include"globals.h"
#include<iostream>
#include<Windows.h>

using namespace std;

Player::Player(sf::Vector2f pos, bool player)
{
	position = pos;
	playerOne = player;
	PlayerTexture.loadFromFile("Assests/Player/Characters/frog.png");
	PlayerSprite.setTexture(PlayerTexture);
	PlayerSprite.setTextureRect(sf::IntRect(0, 0, width, height));
	PlayerSprite.setPosition(position);

	HealthBarTexture.loadFromFile("Assests/Player/healthbar.png");
	HealthBarSprite.setTexture(HealthBarTexture);

	HealthBarEmptyTexture.loadFromFile("Assests/Player/healthbarempty.png");
	HealthBarEmptySprite.setTexture(HealthBarEmptyTexture);

	if (!playerOne) {
		HealthBarSprite.setOrigin(hbWidth, 0);
		HealthBarSprite.setTextureRect(sf::IntRect(0, hbHeight, hbWidth, -hbHeight));
		HealthBarSprite.setPosition(1920 - hbWidth, hbHeight);
		HealthBarSprite.setRotation(180);

		HealthBarEmptySprite.setOrigin(hbWidth, 0);
		HealthBarEmptySprite.setTextureRect(sf::IntRect(0, 0, 0, hbHeight));
		HealthBarEmptySprite.setPosition(1920 - hbWidth, hbHeight);
		HealthBarEmptySprite.setRotation(180);
	}
	else {
		HealthBarEmptySprite.setTextureRect(sf::IntRect(0, 0, 0, hbHeight));
	}
}

Player::~Player()
{
}

void Player::collide(int floorLevel, sf::Vector2u windowSize) {
	if (position.y + height >= floorLevel) { //floor collide
		vy = 0;
		position.y = floorLevel - height;
		onGround = true;
	}
	if (position.x + width >= windowSize.x) {
		position.x = windowSize.x - width;
	}
	else if (position.x <= 0) {
		position.x = 0;
	}

	PlayerSprite.setPosition(position);
}

void Player::draw(sf::RenderWindow& window) {
	if (facing) {
		PlayerSprite.setTextureRect(sf::IntRect(0, 0, width, height));
	}
	if (!facing) {
		PlayerSprite.setTextureRect(sf::IntRect(width, 0, -width, height));
	}
	window.draw(HealthBarSprite);
	window.draw(HealthBarEmptySprite);
	window.draw(PlayerSprite);
}

void Player::look(float otherX){
	if (otherX > position.x) {
		facing = true;
	}
	else if (otherX < position.x) {
		facing = false;
	}
}

void Player::move() {
	if (keys[LEFT] == true){
		vx = -10;
		//std::cout << "left" << std::endl;
	}
	else if (keys[RIGHT] == true){
		vx = 10;
		//std::cout << "right" << std::endl;
	}
	else vx = 0;
	if (keys[UP] == true and onGround == true){
		vy = -20;
		onGround = false;
		//std::cout << "up" << std::endl;
	}
	else if (keys[DOWN] == true and onGround == false) {
		vy = 10;
		//std::cout << "down" << std::endl;
	}

	vy += gravity;
		
	position.x += vx;
	position.y += vy;

	
}

sf::Vector2f Player::getPos() { return position; }

void Player::determine_direction() {
	if (keys[LEFT]) {
		if (keys[UP]) {
			direction = ULEFT;
		}
		else if (keys[DOWN]) {
			direction = DLEFT;
		}
		else {
			direction = LEFT;
		}
	}
	else if (keys[RIGHT]) {
		if (keys[UP]) {
			direction = URIGHT;
		}
		else if (keys[DOWN]) {
			direction = DRIGHT;
		}
		else {
			direction = RIGHT;
		}
	}
	else if (keys[DOWN]) {
		direction = DOWN;
	}
	else if (keys[UP]) {
		direction = UP;
	}
	else {
		direction = NONE;
	}
}

void Player::damage(int damage) {
	health -= damage;
	healthBar();
}

void Player::healthBar() {
	if (playerOne) {
		HealthBarEmptySprite.setTextureRect(sf::IntRect(0, 0, maxHealth - health, hbHeight));
	}
	else {
		HealthBarEmptySprite.setTextureRect(sf::IntRect(0, hbHeight, maxHealth - health, -hbHeight));
	}
	//HealthBarEmptySprite.setTextureRect(sf::IntRect(0, 0, maxHealth - health, hbHeight));
}

int Player::getHealth() {
	return health;
}

void Player::specialAttack() {
	std::cout << "special" << std::endl;
}

void Player::quickAttack() {
	std::cout << "quick" << std::endl;
}

void Player::heavyAttack() {
	std::cout << "heavy" << std::endl;
}

void Player::block() {
	std::cout << "block" << std::endl;
}