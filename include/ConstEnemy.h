#pragma once
#include "Enemy.h"

class ConstEnemy :public Enemy {

private:

public:

    //destrcutor
    ~ConstEnemy() = default;

    //constructors
    ConstEnemy();
    ConstEnemy(const sf::Vector2f&, const sf::Vector2f&, const sf::Texture&, const char&, const sf::Vector2f&);

    //finds the enemy next move
    void nextMove()override;
};
