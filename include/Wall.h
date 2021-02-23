#pragma once
#include "StaticObject.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"


class Wall :public StaticObject 
{
private:

    sf::Time m_timeToRebuild;

    sf::Clock m_clock;

    bool m_IsDig;
    bool m_objectInsideDigged;

public:

    //distructors
    ~Wall() = default;

    //constructors
    Wall();
    Wall(const Wall& board);
    Wall(sf::Vector2f, sf::Texture);

    //draw object
    void draw(sf::RenderWindow& window)const;
    
    //collision with othe objects
    void handleCollision(GameObject&)override;
    void handleCollision(Player&)override;
    void handleCollision(Coin&)override;
    void handleCollision(Ladder&)override;
    void handleCollision(Rope&)override;
    void handleCollision(Wall&)override;
    void handleCollision(Board&)override;
    void handleCollision(Enemy&)override;
    void handleCollision(Gifts&)override;

    //handle digged wall
    void reBuild();
    void startTimer();

    //get functions
    bool getDig() const;
    bool getInsideDigged() const;
   
    //set functions
    void setInsideDigged(const bool& set);
    void setDig(const bool& diged);

   

};


