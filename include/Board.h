#pragma once
#include <iostream>
#include "StaticObject.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

class Board :public StaticObject {

public:

    //destrcutor
    ~Board() = default;

    //constructors
    Board();
    Board(sf::Vector2f, sf::Texture);

    //draw object
    void draw(sf::RenderWindow&);

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

