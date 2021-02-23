#pragma once
#include "Enemy.h"

class RandomEnemy :public Enemy {
    public:

        //distructors
        ~RandomEnemy() = default;

        //constructors
        RandomEnemy();
        RandomEnemy(const sf::Vector2f&, const sf::Vector2f&, const sf::Texture&, const char&, const sf::Vector2f&);
        
        //moving functions
        void nextMove()override;

    };
