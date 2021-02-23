#include "Coin.h"

Coin::Coin() : StaticObject(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Texture(), '*'){}

Coin::Coin(const Coin& coin) : StaticObject(coin.getSize(), coin.getLocation(), sf::Texture(), '*') {}

Coin::Coin(sf::Vector2f Location, sf::Texture texture) : StaticObject(GRIDSIZE, Location,texture, '*'){}

void Coin::draw(sf::RenderWindow& window)
{
	window.draw(createShapeSprite());
}

void Coin::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}

void Coin::handleCollision(Player& gameObject) 
{
	m_isDisposed = true;
	gameObject.handleCollision(*this);
}

void Coin::handleCollision(Coin& gameObject){}

void Coin::handleCollision(Ladder& gameObject){}

void Coin::handleCollision(Rope& gameObject){}

void Coin::handleCollision(Wall& gameObject){}

void Coin::handleCollision(Board& gameObject){}

void Coin::handleCollision(Enemy& gameObject){}

void Coin::handleCollision(Gifts& gameObject){}


