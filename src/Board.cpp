#include "Board.h"

Board::Board():StaticObject(sf::Vector2f(0, 0), sf::Vector2f(0,0), sf::Texture(), 'B'){}

Board::Board(sf::Vector2f Size, sf::Texture texture):StaticObject(Size,
	sf::Vector2f((RESOLUTION.x-Size.x)/2,(RESOLUTION.y-Size.y)/2),texture,'B'){}

void Board::draw(sf::RenderWindow& window)
{
	window.draw(createShapeSprite());
}

void Board::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}

void Board::handleCollision(Player& gameObject) 
{
	auto boardBounds = createRect().getGlobalBounds();
	auto playerBounds = gameObject.getGlobalBounds();
	
	//bottom coolision
	if (playerBounds.top + playerBounds.height > boardBounds.top + boardBounds.height)
	{
		gameObject.setLocation({ playerBounds.left ,boardBounds.top + boardBounds.height - playerBounds.height });
		gameObject.setOnGround(1);
		gameObject.setFalling(0);
	}

	//top collision
	if (playerBounds.top < boardBounds.top ) 
	{
		gameObject.setLocation({ playerBounds.left ,boardBounds.top});
	}

	//left collision
	if (playerBounds.left < boardBounds.left)
	{
		gameObject.setLocation({ boardBounds.left,playerBounds.top });
	}

	//right collision
	if (playerBounds.left + playerBounds.width > boardBounds.left + boardBounds.width)
	{
		gameObject.setLocation({ boardBounds.left + boardBounds.width - playerBounds.width ,playerBounds.top });
	}
}

void Board::handleCollision(Coin& gameObject) {}

void Board::handleCollision(Ladder& gameObject){}

void Board::handleCollision(Rope& gameObject){}

void Board::handleCollision(Wall& gameObject){}

void Board::handleCollision(Board& gameObject)
{
	if (&gameObject == this) return;

	//double dispatch
	gameObject.handleCollision(*this);
}

void Board::handleCollision(Enemy& gameObject)
{

	auto boardBounds = createRect().getGlobalBounds();
	auto playerBounds = gameObject.getGlobalBounds();

	//bottom collision
	if (playerBounds.top + playerBounds.height > boardBounds.top + boardBounds.height)
	{
		gameObject.setLocation({ playerBounds.left ,boardBounds.top + boardBounds.height - playerBounds.height });
		gameObject.setOnBoard(1);
	}

	else gameObject.setOnBoard(0);

	//top collision
	if (playerBounds.top < boardBounds.top) {

		gameObject.setLocation({ playerBounds.left ,boardBounds.top });

	}

	//left collision
	if (playerBounds.left < boardBounds.left) {

		gameObject.setLocation({ boardBounds.left,playerBounds.top });

	}

	//right collision
	if (playerBounds.left + playerBounds.width > boardBounds.left + boardBounds.width)
	{
		gameObject.setLocation({ boardBounds.left + boardBounds.width - playerBounds.width ,playerBounds.top });
	}
}

void Board::handleCollision(Gifts& gameObject){}

