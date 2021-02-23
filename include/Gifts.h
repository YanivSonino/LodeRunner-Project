#pragma once
#include "StaticObject.h"
#include <SFML/Graphics.hpp>
#include "Player.h"

class Gifts :public StaticObject {

public:

    //distructor
    ~Gifts() = default;

    //constructors
    Gifts();
    Gifts(sf::Vector2f, sf::Texture);

    //draw object
    void draw(sf::RenderWindow& window);

    //collisions with other objects
    void handleCollision(GameObject&)override;
    void handleCollision(Player&)override;
    void handleCollision(Coin&)override;
    void handleCollision(Ladder&)override;
    void handleCollision(Rope&)override;
    void handleCollision(Wall&)override;
    void handleCollision(Board&)override;
    void handleCollision(Enemy&)override;
    void handleCollision(Gifts&)override;

};
