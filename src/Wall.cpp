#include "Wall.h"

Wall::Wall() : StaticObject(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Texture(), '#'), m_IsDig(0), m_objectInsideDigged(0){}
Wall::Wall(const Wall& board) : StaticObject(board.getSize(), board.getLocation(), sf::Texture() ,'#'), m_IsDig(0)
, m_objectInsideDigged(0) {}

Wall::Wall( sf::Vector2f Location, sf::Texture texture) :
	StaticObject(GRIDSIZE, Location,texture, '#'),m_IsDig(0), m_objectInsideDigged(0){}

void Wall::draw(sf::RenderWindow& window)const
{
	if (!m_IsDig)
	{
		window.draw(createShapeSprite());
	}
}

void Wall::setDig(const bool& diged)
{
	m_IsDig = diged;
}

bool Wall::getDig()const
{
	return m_IsDig;
}

void Wall::handleCollision(GameObject& gameObject) 
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}

void Wall::handleCollision(Enemy& gameObject)
{

	auto wallBounds = createRect().getGlobalBounds();
	auto enemyBounds = gameObject.getGlobalBounds();

	//if the wall and enemy arent digged
	if (gameObject.getDig() && !m_IsDig)
	{
		gameObject.setLocation({ enemyBounds.left, wallBounds.top - wallBounds.height });
	}

	//if  no object inside
	if (m_objectInsideDigged) return;
	
	if (m_IsDig) 
	{
		gameObject.setDig(true);
	}

	else
	{
		gameObject.setDig(false);
	}
	
	gameObject.handleCollision(*this);
}

void Wall::handleCollision(Gifts& gameObject){}

void Wall::handleCollision(Player& gameObject) 
{
    gameObject.handleCollision(*this);
}
void Wall::handleCollision(Coin& gameObject){}

void Wall::handleCollision(Ladder& gameObject){}

void Wall::handleCollision(Rope& gameObject){}

void Wall::handleCollision(Wall& gameObject)
{
    gameObject.handleCollision(*this);
}

void Wall::handleCollision(Board& gameObject){}

void Wall::reBuild()
{
	//timer to restore digged wall
	if ((int)m_clock.getElapsedTime().asSeconds() - (int)m_timeToRebuild.asSeconds() == 7) 
	{
		m_IsDig = 0;
		m_objectInsideDigged = 0;
	}
}

void Wall::startTimer()
{
	m_timeToRebuild = m_clock.getElapsedTime();	
}

bool Wall::getInsideDigged() const 
{
	return m_objectInsideDigged;
}

void Wall::setInsideDigged(const bool& set) 
{
	m_objectInsideDigged = set;
}