#include "Rope.h"

Rope::Rope() : StaticObject(){}

Rope::Rope(sf::Vector2f Location, sf::Texture texture) : StaticObject(GRIDSIZE, Location,texture, '-'){}

void Rope::draw(sf::RenderWindow& window)
{
	window.draw(createShapeSprite());
}

void Rope::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}
void Rope::handleCollision(Player& gameObject)
{
	auto ropeBounds = createRect().getGlobalBounds();
	auto playerBounds = gameObject.getGlobalBounds();

	//if player's direction is up or down
	if (gameObject.getDirection().x == 1 || gameObject.getDirection().x == -1 ) 
	{
		gameObject.setLocation(sf::Vector2f(gameObject.getLocation().x, getLocation().y + 15));
	}

	//if player's direction is up and object not climbing
	if (gameObject.getDirection().y == 1 && !gameObject.getOnLadder())
	{
		//bottom coliision
		if (playerBounds.top + playerBounds.height > ropeBounds.top
			&& playerBounds.top + playerBounds.height < ropeBounds.top + ropeBounds.height
			&& playerBounds.left < ropeBounds.left + ropeBounds.width
			&& playerBounds.left + playerBounds.width > ropeBounds.left)
		{

			gameObject.setLocation({ playerBounds.left,ropeBounds.top + 15});
		}
	}
	gameObject.handleCollision(*this);
}
void Rope::handleCollision(Coin& gameObject){}

void Rope::handleCollision(Ladder& gameObject){}

void Rope::handleCollision(Enemy& gameObject)
{
	auto ropeBounds = createRect().getGlobalBounds();
	auto playerBounds = gameObject.getGlobalBounds();

	//if enemy's direction is up or down
	if (gameObject.getNextMove().x == 1 || gameObject.getNextMove().x == -1) {
		gameObject.setLocation(sf::Vector2f(gameObject.getLocation().x, getLocation().y + 13));
	}

	//if enemy's direction is up and object not climbing
	if (gameObject.getDirection().y == 1 && !gameObject.getOnLadder())
	{
		if (playerBounds.top + playerBounds.height > ropeBounds.top
			&& playerBounds.top + playerBounds.height < ropeBounds.top + ropeBounds.height
			&& playerBounds.left < ropeBounds.left + ropeBounds.width
			&& playerBounds.left + playerBounds.width > ropeBounds.left)
		{
			gameObject.setLocation({ playerBounds.left,ropeBounds.top + 15 });
		}
	}
	gameObject.handleCollision(*this);
}

void Rope::handleCollision(Gifts& gameObject){}

void Rope::handleCollision(Rope& gameObject){}

void Rope::handleCollision(Wall& gameObject){}

void Rope::handleCollision(Board& gameObject){}


