#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>

class Timer {
private:

	int m_seconds,m_minutes;
	int m_genralTime;

	sf::Font m_font;

	sf::Text m_title;

	sf::Vector2f m_location;
	sf::Vector2f m_size;

	std::string m_time;

public:

	//distructors
	~Timer() = default;

	//constructors
	Timer();
	Timer(const int GenralTime, sf::Font);

	//set functions
	void setFont(const sf::Font&);
	void setGenralTime(const int& gentime);
	void setLocation(const sf::Vector2f&);

	//get functions
	int getGenralTime() const;
	int getTimer() const;

	//draw object
	void draw(sf::RenderWindow&);

	//timer handling
	sf::Text Timer2Text() const;
	void UpdateTimer(const int);

};