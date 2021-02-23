#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

class Button;

class Menu {
public:

    //distructor
    ~Menu() = default;

    //constructors
    Menu();

    //draw object
    void draw(sf::RenderWindow& window);

    //handle shape, location and size
    sf::FloatRect getGlobalStart();
    sf::FloatRect getGlobalQuit();
    sf::RectangleShape createRect(Button &);

    //change sprites functions
    void ChangeStartMarkedSpirte();
    void ChangeStartSpirte();
    void ChangeQuitMarkedSpirte();
    void ChangeQuitSpirte();

private:

    std::vector<Button> m_menuButtons;

    sf::Font m_font;

    sf::Texture m_quitButtonT;
    sf::Texture m_startButtonT;
    sf::Texture m_openT;
    sf::Texture m_startButtonTM;
    sf::Texture m_quitButtonTM;

};



