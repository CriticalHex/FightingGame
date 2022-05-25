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
	hitbox(position.x, position.y, width - psWidthOffset, height - psHeightOffset);
	if (attackDelay > 0) {
		xFrame += 1;
		if (xFrame > 5) { xFrame = 0; }
		attackDelay--;
	}
	else {
		xFrame = 0;
	}
	if (stun > 0) {
		stun--;
	}
	if (facing) {
		PlayerSprite.setTextureRect(sf::IntRect(0 + (width * xFrame), 0, width, height));
	}
	else {
		PlayerSprite.setTextureRect(sf::IntRect(width + (width * xFrame), 0, -width, height));
	}

	window.draw(HealthBarSprite);
	window.draw(HealthBarEmptySprite);
	window.draw(PlayerSprite);
	if (devMode == true) {
		window.draw(AttackRect);
		window.draw(pHitbox);
	}

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

void Player::move(int floorLevel) {
	if (position.y + height < floorLevel) { //floor collide
		onGround = false;
	}

	if (keys[LEFT] == true) {
		vx = -10;
	}
	else if (keys[RIGHT] == true) {
		vx = 10;
	}
	else {
		if (onGround == false) {
			vx *= 0.9;
		}
		else {
			vx = 0;
		}
	}
	if (keys[UP] == true and onGround == true) {
		vy = -20;
		onGround = false;
	}
	else if (keys[DOWN] == true and onGround == false) {
		vy = 10;
	}

	vy += gravity;

	position.y += vy;
	position.x += vx;
}

sf::Vector2f Player::getPos() { return position; }

sf::Vector2f Player::getPlayerPos() { return playerXY; }

int Player::getWidth() { return playerWH.x; }

int Player::getHeight() { return playerWH.y; }

bool Player::getPlayer() { return playerOne; };

void Player::setAttackDelay(int value) { attackDelay = value; };

int Player::getAttackDelay() { return attackDelay; };

void Player::setOnGround(bool x) { onGround = x; };

void Player::setStun(int stunAmmount) { stun = stunAmmount; };

int Player::getStun() { return stun; };

void Player::setDevMode(bool x) { devMode = x; };

bool Player::getDevMode() { return devMode; };

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
			attackDelay = 6;
			player->setStun(3);
			shoulder.x = (playerXY.x + playerWH.x);
			shoulder.y = (playerXY.y + shoulderPos);
			fist.x = (playerXY.x + playerWH.x + 25);
			fist.y = (playerXY.y + shoulderPos - reach);

			AttackRect.setSize(sf::Vector2f(25, -reach));
			AttackRect.setPosition(shoulder);
			AttackRect.setOutlineColor(sf::Color::Red);
			AttackRect.setOutlineThickness(5);
			AttackRect.setFillColor(sf::Color::Transparent);
			if (collision(shoulder, fist, player->getPlayerPos(), sf::Vector2f((player->getPlayerPos().x + player->getWidth()), player->getPlayerPos().y + player->getHeight()))) {
				player->damage(5);
				player->setVel(6, -10);
				player->setOnGround(false);

			}
		}
		else if (facing == true and direction == DOWN) {
			attackDelay = 6;
			player->setStun(3);
			shoulder.x = (playerXY.x + playerWH.x);
			shoulder.y = (playerXY.y + playerWH.y - 25);
			fist.x = (playerXY.x + playerWH.x + reach);
			fist.y = (playerXY.y + playerWH.y - 25);

			AttackRect.setSize(sf::Vector2f(reach, -25));
			AttackRect.setPosition(shoulder);
			AttackRect.setOutlineColor(sf::Color::Red);
			AttackRect.setOutlineThickness(5);
			AttackRect.setFillColor(sf::Color::Transparent);
			if (collision(shoulder, fist, player->getPlayerPos(), sf::Vector2f((player->getPlayerPos().x + player->getWidth()), player->getPlayerPos().y + player->getHeight()))) {
				player->damage(5);
				player->setVel(10, -6);
				player->setOnGround(false);
			}
		}
		else {
			attackDelay = 6;
			player->setStun(3);
			shoulder.x = (playerXY.x + playerWH.x);
			shoulder.y = (playerXY.y + shoulderPos);
			fist.x = (playerXY.x + playerWH.x + reach);
			fist.y = (playerXY.y + shoulderPos + 25);

			AttackRect.setSize(sf::Vector2f(reach, 25));
			AttackRect.setPosition(shoulder);
			AttackRect.setOutlineColor(sf::Color::Red);
			AttackRect.setOutlineThickness(5);
			AttackRect.setFillColor(sf::Color::Transparent);
			if (collision(shoulder, fist, player->getPlayerPos(), sf::Vector2f((player->getPlayerPos().x + player->getWidth()), player->getPlayerPos().y + player->getHeight()))) {
				player->damage(5);
				player->setVel(10, -6);
				player->setOnGround(false);
			}
		}
	}

	if (!facing) {
		if (facing == false and direction == UP) {
			attackDelay = 6;
			player->setStun(3);
			shoulder.x = (playerXY.x);
			shoulder.y = (playerXY.y + shoulderPos);
			fist.x = (playerXY.x - 25);
			fist.y = (playerXY.y + shoulderPos - reach);

			AttackRect.setSize(sf::Vector2f(-25, -reach));
			AttackRect.setPosition(shoulder);
			AttackRect.setOutlineColor(sf::Color::Red);
			AttackRect.setOutlineThickness(5);
			AttackRect.setFillColor(sf::Color::Transparent);
			if (collision(shoulder, fist, player->getPlayerPos(), sf::Vector2f((player->getPlayerPos().x + player->getWidth()), player->getPlayerPos().y + player->getHeight()))) {
				player->damage(5);
				player->setVel(-6, -10);
				player->setOnGround(false);
			}
		}
		else if (facing == false and direction == DOWN) {
			attackDelay = 6;
			player->setStun(3);
			shoulder.x = (playerXY.x);
			shoulder.y = (playerXY.y + playerWH.y - 25);
			fist.x = (playerXY.x - reach);
			fist.y = (playerXY.y + playerWH.y - 25);

			AttackRect.setSize(sf::Vector2f(-reach, -25));
			AttackRect.setPosition(shoulder);
			AttackRect.setOutlineColor(sf::Color::Red);
			AttackRect.setOutlineThickness(5);
			AttackRect.setFillColor(sf::Color::Transparent);
			if (collision(shoulder, fist, player->getPlayerPos(), sf::Vector2f((player->getPlayerPos().x + player->getWidth()), player->getPlayerPos().y + player->getHeight()))) {
				player->damage(5);
				player->setVel(-10, -6);
				player->setOnGround(false);
			}
		}
		else {
			player->setStun(3);
			attackDelay = 6;
			shoulder.x = (playerXY.x);
			shoulder.y = (playerXY.y + shoulderPos);
			fist.x = (playerXY.x - reach);
			fist.y = (playerXY.y + shoulderPos + 25);

			AttackRect.setSize(sf::Vector2f(reach, -25));
			AttackRect.setPosition(fist);
			AttackRect.setOutlineColor(sf::Color::Red);
			AttackRect.setOutlineThickness(5);
			AttackRect.setFillColor(sf::Color::Transparent);
			if (collision(shoulder, fist, player->getPlayerPos(), sf::Vector2f((player->getPlayerPos().x + player->getWidth()), player->getPlayerPos().y + player->getHeight()))) {
				player->damage(5);
				player->setVel(-10, -6);
				player->setOnGround(false);
			}
		}
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

void Player::setVel(float x, float y) {
	vy += y;
	vx += x;
}

void Player::hitbox(int xPos, int yPos, int w, int h) {
	if (facing) {
		pHitbox.setSize(sf::Vector2f(w, h));
		pHitbox.setPosition(xPos, yPos);
		pHitbox.setOutlineColor(sf::Color::Red);
		pHitbox.setOutlineThickness(5);
		pHitbox.setFillColor(sf::Color::Transparent);
		playerXY.x = xPos;
		playerXY.y = yPos;
		playerWH.x = w;
		playerWH.y = h;
	}
	else if (!facing) {
		pHitbox.setSize(sf::Vector2f(w, h));
		pHitbox.setPosition(xPos + psWidthOffset, yPos);
		pHitbox.setOutlineColor(sf::Color::Red);
		pHitbox.setOutlineThickness(5);
		pHitbox.setFillColor(sf::Color::Transparent);
		playerXY.x = xPos + psWidthOffset;
		playerXY.y = yPos;
		playerWH.x = w;
		playerWH.y = h;
	}

}