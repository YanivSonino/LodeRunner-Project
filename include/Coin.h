#pragma once
#include "StaticObject.h"
#include <SFML/Graphics.hpp>

#include "Player.h"

class Coin :public StaticObject {

public:
    //destrctors
    ~Coin() = default;

    //constructors
    Coin();
    Coin(const Coin& coin);
    Coin(sf::Vector2f, sf::Texture);

    //draw object
    void draw(sf::RenderWindow& window);

    //collisions with other objects
    void handleCollision(GameObject& gameObject) override;
    void handleCollision(Player& gameObject) override;
    void handleCollision(Coin& gameObject) override;
    void handleCollision(Ladder& gameObject) override;
    void handleCollision(Rope& gameObject) override;
    void handleCollision(Wall& gameObject) override;
    void handleCollision(Board& gameObject) override;
    void handleCollision(Enemy& gameObject) override;
    void handleCollision(Gifts& gameObject) override;

};
