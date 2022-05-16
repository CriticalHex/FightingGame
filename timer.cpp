#include"timer.h"
#include<ctime>;
#include<SFML/Graphics.hpp>

Timer::Timer(int winX)
{
	time(&start);
	time(&timer);
	seconds = difftime(timer, start);

	font.loadFromFile("Assets/Font/cryptic.otf");

	text.setString(elapsed_time);
	text.setFont(font);
	text.setCharacterSize(60);
	text.setOrigin(75, 0);
	text.setPosition(winX / 2, 0);
	text.setFillColor(sf::Color::Blue);
}

Timer::~Timer()
{
}

void Timer::count(sf::RenderWindow& window) {
	time(&timer);
	seconds = difftime(timer, start);
	minutes = seconds / 60;
	if (seconds % 60 < 10) {
		secStr = "0" + to_string(seconds % 60);
	}
	else {
		secStr = to_string(seconds % 60);
	}
	if (minutes < 10) {
		minStr = "0" + to_string(minutes);
	}
	else {
		minStr = to_string(minutes);
	}
	elapsed_time = minStr + ":" + secStr;
	text.setString(elapsed_time);

	window.draw(text);
}