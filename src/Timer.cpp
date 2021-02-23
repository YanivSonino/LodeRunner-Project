#include "Timer.h"

Timer::Timer() :m_size(30, 30), m_time("HI")
{
	UpdateTimer(0);	
}

Timer::Timer(const int GenralTime,sf::Font font):m_font(font),m_size(30,30)
{
	UpdateTimer(GenralTime);
}

void Timer::setFont(const sf::Font& fontaj) 
{
	m_font = fontaj;
}

void Timer::UpdateTimer(const int GenralTime) 
{
	m_minutes = GenralTime / 60;
	m_seconds = GenralTime - (m_minutes * 60);
}

int Timer::getGenralTime()const 
{
	return m_genralTime;
}

void Timer::setGenralTime(const int & gentime)
{
	m_genralTime=gentime;
}

int Timer::getTimer()const  
{
	return m_minutes * 60 + m_seconds;
}

void Timer::setLocation(const sf::Vector2f&Location)
{
	m_location = Location;
}

void Timer::draw(sf::RenderWindow& window)
{
	window.draw(Timer2Text());
}

sf::Text Timer::Timer2Text() const
{
	//set the timer string
	std::string timeText;
	timeText += "TIME LEFT: ";

	if (m_minutes < 10) 
	{
		timeText += "0";
	}

	timeText += std::to_string(m_minutes);
	timeText += ":";

	if (m_seconds < 10) 
	{
		timeText += "0";
	}

	timeText += std::to_string(m_seconds);
	auto text = sf::Text(timeText, m_font);

	text.setCharacterSize(TEXTSIZE);
	sf::FloatRect centerText = text.getGlobalBounds();
	text.setOrigin(centerText.left + centerText.width / 2.0f, centerText.top + centerText.height / 2.0f);
	text.setPosition(m_location);

	if (m_seconds < 30 && m_minutes == 0) 
	{
		text.setColor(sf::Color::Red);
	}

	return text;
}