#include <iostream>
#include<SFML\Graphics.hpp>
//#include<SFML\Network.hpp>
#include<vector>
#include<ctime>
#include"player.h"
#include"globals.h"
#include"timer.h"

using namespace std;

int main()
{
    cout << "we ball.\n";

	//variables
	//window variables
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "FIGHT!", sf::Style::Fullscreen);
	window.setFramerateLimit(60);
	int winX = window.getSize().x;
	int winY = window.getSize().y;
	sf::Event event;

	//timer
	Timer timer(winX);

	//text setup
	string elapsed_time = "00:00";
	sf::Font font;
	font.loadFromFile("Assests/Font/arial.ttf");
	sf::Text text(elapsed_time, font);
	text.setCharacterSize(60);
	text.setOrigin(text.getCharacterSize(), 0);
	text.setPosition(winX / 2, 0);
	text.setFillColor(sf::Color::Blue);

	//bg
	sf::Texture bg0Tex;
	bg0Tex.loadFromFile("Assests/Background/bg0.png");
	sf::Sprite bg0(bg0Tex);

	//player initialization
	vector<Player*> players;
	players.push_back(new Player(sf::Vector2f(150, 600), true));
	players.push_back(new Player(sf::Vector2f(winX - 300, 600), false));

	//floor variables
	int floorY = 900;
	sf::Vertex floor[] = { sf::Vertex(sf::Vector2f(0, floorY), sf::Color::Red), sf::Vertex(sf::Vector2f(winX, floorY), sf::Color::Red) };
	

    while (window.isOpen()) {
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
				players[0]->damage(5);
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
				players[1]->damage(5);
			}
			else players[1]->keys[UP] = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				players[1]->keys[DOWN] = true;
			}
			else players[1]->keys[DOWN] = false;



			if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
				players[0]->quickAttack();
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
				players[1]->quickAttack();
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

		for (auto& it : players) {
			it->determine_direction();
			it->move();
			it->collide(floorY, window.getSize());
		}

		players[0]->look(players[1]->getPos().x);
		players[1]->look(players[0]->getPos().x);

        //render
        window.clear();
		window.draw(bg0);
		timer.count(ref(window));
		window.draw(floor, 2, sf::Lines);
		for (auto& it : players) {
			it->draw(ref(window));
		}
        window.display();
    };
}