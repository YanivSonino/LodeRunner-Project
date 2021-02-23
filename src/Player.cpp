#include "Player.h"
#include "GameController.h"

Player::Player() :m_life(3),m_score(0), DynamicObject(),m_keyPressed(sf::Keyboard::P), m_collectedCoin(false) {}

Player::Player(sf::Vector2f Size, sf::Vector2f Location, sf::Texture texture, char Shape, sf::Vector2f Direction,sf::Font font) :
	DynamicObject({ Size.x-2,Size.y }, Location, texture, Shape, Direction), m_life(3),m_score(0),m_font(font), m_collectedCoin(false),
	m_keyPressed(sf::Keyboard::P){}

void Player::moveBack()
{
	setLocation(getLastLcation());
}

void Player::draw(sf::RenderWindow& window) 
{
	window.draw(createShapeSprite());
}

void Player::lifeGift() 
{
	m_life++;
}

void Player::lifeLost() 
{
	m_life--;
}

void Player::scoreGift()
{
	m_score += 500;
}

void Player::initScore()
{
	m_score = 0;
}

int Player::getLife()const 
{
	return m_life;
}

int Player::getScore(const int& level)
{

	if (m_collectedCoin)
	{
		m_score += level * 2;
		m_collectedCoin = false;
	}
	return m_score;
}

void Player::BonusLevel(const int& level)
{
	m_score += level * 50;
}

void Player::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}

void Player::handleCollision(Player& gameObject){}

void Player::handleCollision(Coin& gameObject)
{
	m_collectedCoin = true; //coin collected
}

void Player::handleCollision(Ladder& gameObject)
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
	//Top collision
	else {
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

	//stabilize player on ladder
	if ((getDirection().y == 1 || getDirection().y == -1))
	{
		setLocation(sf::Vector2f(gameObject.getLocation().x, getLocation().y));
		setDirection({ 0,0 });
	}
}

void Player::handleCollision(Rope& gameObject)
{
	auto playerBounds = createRect().getGlobalBounds();
	auto ropeBounds = gameObject.getGlobalBounds();
	
	//getting only bottom collison with the rope
	if (playerBounds.top < ropeBounds.top + ropeBounds.height
		&& playerBounds.top + playerBounds.height > ropeBounds.top + ropeBounds.height
		&& playerBounds.left < ropeBounds.left + ropeBounds.width
		&& playerBounds.left + playerBounds.width > ropeBounds.left)
	{
		setOnRope(1);
		//stabilize player on rope
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


void Player::handleCollision(Enemy& gameObject)
{
	auto playerBounds = createRect().getGlobalBounds();
	auto enemyBounds = gameObject.getGlobalBounds();

	//enemy can kill the player only if enemy is not digged
	if (!gameObject.getDig())
	{
		m_isDisposed = true;
	}

	else 
	{
		//bottom collision
		if (playerBounds.top + playerBounds.height > enemyBounds.top
			&& playerBounds.top + playerBounds.height < enemyBounds.top + enemyBounds.height
			&& playerBounds.left < enemyBounds.left + enemyBounds.width
			&& playerBounds.left + playerBounds.width > enemyBounds.left)

		{
			setOnDigged(false);
			setFalling(0);
			setOnGround(1);
			setLastLocation({ playerBounds.left,enemyBounds.top - playerBounds.height });
			setLocation({ playerBounds.left,enemyBounds.top - playerBounds.height });

		}
	}
}

void Player::handleCollision(Gifts& gameObject)
{
	gameObject.handleCollision(*this);
}

void Player::handleCollision(Wall& gameObject)
{
	auto playerBounds = createRect().getGlobalBounds();
	auto wallBounds = gameObject.getGlobalBounds();

	//check if the wall is digged and no one inside of it
	if (gameObject.getDig() && !gameObject.getInsideDigged()) 
	{
		setOnDigged(true);
		return;
	}

	//check if some entity is digged in the wall
	if (gameObject.getInsideDigged()) 
		return;

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
		setLocation({wallBounds.left - playerBounds.width , playerBounds.top});
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

void Player::handleCollision(Board& gameObject)
{
	gameObject.handleCollision(*this);
}

void Player::dirToMove()
{

	static const
		std::initializer_list<std::pair<sf::Keyboard::Key, sf::Vector2f>>
		keyToVectorMapping =
	{
		{ sf::Keyboard::Right, { 1, 0 } },
		{ sf::Keyboard::Left , { -1, 0 } },
		{ sf::Keyboard::Up   , { 0, -1 } },
		{ sf::Keyboard::Down , { 0, 1 } },
	};

	setDirection({ 0 , 0 });
	for (const auto& pair : keyToVectorMapping)
	{
		if (sf::Keyboard::isKeyPressed(pair.first))
		{
			m_keyPressed = pair.first;
			setDirection(pair.second);
			
			//player can go up only when he is on ladder
			if (getDirection().y == -1 && !getOnLadder()) 
			{
				setDirection({ 0 , 0 });
			}
		}
	}
}

void Player::setDirectionDig(const sf::Vector2f&dir)
{
	m_dirToDig = dir;
}

sf::Vector2f Player::getDirectionDig()const 
{
	return m_dirToDig;
}

sf::Keyboard::Key Player::getKeyPressed()const 
{
	return m_keyPressed;
}

void Player::setKeyPressed(const sf::Keyboard::Key& key) 
{
	m_keyPressed = key;
}

void Player::move(GameController& controller)
{
	auto ShapeSpeed =100.f;

	dirToMove(); //Get Key to move

	if (getFalling()) //Check to activate gravity
	{
		setDirection({ 0,1 });
		ShapeSpeed = 300.f;
	}
	//move
	GameObject::setLocation(sf::Vector2f(getLocation().x + (getDirection().x * ShapeSpeed * controller.getDT()),
		getLocation().y + (getDirection().y * ShapeSpeed * controller.getDT())));
}

