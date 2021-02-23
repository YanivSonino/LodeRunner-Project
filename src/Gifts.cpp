#include "Gifts.h"

Gifts::Gifts() : StaticObject(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Texture(), '+'){}

Gifts::Gifts(sf::Vector2f Location, sf::Texture texture) : StaticObject(GRIDSIZE, Location, texture, '+') {}

void Gifts::draw(sf::RenderWindow& window)
{
	window.draw(createShapeSprite());
}

void Gifts::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}

void Gifts::handleCollision(Gifts& gameObject)
{
	if (&gameObject == this) return;
}

void Gifts::handleCollision(Player& gameObject)
{
	m_isDisposed = true;
}

void Gifts::handleCollision(Coin& gameObject){}

void Gifts::handleCollision(Ladder& gameObject){}

void Gifts::handleCollision(Rope& gameObject){}

void Gifts::handleCollision(Wall& gameObject){}

void Gifts::handleCollision(Board& gameObject){}

void Gifts::handleCollision(Enemy& gameObject){}
