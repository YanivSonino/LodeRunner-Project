
#include "DynamicObject.h"



DynamicObject::DynamicObject():m_direction(sf::Vector2f(0,0)),m_isFalling(0), m_isOnGround(0),
m_isOnLadder(0), m_isOnRope(0), m_isClimbing(0),m_ladderAbove(0), m_ladderBenith(0), m_isOnBoard(0){}

DynamicObject::DynamicObject(sf::Vector2f Size, sf::Vector2f Location, sf::Texture texture, char Shape, sf::Vector2f Direction):
	GameObject(Size,Location,texture,Shape), m_direction(Direction), m_lastLocation(Location), m_isFalling(0), m_isOnGround(0),
	m_isOnLadder(0), m_isOnRope(0), m_isClimbing(0), m_ladderAbove(0), m_ladderBenith(0), m_isOnBoard(0), m_onDiggedWall(0){}

bool DynamicObject::getOnDigged() const
{
	return m_onDiggedWall;
}

void DynamicObject::setOnDigged(const bool& set)
{
	m_onDiggedWall = set;
}

bool DynamicObject::getOnGround() const
{
	return m_isOnGround;
}

bool DynamicObject::getOnRope() const
{
	return m_isOnRope;
}
bool DynamicObject::getOnBoard() const
{
	return m_isOnBoard;
}

bool DynamicObject::getOnLadder() const
{
	return m_isOnLadder;
}

bool DynamicObject::getClimbing() const
{
	return m_isClimbing;
}

void DynamicObject::setClimbing(const bool& set)
{
	m_isClimbing = set;
}

void DynamicObject::setOnGround(const bool& set)
{
	m_isOnGround = set;
}

void DynamicObject::setOnBoard(const bool& set)
{
	m_isOnBoard = set;
}

void DynamicObject::setOnRope(const bool& set)
{
	m_isOnRope = set;
}

void DynamicObject::setOnLadder(const bool& set)
{
	m_isOnLadder = set;
}

sf::Vector2f DynamicObject::getDirection() const
{
	return m_direction;
}

float DynamicObject::getTopLadder() const
{
	return m_topladderheight;
}

sf::Vector2f DynamicObject::getLastLcation()
{
	return m_lastLocation;
}

void DynamicObject::setLastLocation(const sf::Vector2f& location)
{
	m_lastLocation = location;
}

void DynamicObject::setDirection(const sf::Vector2f& Direction)
{
	m_direction = Direction;
}

void DynamicObject::setTopLadder(const float& set) 
{
	m_topladderheight = set;
}

void DynamicObject::setFalling(const bool& gravity) 
{
	m_isFalling = gravity;
}

bool DynamicObject::getFalling() const 
{
	return m_isFalling;
}

void DynamicObject::setLadderBenith(const bool& set)
{
	m_ladderBenith = set;
}

void DynamicObject::setLadderAbove(const bool& set)
{
	m_ladderAbove = set;
}

bool DynamicObject::getLadderAbove()const 
{
	return m_ladderAbove;
}

bool DynamicObject::getLadderBenith()const 
{
	return m_ladderBenith;
}

void DynamicObject::init()
{
	/// <summary>
	/// initalize all boolean
	/// </summary>
	setOnDigged(false);
	setOnBoard(false);
	setLadderAbove(false);
	setLadderBenith(false);
	setOnGround(false);
	setOnRope(false);
	setOnLadder(false);
	setOnRope(false);
}