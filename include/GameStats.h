#pragma once
#include "GameController.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class GameStats 
{
    std::string m_string;
    std::string m_statusString;

    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_status;

    sf::Vector2f m_size;
    sf::Vector2f m_location;

    sf::RectangleShape m_box;

    int m_stat;

public:
    //distructor
    ~GameStats() = default;

    //constructors
    GameStats(const std::string&, unsigned int, int, const sf::Color, int, const sf::Font);

    //draw object
    void draw(sf::RenderWindow& window);

    //creates status shapes
    sf::Text createText() const;
    sf::Text createStatText() const;

    //set functions
    void setfont(const sf::Font& other);
    void setStat(const int&);

    //get functions
    int getStat() const;
    
};
