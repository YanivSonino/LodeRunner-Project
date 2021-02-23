#include "Button.h"

Button::Button(const sf::Texture texture, sf::Vector2f location,const sf::Vector2f size) :
	m_size(size), m_location(location), m_texture(texture) {}


void Button::draw(sf::RenderWindow& window)
{
	window.draw(createShapeSprite());
}

sf::Sprite Button::createShapeSprite() const
{
	auto shape = sf::Sprite(m_texture);

	shape.setScale(m_size.x / shape.getGlobalBounds().width,
		m_size.y / shape.getGlobalBounds().height);
	shape.setPosition(m_location);

	return shape;
}

sf::Vector2f Button::getSize()const 
{
	return m_size;
}

sf::Vector2f Button::getLocation()const 
{
	return m_location;
}

void Button::setTexture(const sf::Texture& texture) 
{
	m_texture = texture;
}

void Button::setLocation(const sf::Vector2f& location)
{
	m_location = location;
}

sf::FloatRect Button::getGlobalBounds() const
{
	return createRect().getGlobalBounds();
}

sf::RectangleShape Button::createRect() const
{
	auto shape = sf::RectangleShape(m_size);
	shape.setPosition(m_location);

	return shape;
}
