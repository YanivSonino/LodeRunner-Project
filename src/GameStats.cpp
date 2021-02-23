#include "GameStats.h"

GameStats::GameStats(const std::string& string, unsigned int textSize, int location, const sf::Color color, int stat, const sf::Font font) :
	m_size(STATSIZE), m_box(m_size), m_stat(stat), m_font(font), m_string(string)
{
	m_location = sf::Vector2f(m_size.x * location, m_size.y);
	m_box.setPosition(m_location);
	m_box.setFillColor(color);
	m_box.setOutlineThickness(2);
	m_box.setOutlineColor(sf::Color::Red);
}

void GameStats::draw(sf::RenderWindow& window)
{
	window.draw(m_box);
	m_title = createText();
	window.draw(m_title);
	window.draw(createStatText());
}

sf::Text GameStats::createText() const
{
	auto text = sf::Text(m_string, m_font);

	text.setCharacterSize(TEXTSIZE);
	text.setPosition(m_location.x + m_box.getGlobalBounds().width / 2 - text.getGlobalBounds().width / 2,
		m_location.y);

	return text;
}

void GameStats::setfont(const sf::Font& other)
{
	m_font = other;
	m_title.setFont(m_font);
	m_title.setString(m_string);
}

void GameStats::setStat(const int& newStat)
{
	m_stat = newStat;
}

int GameStats::getStat() const
{
	return m_stat;
}

sf::Text GameStats::createStatText() const
{
	auto a = std::to_string(m_stat);
	auto text = sf::Text(a, m_font);

	text.setCharacterSize(TEXTSIZE);
	text.setPosition(m_title.getGlobalBounds().left + m_title.getGlobalBounds().width + 4, m_location.y);

	return text;

}