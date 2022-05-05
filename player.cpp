#include<SFML\Graphics.hpp>
#include "player.h"
#include"globals.h"

Player::Player(sf::Vector2f pos, bool face)
{
	position = pos;
	facing = face;
	texture.loadFromFile("Assests/frog.png");
	rect.setPosition(position);
	rect.setFillColor(sf::Color::Red);
	rect.setSize(sf::Vector2f(width, height));
}

Player::~Player()
{
}

void Player::collide(int floorLevel, sf::Vector2u windowSize) {
	if (position.y + height >= floorLevel) {
		vy = 0;
		position.y = floorLevel - height;
	}
	if (position.x + width >= windowSize.x) {
		position.x = windowSize.x - width;
	}
	else if (position.x <= 0) {
		position.x = 0;
	}
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(rect);
}


void Player::move(){
	if (keys[LEFT] == true)
        vx = -3;

    if (keys[RIGHT] == true)
        vx = 3;

    if (keys[UP] == true)
        vy = -3;

    if (keys[DOWN] == true)
        vy = 3;

	position.x += vx;
	position.y += vy;
}