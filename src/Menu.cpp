#include "Menu.h"

Menu::Menu()
{
    auto buttonColor = GRAY;
    std::string buttonTitle;

    m_quitButtonT.loadFromFile("Quit.PNG");
    m_startButtonT.loadFromFile("Start.PNG");
    m_startButtonTM.loadFromFile("StartOn.PNG");
    m_quitButtonTM.loadFromFile("QuitOn.PNG");
    m_openT.loadFromFile("Open.PNG");

    for (auto buttonIndex = 0; buttonIndex < NUMOFSTATS; buttonIndex++) 
    {
        switch (buttonIndex) 
        {
        case(2):
            buttonTitle = "START";
            m_menuButtons.push_back(Button(m_startButtonT, STARTLOCATION , START_BUTTON_SIZE));
            break;
        case(1):
            buttonTitle = "QUIT";
            m_menuButtons.push_back(Button(m_quitButtonT, QUITLOCATION, QUIT_BUTTON_SIZE));
            break;
        case(0):
            buttonTitle = "OPEN";
            m_menuButtons.push_back(Button(m_openT, { 0,0 }, RESOLUTION_SIZE));
            break;
        }
    }
}

void Menu::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < m_menuButtons.size(); i++) 
    {
        m_menuButtons[i].draw(window);
    }
}

sf::FloatRect Menu::getGlobalStart()
{
    return createRect(m_menuButtons[2]).getGlobalBounds();
}

sf::FloatRect Menu::getGlobalQuit()
{
    return createRect(m_menuButtons[1]).getGlobalBounds();
}

sf::RectangleShape Menu::createRect(Button& button) 
{
    auto shape = sf::RectangleShape(sf::Vector2f(button.getSize().x, button.getSize().y));
    shape.setPosition(button.getLocation());

    return shape;
}
void Menu::ChangeStartMarkedSpirte() 
{
    m_menuButtons[2].setTexture(m_startButtonTM);
}

void Menu::ChangeStartSpirte()
{
    m_menuButtons[2].setTexture(m_startButtonT);
}

void Menu::ChangeQuitMarkedSpirte()
{
    m_menuButtons[1].setTexture(m_quitButtonTM);
}

void Menu::ChangeQuitSpirte()
{
    m_menuButtons[1].setTexture(m_quitButtonT);
}
