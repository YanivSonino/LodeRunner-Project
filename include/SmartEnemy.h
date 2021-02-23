#pragma once
#include "Enemy.h"

class SmartEnemy :public Enemy {

private:

    bool m_hangOn;

public:

    //distructors
    ~SmartEnemy() = default;

    //constructors
    SmartEnemy();
    SmartEnemy(const sf::Vector2f&, const sf::Vector2f&, const sf::Texture&, const char&, const sf::Vector2f&);

    //moving functions
    void nextMove()override;

};
