#include <iostream>
#include<SFML\Graphics.hpp>
//#include<SFML\Network.hpp>
#include<vector>
#include"player.h"
#include"globals.h"

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

	//player initialization
	vector<Player*> players;
	players.push_back(new Player(sf::Vector2f(150, 600), 1));
	players.push_back(new Player(sf::Vector2f(winX - 300, 600), 0));

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
				std::cout << "LEFT" << std::endl;
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

			for (auto& it : players) {
				it->move();
			}
			
		}

		for (auto& it : players) {
			it->collide(floorY, window.getSize());
		}

        //render
        window.clear();
		window.draw(floor, 2, sf::Lines);
		for (auto& it : players) {
			it->draw(ref(window));
		}
        window.display();
    };
}