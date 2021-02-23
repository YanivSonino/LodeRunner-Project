#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>

class Player;
class Enemy;
class Coin;
class Ladder;
class Wall;
class Rope;
class Board;
class Gifts;

class GameObject {

private:

	sf::Vector2f m_location;
	sf::Vector2f m_size;

	sf::Sprite m_sprite;

	sf::Texture m_texture;

	char m_shape;

protected:

	bool m_isDisposed;

public:

	//distructors
	virtual ~GameObject() = default;

	//constructors
	GameObject();
	GameObject(const sf::Vector2f& , const sf::Vector2f&, const sf::Texture&, const char&);

	//draw object
	virtual void draw(sf::RenderWindow& window)const;

	//shapes, locations and sizes handling
	virtual sf::FloatRect getGlobalBounds() const;
	sf::Sprite createShapeSprite() const;
	virtual sf::Sprite getSprite()const;
	virtual char getShape()const;
	virtual sf::Vector2f getLocation()const;
	virtual sf::Vector2f getSize()const; 
	sf::RectangleShape createRect() const;

	//collisions with other objects
	virtual void handleCollision(GameObject&) = 0;
	virtual void handleCollision(Player&) = 0;
	virtual void handleCollision(Coin&) = 0;
	virtual void handleCollision(Ladder&) = 0;
	virtual void handleCollision(Rope&) = 0;
	virtual void handleCollision(Wall&) = 0;
	virtual void handleCollision(Board&) = 0;
	virtual void handleCollision(Enemy&) = 0;
	virtual void handleCollision(Gifts& )= 0;
	bool checkCollision(const sf::FloatRect&);

	//boolean functions to handle actions
	bool checkWhereToDig(const sf::FloatRect& , const sf::Vector2f&, const sf::Vector2f&);
	bool checkCanYouDig(const sf::FloatRect&, const sf::Vector2f&, const sf::Vector2f&);
	bool checkCenter(const sf::FloatRect&);
	bool checkBottomCollision(const sf::FloatRect&);
	bool checkTopCollision(const sf::FloatRect&);
	bool isDisposed() const;

	//set functions
	virtual void setSize(const sf::Vector2f);
	virtual void setLocation(const sf::Vector2f);
	virtual void setDisposed(const bool&);
};


