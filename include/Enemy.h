#pragma once
#include "DynamicObject.h"
#include <SFML/Graphics.hpp>

class Enemy :public DynamicObject {
private:

    sf::Vector2f m_nextMove;
    sf::Vector2f m_playerLocation;

    bool m_isDiged;

public:

    //distructors
    virtual ~Enemy() = default;

    //constructors
    Enemy();
    Enemy(const sf::Vector2f&,const sf::Vector2f&,const sf::Texture&,const char&,const sf::Vector2f&);
    
    //get functions
    bool getDig() const;
    sf::Vector2f getPlayerLocation()const;
    virtual sf::Vector2f getNextMove();

    //set functions
    virtual void setNextMove(const sf::Vector2f&);
    void setDig(const bool&);
    virtual void setPlayerLocation(const sf::Vector2f&);

    //handle collisions with objects
    void handleCollision(GameObject&)override;
    void handleCollision(Player&)override;
    void handleCollision(Coin&)override;
    void handleCollision(Ladder&)override;
    void handleCollision(Rope&)override;
    void handleCollision(Wall&)override;
    void handleCollision(Board&)override;
    void handleCollision(Enemy&)override;
    void handleCollision(Gifts&)override;

    //moving functions
    virtual void nextMove() = 0;
    void move(GameController&)override;

    //draw object
    void draw(sf::RenderWindow& window);
};