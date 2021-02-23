#include "Ladder.h"

Ladder::Ladder() : StaticObject(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Texture(), 'H'){}

Ladder::Ladder(const Ladder& ladder) : StaticObject(ladder.getSize(), ladder.getLocation(), sf::Texture(), 'H'){}

Ladder::Ladder(sf::Vector2f Location, sf::Texture texture) : StaticObject(LADDERSIZE, Location,texture, 'H'){}

void Ladder::draw(sf::RenderWindow& window)
{
	window.draw(createShapeSprite());
}

void Ladder::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}

void Ladder::handleCollision(Player& gameObject) 
{
	gameObject.handleCollision(*this);
}

void Ladder::handleCollision(Coin& gameObject){}

void Ladder::handleCollision(Ladder& gameObject){}

void Ladder::handleCollision(Rope& gameObject){}

void Ladder::handleCollision(Wall& gameObject){}

void Ladder::handleCollision(Board& gameObject){}

void Ladder::handleCollision(Enemy& gameObject)
{
	gameObject.handleCollision(*this);
}

void Ladder::handleCollision(Gifts& gameObject){}


