#include <iostream>
#include<SFML\Graphics.hpp>
//#include<SFML\Network.hpp>
#include<vector>
#include<ctime>
#include"player.h"
#include"globals.h"
#include"timer.h"

using namespace std;

bool menuLoop(sf::RenderWindow& window, int winX, int winY);

void gameLoop(sf::RenderWindow& window, int winX, int winY);

void gameEventLoop(sf::RenderWindow& window, vector<Player*>& players);

void gameOverLoop(sf::RenderWindow& window, int winX, int winY);

void gameOverEventLoop(sf::RenderWindow& window, vector<Player*>& players);

int main()
{
	cout << "we ball.\n";

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "FIGHT!", sf::Style::Fullscreen);
	window.setFramerateLimit(60);
	int winX = window.getSize().x;
	int winY = window.getSize().y;

	if (menuLoop(ref(window), winX, winY)) {
		gameLoop(ref(window), winX, winY);
	}
	
}

bool menuLoop(sf::RenderWindow& window, int winX, int winY) {
	bool inMenu = true;

	sf::Font font;
	font.loadFromFile("Assets/Font/cryptic.otf");

	//stuff to render
	
	//quit box
	sf::Vector2f quitPos((winX / 2) - 300, 800);
	sf::RectangleShape quitBox(sf::Vector2f(600, 200));
	quitBox.setPosition(quitPos);
	quitBox.setFillColor(sf::Color::Cyan);

	sf::Text quitText;
	quitText.setFont(font);
	quitText.setString("QUIT");
	quitText.setCharacterSize(180);
	quitText.setPosition(quitPos.x + 10, quitPos.y - 25);
	quitText.setFillColor(sf::Color::Black);

	//play box
	sf::Vector2f playPos((winX / 2) - 300, 200);
	sf::RectangleShape playBox(sf::Vector2f(600, 200));
	playBox.setPosition(playPos);
	playBox.setFillColor(sf::Color::Cyan);

	sf::Text playText;
	playText.setFont(font);
	playText.setString("PLAY");
	playText.setCharacterSize(180);
	playText.setPosition(playPos.x + 10, playPos.y - 25);
	playText.setFillColor(sf::Color::Black);

	while (inMenu) {
		sf::Event event;
		sf::Vector2f mousePos;

		while (window.pollEvent(event))
		{

			// Close window: exit
			if (event.type == sf::Event::Closed) {
				inMenu = false;
				window.close();
				return false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) { //press lcontrol: exit
				inMenu = false;
				window.close();
				return false;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				mousePos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				if (mousePos.x > quitBox.getPosition().x and mousePos.y > quitBox.getPosition().y and mousePos.x < quitBox.getPosition().x + quitBox.getSize().x and mousePos.y < quitBox.getPosition().y + quitBox.getSize().y) {
					inMenu = false;
					return false;
				}
				else if (mousePos.x > playBox.getPosition().x and mousePos.y > playBox.getPosition().y and mousePos.x < playBox.getPosition().x + playBox.getSize().x and mousePos.y < playBox.getPosition().y + playBox.getSize().y) {
					inMenu = false;
					return true;
				}
			}
		}

		//render
		window.clear(sf::Color(0,25,25));
		window.draw(playBox);
		window.draw(playText);
		window.draw(quitBox);
		window.draw(quitText);
		window.display();

	}

}

void gameLoop(sf::RenderWindow& window, int winX, int winY) {

	//timer
	Timer timer(winX);

	//bg
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Assets/Background/background.png");
	sf::Sprite backgroundSprite(backgroundTexture);

	//player initialization
	vector<Player*> players;
	players.push_back(new Player(sf::Vector2f(150, 600), true));
	players.push_back(new Player(sf::Vector2f(winX - 300, 600), false));

	//floor variables
	int floorY = 900;
	sf::Texture floorTexture;
	floorTexture.loadFromFile("Assets/Background/floor.png");
	sf::Sprite floorSprite(floorTexture);
	floorSprite.setPosition(0, floorY - 100);

	while (window.isOpen()) {

		gameEventLoop(ref(window), ref(players));

		for (auto& it : players) {
			if (it->getHealth() <= 0) {
				window.close();
			}
			it->determine_direction();
			it->move();
			it->collide(floorY, window.getSize());
		}

		players[0]->look(players[1]->getPos().x);
		players[1]->look(players[0]->getPos().x);

		//render
		window.clear();
		window.draw(backgroundSprite);
		timer.count(ref(window));
		window.draw(floorSprite);
		for (auto& it : players) {
			it->draw(ref(window));
		}
		window.display();
	}
}

void gameEventLoop(sf::RenderWindow& window, vector<Player*>& players) {
	sf::Event event;
	while (window.pollEvent(event))
	{
		// Close window: exit--------------------------------------------------------------------------------------------------------------------------
		if (event.type == sf::Event::Closed)
			window.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) { //press lcontrol: exit
			window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			players[0]->keys[LEFT] = true;
		}
		else players[0]->keys[LEFT] = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			players[0]->keys[RIGHT] = true;
		}
		else players[0]->keys[RIGHT] = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			players[0]->keys[UP] = true;
		}
		else players[0]->keys[UP] = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			players[0]->keys[DOWN] = true;
		}
		else players[0]->keys[DOWN] = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			players[1]->keys[LEFT] = true;
		}
		else players[1]->keys[LEFT] = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			players[1]->keys[RIGHT] = true;
		}
		else players[1]->keys[RIGHT] = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			players[1]->keys[UP] = true;
		}
		else players[1]->keys[UP] = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			players[1]->keys[DOWN] = true;
		}
		else players[1]->keys[DOWN] = false;



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
			players[0]->quickAttack(ref(window), players[1]);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			players[0]->heavyAttack();
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
			players[0]->block();
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
			players[0]->specialAttack();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
			players[1]->quickAttack(ref(window), players[0]);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
			players[1]->specialAttack();
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
			players[1]->heavyAttack();
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) {
			players[1]->block();
		}

	}
}

void gameOverLoop(sf::RenderWindow& window, int winX, int winY) {

}

void gameOverEventLoop(sf::RenderWindow& window, vector<Player*>& players) {

}
