#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>


class Button {
public:
    //destrctors 
    ~Button() = default;

    //constructors
    Button(sf::Texture,const sf::Vector2f,const sf::Vector2f);

    //draw object
    void draw(sf::RenderWindow&);

    //create shapes for handling
    sf::RectangleShape createRect()const;
    sf::Sprite createShapeSprite() const;

    //get functions
    sf::Vector2f getSize() const;
    sf::Vector2f getLocation() const;
    sf::FloatRect getGlobalBounds()const;

    //set functions
    void setTexture(const sf::Texture&);
    void setLocation(const sf::Vector2f&);

private:

    std::string m_string;
    std::string m_statusString;

    sf::Font m_font;

    sf::Text m_title;
    sf::Text m_status;

    sf::Vector2f m_size;
    sf::Vector2f m_location;

    sf::Texture m_texture;

};
