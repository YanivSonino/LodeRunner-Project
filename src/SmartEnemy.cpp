#include "SmartEnemy.h"


SmartEnemy::SmartEnemy() : Enemy(), m_hangOn(0){}

SmartEnemy::SmartEnemy(const sf::Vector2f& Size, const sf::Vector2f& Location, const sf::Texture& texture, const char& Shape, const sf::Vector2f& Direction) :
	Enemy({ Size.x,Size.y}, Location, texture, Shape, Direction), m_hangOn(0){}


void SmartEnemy::nextMove()
{
	auto location = getPlayerLocation();
	//if enemy isnt falling
	if (!getFalling()) 
	{
		//calculate next move if player is in the same level
		if ((int)getLocation().y - (int)location.y < 4 && (int)getLocation().y - (int)location.y > -4) 
		{

			if (getLocation().x >= location.x) 
			{
				setNextMove({ -1,0 });
			}

			else if (getLocation().x < location.x) 
			{
				setNextMove({ 1,0 });
			}
		}
		//calculate next move if player isnt in the same level
		else 
		{

			if (getLocation().y -2 > location.y) 
			{

				if (getLocation().x >= location.x && !m_hangOn) 
				{
					setNextMove({ -1,0 });
					m_hangOn = 0;
				}

				else if (getLocation().x < location.x && !m_hangOn)
				{
					setNextMove({ 1,0 });
					m_hangOn = 0;
				}

				if (getLadderAbove()) 
				{
					m_hangOn = 1;
					setNextMove({ 0,-1 });
					return;
				}

				if 
					(getOnLadder() && m_hangOn) 
				{
					setNextMove({ 0,-1 });
					if (!getLadderBenith()) 
					{
						m_hangOn = 0;
					}
				}
			}
			else
			{

				if (getLocation().x >= location.x && !m_hangOn) 

				{
					setNextMove({ -1,0 });
					m_hangOn = 0;
				}

				else if (getLocation().x < location.x && !m_hangOn) 

				{
					setNextMove({ 1,0 });
					m_hangOn = 0;
				}

				else if (getLocation().x < location.x && getOnRope()) 

				{
					setNextMove({ 0,1 });
					m_hangOn = 0;
				}

				else if (getLocation().x >= location.x && getOnRope()) 
				{
					setNextMove({ 0,1 });
					m_hangOn = 0;
				}

				if (getLadderBenith()) 
				{
					m_hangOn = 1;
					setNextMove({ 0,1 });
					return;
				}

				if (getOnLadder() && m_hangOn)
				{
					setNextMove({ 0,1 });
					if (!getLadderAbove()) 
					{
						m_hangOn = 0;
					}
				}

				if (m_hangOn && getLadderAbove() && getOnGround())
					m_hangOn = 0;
			}
		}
	}

	else 
	{
		setNextMove({ 0,1 });
		m_hangOn = 0;
	}
	
}

