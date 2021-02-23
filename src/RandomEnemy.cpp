#include "RandomEnemy.h"


RandomEnemy::RandomEnemy() : Enemy()
{
	srand(time(NULL));
}

RandomEnemy::RandomEnemy(const sf::Vector2f& Size, const  sf::Vector2f& Location, const sf::Texture& texture, const char& Shape, const sf::Vector2f& Direction) :
	Enemy({ Size.x - 2,Size.y - 2 }, Location, texture, Shape, Direction){}

void RandomEnemy::nextMove()
{
	srand(time(NULL));
	auto Rand = rand() % 4;

	sf::Vector2f dir;

	if (!getFalling())
	{
		switch (Rand) 
		{

		case 0:
			dir = { 1, 0 };
			break;

		case 1:
			dir = { -1, 0 };
			break;

		case 2:
			dir = { 0, 1 };
			break;

		case 3:
			dir = { 0, -1 };
			break;
		}
	}

	else 
	{
		dir = { 0,1 };

	}

	setNextMove(dir);
}

