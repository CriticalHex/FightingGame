#include <iostream>
#include<SFML\Graphics.hpp>
//#include<SFML\Network.hpp>
#include"player.cpp"

using namespace std;

void floorCollide(sf::RenderWindow& window, Player& p1, Player& p2);

int main()
{
    cout << "we ball.\n";

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "FIGHT!", sf::Style::Fullscreen);

    Player p1(200, 900, 1);
    Player p2(window.getSize().x - 200, 900, 0);

    while (true) {

        //render
        window.clear();
        floorCollide(window, p1, p2);
        window.display();
    };
}

void floorCollide(sf::RenderWindow& window, Player& p1, Player& p2) {
    int ypos = 900;
    sf::Vertex floor[2] = { sf::Vertex(sf::Vector2f(0, ypos), sf::Color::Red), sf::Vertex(sf::Vector2f(window.getSize().x, ypos), sf::Color::Red) };
    window.draw(floor, 2, sf::Lines);
}