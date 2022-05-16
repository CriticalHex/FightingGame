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
	PlayerTexture.loadFromFile("Assets/Player/Characters/frog.png");
	PlayerSprite.setTexture(PlayerTexture);
	PlayerSprite.setTextureRect(sf::IntRect(0, 0, width, height));
	PlayerSprite.setPosition(position);

	HealthBarTexture.loadFromFile("Assets/Player/healthbar.png");
	HealthBarSprite.setTexture(HealthBarTexture);

	HealthBarEmptyTexture.loadFromFile("Assets/Player/healthbarempty.png");
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
	window.draw(AttackRect);
	AttackRect.setOutlineColor(sf::Color::Transparent);
}

void Player::look(float otherX) {
	if (otherX > position.x) {
		facing = true;
	}
	else if (otherX < position.x) {
		facing = false;
	}
}

void Player::move() {
	if (keys[LEFT] == true) {
		vx = -10;
	}
	else if (keys[RIGHT] == true) {
		vx = 10;
	}
	else vx = 0;
	if (keys[UP] == true and onGround == true) {
		vy = -20;
		onGround = false;
	}
	else if (keys[DOWN] == true and onGround == false) {
		vy = 10;
	}

	vy += gravity;

	position.x += vx;
	position.y += vy;

	
}

sf::Vector2f Player::getPos() { return position; }

int Player::getWidth() { return width; }

int Player::getHeight() { return height; }

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

void Player::quickAttack(sf::RenderWindow& window, Player* player) {
	sf::Vector2f shoulder;
	sf::Vector2f fist;
	if (facing) {
		if (facing == true and direction == UP) {
			shoulder.x = (position.x + width);
			shoulder.y = (position.y + 50);
			fist.x = (position.x + width + 25);
			fist.y = (position.y + 50 - reach);

			AttackRect.setSize(sf::Vector2f(25, -reach));
			AttackRect.setPosition(shoulder);
			AttackRect.setOutlineColor(sf::Color::Red);
			AttackRect.setOutlineThickness(5);
			AttackRect.setFillColor(sf::Color::Transparent);
		}
		else if (facing == true and direction == DOWN) {
			shoulder.x = (position.x + width);
			shoulder.y = (position.y + height - 25);
			fist.x = (position.x + width + reach);
			fist.y = (position.y + height - 25);

			AttackRect.setSize(sf::Vector2f(reach, -25));
			AttackRect.setPosition(shoulder);
			AttackRect.setOutlineColor(sf::Color::Red);
			AttackRect.setOutlineThickness(5);
			AttackRect.setFillColor(sf::Color::Transparent);
		}
		else {
			shoulder.x = (position.x + width);
			shoulder.y = (position.y + 50);
			fist.x = (position.x + width + reach);
			fist.y = (position.y + 50 + 25);

			AttackRect.setSize(sf::Vector2f(reach, 25));
			AttackRect.setPosition(shoulder);
			AttackRect.setOutlineColor(sf::Color::Red);
			AttackRect.setOutlineThickness(5);
			AttackRect.setFillColor(sf::Color::Transparent);
		}
	}

	if (!facing) {
		if (facing == false and direction == UP) {
			shoulder.x = (position.x);
			shoulder.y = (position.y + 50);
			fist.x = (position.x - 25);
			fist.y = (position.y + 50 - reach);

			AttackRect.setSize(sf::Vector2f(-25, -reach));
			AttackRect.setPosition(shoulder);
			AttackRect.setOutlineColor(sf::Color::Red);
			AttackRect.setOutlineThickness(5);
			AttackRect.setFillColor(sf::Color::Transparent);
		}
		else if (facing == false and direction == DOWN) {
			shoulder.x = (position.x);
			shoulder.y = (position.y + height - 25);
			fist.x = (position.x - reach);
			fist.y = (position.y + height - 25);

			AttackRect.setSize(sf::Vector2f(-reach, -25));
			AttackRect.setPosition(shoulder);
			AttackRect.setOutlineColor(sf::Color::Red);
			AttackRect.setOutlineThickness(5);
			AttackRect.setFillColor(sf::Color::Transparent);
		}
		else {
			shoulder.x = (position.x);
			shoulder.y = (position.y + 50);
			fist.x = (position.x - reach);
			fist.y = (position.y + 50 + 25);

			AttackRect.setSize(sf::Vector2f(reach, -25));
			AttackRect.setPosition(fist);
			AttackRect.setOutlineColor(sf::Color::Red);
			AttackRect.setOutlineThickness(5);
			AttackRect.setFillColor(sf::Color::Transparent);
		}
	}
	
	if (collision(shoulder, fist, player->getPos(), sf::Vector2f((player->getPos().x + player->getWidth()), player->getPos().y + player->getHeight()))) {
		player->damage(5);
	}
}

void Player::heavyAttack() {
	std::cout << "heavy" << std::endl;
}

void Player::block() {
	std::cout << "block" << std::endl;
}

bool Player::collision(sf::Vector2f shoulder, sf::Vector2f fist, sf::Vector2f otherPosTopLeft, sf::Vector2f otherPosBottemRight) {
	if ((((shoulder.x >= otherPosTopLeft.x) and (shoulder.x <= otherPosBottemRight.x)) and
	((shoulder.y >= otherPosTopLeft.y) and (shoulder.y <= otherPosBottemRight.y))) or
	(((fist.x >= otherPosTopLeft.x) and (fist.x <= otherPosBottemRight.x)) and
	((fist.y >= otherPosTopLeft.y) and (fist.y <= otherPosBottemRight.y)))) {
		return true;
	}
	return false;
}
