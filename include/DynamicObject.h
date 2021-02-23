#pragma once
#include "GameObject.h"
#include "StaticObject.h"
#include <SFML/Graphics.hpp>

class GameController;

class DynamicObject : public GameObject {
private:

	float m_topladderheight = 0;

	sf::Vector2f m_direction;
	sf::Vector2f m_lastLocation;

	bool m_isFalling;
	bool m_isClimbing;
	bool m_isOnGround;
	bool m_isOnBoard;
	bool m_isOnLadder;
	bool m_isOnRope;
	bool m_ladderAbove;
	bool m_ladderBenith;
	bool m_onDiggedWall;

public:

	//distructors
	virtual ~DynamicObject()=default;

	//constructors
	DynamicObject();
	DynamicObject(sf::Vector2f, sf::Vector2f, sf::Texture, char, sf::Vector2f);

	//get functions
	bool getOnDigged() const;
	bool getLadderAbove()const;
	bool getLadderBenith() const;
	virtual bool getOnGround()const;
	virtual bool getOnRope()const;
	virtual bool getOnBoard() const;
	virtual bool getOnLadder()const;
	virtual bool getClimbing()const;
	virtual bool getFalling() const;

	virtual float getTopLadder()const;

	virtual sf::Vector2f getLastLcation();
	virtual sf::Vector2f getDirection()const;

	//set functions
	void setOnDigged(const bool&);
	virtual void setClimbing(const bool&);
	virtual void setOnGround(const bool&);
	virtual void setOnBoard(const bool&);
	virtual void setOnLadder(const bool&);
	virtual void setOnRope(const bool&);
	virtual void setLastLocation(const sf::Vector2f&);
	virtual void setDirection(const sf::Vector2f&);
	void setTopLadder(const float&);
	virtual void setFalling(const bool&);
	void setLadderBenith(const bool&);
	virtual void setLadderAbove(const bool&);

	//initalize bool members
	virtual void init();

	//move object
	virtual void move(GameController&) = 0;

	//draw object
	virtual void draw(sf::RenderWindow&) = 0;
	
};
