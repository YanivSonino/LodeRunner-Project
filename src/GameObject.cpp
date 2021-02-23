#include "GameObject.h"



GameObject::GameObject(): m_size(PIXEL, PIXEL), m_location(0, 0), m_sprite(sf::Sprite()),m_shape(' '),m_isDisposed(false){}

GameObject::GameObject(const sf::Vector2f& Size , const sf::Vector2f& Location, const sf::Texture& texture, const char& Shape) :
	m_size(Size), m_location(Location) , m_shape(Shape), m_isDisposed(false),m_texture(texture)
{
	m_sprite = createShapeSprite();
}

void  GameObject::draw(sf::RenderWindow& window) const
{
	//if object is not nullptr(space)
	if(this)
	window.draw(createShapeSprite());
}

sf::FloatRect GameObject::getGlobalBounds() const
{
	return createRect().getGlobalBounds();
}

sf::Sprite GameObject::createShapeSprite() const
{
	auto shape = sf::Sprite(m_texture);

	shape.setScale(m_size.x / shape.getGlobalBounds().width,
		m_size.y / shape.getGlobalBounds().height);
	shape.setPosition(m_location);

	return shape;
}

sf::Sprite GameObject::getSprite() const
{
	return m_sprite;
}

char GameObject::getShape() const
{
	return m_shape;
}

sf::Vector2f GameObject::getLocation() const
{
	return m_location;
}

sf::Vector2f GameObject::getSize() const
{
	return m_size;
}

sf::RectangleShape GameObject::createRect() const
{
	auto shape = sf::RectangleShape(sf::Vector2f(m_size.x,m_size.y));
	shape.setPosition(m_location);

	return shape;
}

bool GameObject::checkCollision(const sf::FloatRect& floatRect)
{
	auto entityBounds = getGlobalBounds();
	entityBounds.top += 2;

	if (floatRect.intersects(entityBounds)) 
	{
		return true;
	}

	return false;
}

bool GameObject::checkWhereToDig(const sf::FloatRect& floatRect, const sf::Vector2f& dir, const sf::Vector2f& boardSize)
{

	auto entityBounds = getGlobalBounds();
	auto start = sf::Vector2f{ (RESOLUTION.x - boardSize.x) / 2 , getGlobalBounds().top };

	entityBounds.left = start.x + PIXEL * ((int)(entityBounds.left - start.x) / PIXEL);
	auto playerLocation = entityBounds.left;

	if (dir.x == 1) 
	{
		entityBounds.left += floatRect.width;
	}

	else 
	{
		entityBounds.left -= floatRect.width;
	}

	entityBounds.top += floatRect.height;

	if (floatRect.intersects(entityBounds))
	{
		setLocation({ playerLocation , getLocation().y });
		return true;
	}

	return false;

}

bool GameObject::checkCanYouDig(const sf::FloatRect& floatRect, const sf::Vector2f& dir, const sf::Vector2f& boardSize)
{
	/// 
	/// the function set location by key pressed and checks if there is an object
	/// there so the player cant dig
	/// 

	auto entityBounds = getGlobalBounds();
	auto start = sf::Vector2f{ (RESOLUTION.x - boardSize.x) / 2 , getGlobalBounds().top };
	
	entityBounds.left = start.x + PIXEL * ((int)(entityBounds.left - start.x) / PIXEL);

	if (dir.x == 1) 
	{
		entityBounds.left += entityBounds.width-2;
	}

	else 
	{
		entityBounds.left -= entityBounds.width-2;
	}

	if (floatRect.intersects(entityBounds)) 
	{
		return true;
	}

	return false;

}

bool GameObject::checkCenter(const sf::FloatRect& floatRect)
{
	/// 
	/// the function creates rect shape and checks if the other rect have the same center location
	/// 
	auto entityBounds = getGlobalBounds();
	entityBounds.top += 2;

	if (entityBounds.contains(floatRect.left + (floatRect.width / 2), floatRect.top+(floatRect.height /2))) 
	{
		return true;
	}

	return false;
}


bool GameObject::checkBottomCollision(const sf::FloatRect& floatRect)
{
	auto entityBounds = getGlobalBounds();
	//if the object is enemy
	if (getShape() == ENEMY) 
	{
		entityBounds.height -= 0;
	}

	else
		entityBounds.height -= 2;
	
	if (entityBounds.contains(floatRect.left, floatRect.top)) {
		return true;
	}

	return false;
}

bool GameObject::checkTopCollision(const sf::FloatRect& floatRect)
{
	auto entityBounds = getGlobalBounds();
	entityBounds.top += 2;

	if (entityBounds.contains(floatRect.left, floatRect.top + floatRect.height)) 
	{
		return true;
	}

	return false;
}

void GameObject::setDisposed(const bool &isDisposed ) 
{
	m_isDisposed = isDisposed;
}

bool GameObject::isDisposed() const
{
	return m_isDisposed;
}

void GameObject::setSize(const sf::Vector2f size)
{
	m_size = size;
}

void GameObject::setLocation(const sf::Vector2f location)
{
	m_location = location;
}


