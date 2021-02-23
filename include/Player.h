#pragma once
#include "DynamicObject.h"
#include "GameStats.h"
#include "Gifts.h"
#include <SFML/Graphics.hpp>

class GameController;
class Player :public DynamicObject {

private:

    sf::Vector2f m_dirToDig;

    sf::Font m_font;

    sf::Keyboard::Key m_keyPressed;

    bool m_collectedCoin;

    int m_life;
    int m_score;

public:

    //distructors
    ~Player() = default;

    //constructors
    Player();
    Player(sf::Vector2f Size, sf::Vector2f Location, sf::Texture, char Shape, sf::Vector2f Direction,sf::Font font);
    
    //draw object
    void draw(sf::RenderWindow& window);

    //game handling functions
    void moveBack();
    void lifeGift();
	void lifeLost();
    void scoreGift();
    void initScore();
    void dirToMove();
    void BonusLevel(const int&);

    //collisions with other objacts
    void handleCollision(GameObject&)override;
    void handleCollision(Player&)override;
    void handleCollision(Coin&)override;
    void handleCollision(Ladder&)override;
    void handleCollision(Rope&)override;
    void handleCollision(Wall&)override;
    void handleCollision(Board&)override;
    void handleCollision(Enemy&)override;
    void handleCollision(Gifts&)override;

    //move object
    void move(GameController& gameController)override;

    //get functions
    sf::Vector2f getDirectionDig() const;
    int getLife() const;
    int getScore(const int&);
    sf::Keyboard::Key getKeyPressed() const;

    //set functions
    void setDirectionDig(const sf::Vector2f&);
    void setKeyPressed(const sf::Keyboard::Key&);

};