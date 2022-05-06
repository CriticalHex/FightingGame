#include<SFML\Graphics.hpp>
#include "player.h"
#include"globals.h"
#include<iostream>

Player::Player(sf::Vector2f pos, bool face)
{
	position = pos;
	facing = face;
	texture.loadFromFile("Assests/frog.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	sprite.setPosition(position);
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
	window.draw(sprite);
}

void look(){

}

void Player::move() {
	if (keys[LEFT] == true){
		vx = -6;
		//std::cout << "left" << std::endl;
	}
	else if (keys[RIGHT] == true){
		vx = 6;
		//std::cout << "right" << std::endl;
	}
	else vx = 0;
	if (keys[UP] == true){
		vy = -6;
		//std::cout << "up" << std::endl;
	}
	else if (keys[DOWN] == true) {
		vy = 6;
		//std::cout << "down" << std::endl;
	}
	else vy = 0;
		
	position.x += vx;
	position.y += vy;

	sprite.setPosition(position);
}

sf::Vector2f Player::getPos() {
	return position;
}