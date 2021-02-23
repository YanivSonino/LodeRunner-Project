#include "ConstEnemy.h"


ConstEnemy::ConstEnemy() : Enemy()
{}

ConstEnemy::ConstEnemy(const sf::Vector2f& Size,const sf::Vector2f& Location,const sf::Texture& texture,const char& Shape,const sf::Vector2f& Direction) :
	Enemy({ Size.x - 2,Size.y - 2 }, Location, texture, Shape, Direction){}


void ConstEnemy::nextMove()
{
	static int stepsNum = 0;
	sf::Vector2f dir;
	
	//enemy is not falling
	if (!getFalling()) 
	{
		switch ((stepsNum / 500) % 2)
		{
		case 0:
			dir = { 1, 0 };
			break;
		case 1:
			dir = { -1, 0 };
			break;
		}
	}

	else 
	{
		dir = { 0,1 };
	}

	stepsNum++;
	setNextMove(dir);
}

