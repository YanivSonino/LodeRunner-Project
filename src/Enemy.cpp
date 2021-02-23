#include "Player.h"


Enemy::Enemy() : DynamicObject(), m_nextMove({ 0,0 }){}

Enemy::Enemy(const sf::Vector2f& Size, const sf::Vector2f& Location, const sf::Texture& texture, const char& Shape, const sf::Vector2f& Direction) :
	DynamicObject({Size.x-2,Size.y}, Location, texture, Shape, Direction) , m_nextMove({ 0,0}), m_isDiged(0) {}

sf::Vector2f Enemy::getPlayerLocation() const
{
	return m_playerLocation;
}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(createShapeSprite());
}

void Enemy::setPlayerLocation(const sf::Vector2f& playerLocation)
{
	m_playerLocation = playerLocation;
}

void Enemy::move(GameController& controller)
{
	//if enemy isn't inside a digged wall
	if (!m_isDiged) {

		auto ShapeSpeed = 80.f;

		//if cannot move
		if (!getLadderAbove() && getNextMove().y == -1 && !getLadderBenith()) 
		{
			setNextMove({ 0,0 });
		}

		//if falling
		if (getFalling()) 
		{
			setNextMove({ 0,1 });
			ShapeSpeed = 200.f;
		}

		GameObject::setLocation(sf::Vector2f(getLocation().x + (getNextMove().x * ShapeSpeed * controller.getDT()),
			getLocation().y + (getNextMove().y * ShapeSpeed * controller.getDT())));
	}
}

sf::Vector2f Enemy::getNextMove()
{
	return m_nextMove;
}

void Enemy::setNextMove(const sf::Vector2f& next)
{
	m_nextMove = next;
}

void Enemy::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}

void Enemy::handleCollision(Enemy& gameObject)
{
	//check if not the same object
	if (&gameObject == this) return;

	size_t i = 0.1;
	auto playerBounds = createRect().getGlobalBounds();
	auto enemyBounds = gameObject.getGlobalBounds();
	//if enemy is not inside a digged wall
	if (!gameObject.getDig()) {
		
		//bottom collision
		if (playerBounds.top + playerBounds.height > enemyBounds.top
			&& playerBounds.top + playerBounds.height < enemyBounds.top + enemyBounds.height
			&& playerBounds.left < enemyBounds.left + enemyBounds.width
			&& playerBounds.left + playerBounds.width > enemyBounds.left)
		{
			setLocation({ playerBounds.left,enemyBounds.top - playerBounds.height + i });
		}

		//Top collision
		else if (playerBounds.top < enemyBounds.top + enemyBounds.height
			&& playerBounds.top + playerBounds.height > enemyBounds.top + enemyBounds.height
			&& playerBounds.left < enemyBounds.left + enemyBounds.width
			&& playerBounds.left + playerBounds.width > enemyBounds.left)
		{
			setLocation({ playerBounds.left, enemyBounds.top + enemyBounds.height });
		}

		//Right Collision
		if (playerBounds.left < enemyBounds.left
			&& playerBounds.left + playerBounds.width < enemyBounds.left + enemyBounds.width
			&& playerBounds.top < enemyBounds.top + enemyBounds.height
			&& playerBounds.top + playerBounds.height > enemyBounds.top)
		{
			setLocation({ enemyBounds.left - playerBounds.width , playerBounds.top });
		}

		//Left collision
		else if (playerBounds.left > enemyBounds.left
			&& playerBounds.left + playerBounds.width > enemyBounds.left + enemyBounds.width
			&& playerBounds.top < enemyBounds.top + enemyBounds.height
			&& playerBounds.top + playerBounds.height > enemyBounds.top + 10)
		{
			setLocation({ enemyBounds.left + enemyBounds.width ,playerBounds.top });
		}

	}

	else {

		if (playerBounds.top + playerBounds.height > enemyBounds.top
			&& playerBounds.top + playerBounds.height < enemyBounds.top + enemyBounds.height
			&& playerBounds.left < enemyBounds.left + enemyBounds.width
			&& playerBounds.left + playerBounds.width > enemyBounds.left)
		{
			setOnGround(1);
			setLastLocation({ playerBounds.left,enemyBounds.top - playerBounds.height });
		}
	}
}

void Enemy::handleCollision(Gifts& gameObject){}

void Enemy::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}

void Enemy::handleCollision(Coin& gameObject){}

void Enemy::handleCollision(Ladder& gameObject)
{
	auto playerBounds = createRect().getGlobalBounds();
	auto ladderBounds = gameObject.getGlobalBounds();

	//bottom collision
	if (playerBounds.top + playerBounds.height > ladderBounds.top
		&& playerBounds.top + playerBounds.height < ladderBounds.top + ladderBounds.height
		&& playerBounds.left < ladderBounds.left + ladderBounds.width
		&& playerBounds.left + playerBounds.width > ladderBounds.left)
	{
		if (!getOnLadder()) 
		{
			setOnLadder(1);
			setFalling(false);
		}
	}

	
	else 
	{
		//Top collision
		if (playerBounds.top < ladderBounds.top + ladderBounds.height
			&& playerBounds.top + playerBounds.height > ladderBounds.top + ladderBounds.height
			&& playerBounds.left < ladderBounds.left + ladderBounds.width
			&& playerBounds.left + playerBounds.width > ladderBounds.left)
		{
			setLadderAbove(1);
			setFalling(false);
		}
	}

	setOnLadder(1);

	//stabilize enemy on ladder
	if ((getNextMove().y == 1 || getNextMove().y == -1)) {
		setLocation(sf::Vector2f(gameObject.getLocation().x, getLocation().y));
		setDirection({ 0,0 });
	}

}

void Enemy::handleCollision(Rope& gameObject)
{
	auto playerBounds = createRect().getGlobalBounds();
	auto ropeBounds = gameObject.getGlobalBounds();

	//bottom collision
	if (playerBounds.top < ropeBounds.top + ropeBounds.height
		&& playerBounds.top + playerBounds.height > ropeBounds.top + ropeBounds.height
		&& playerBounds.left < ropeBounds.left + ropeBounds.width
		&& playerBounds.left + playerBounds.width > ropeBounds.left)
	{
		setOnRope(1);
		//if enemy able to move
		if (!getFalling() && getDirection().y == 1 && !getOnLadder())
		{
			setOnRope(0);
			setLocation({ getLocation().x, getLocation().y + 15 });
			return;
		}

		setFalling(0);
		setDirection({ 0,0 });
	}

	else setOnRope(0);
}

void Enemy::setDig(const bool& diged)
{
	m_isDiged = diged;
}

bool Enemy::getDig()const
{
	return m_isDiged;
}

void Enemy::handleCollision(Wall& gameObject)
{

	auto playerBounds = createRect().getGlobalBounds();
	auto wallBounds = gameObject.getGlobalBounds();
	
	//if player is not inside a digged wall
	if (gameObject.getDig() && !gameObject.getInsideDigged()) 
	{
		setLocation({ wallBounds.left ,wallBounds.top });
		m_isDiged = 1;
		gameObject.setInsideDigged(1);
		return;
	}

	gameObject.setInsideDigged(0);
	//if enemy is inside a digged wall
	if (m_isDiged)
	{
		return;
	}

	//bottom collision
	if (playerBounds.top + playerBounds.height > wallBounds.top
		&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
		&& playerBounds.left < wallBounds.left + wallBounds.width
		&& playerBounds.left + playerBounds.width > wallBounds.left)

	{
		setFalling(0);
		setOnGround(1);
		setLastLocation({ playerBounds.left,wallBounds.top - playerBounds.height });
		setLocation({ playerBounds.left,wallBounds.top - playerBounds.height });
	}

	//Top collision
	else if (playerBounds.top < wallBounds.top + wallBounds.height
		&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
		&& playerBounds.left < wallBounds.left + wallBounds.width
		&& playerBounds.left + playerBounds.width > wallBounds.left)
	{

		setLocation({ playerBounds.left, wallBounds.top + wallBounds.height });
	}

	//Right Collision
	if (playerBounds.left < wallBounds.left
		&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
		&& playerBounds.top < wallBounds.top + wallBounds.height
		&& playerBounds.top + playerBounds.height > wallBounds.top + 10)
	{
		setLocation({ wallBounds.left - playerBounds.width , playerBounds.top });
	}

	//Left collision
	else if (playerBounds.left > wallBounds.left
		&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
		&& playerBounds.top < wallBounds.top + wallBounds.height
		&& playerBounds.top + playerBounds.height > wallBounds.top + 10)
	{
		setLocation({ wallBounds.left + wallBounds.width ,playerBounds.top });
	}
}

void Enemy::handleCollision(Board& gameObject){}