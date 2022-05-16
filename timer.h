#pragma once

#include<ctime>;
#include<SFML/Graphics.hpp>

using namespace std;

class Timer
{
public:
	Timer(int winX);
	~Timer();
	void count(sf::RenderWindow& window);
private:
	time_t timer;
	time_t start;
	string minStr = "00";
	string secStr = "00";
	int seconds = 0;
	int minutes = 0;
	string elapsed_time = "00:00";
	sf::Font font;
	sf::Text text;
};

