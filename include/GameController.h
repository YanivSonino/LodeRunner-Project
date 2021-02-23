#pragma once
#include "Timer.h"
#include "ConstEnemy.h"
#include "Board.h"
#include "Enemy.h"
#include "Player.h"
#include "RandomEnemy.h"
#include "Wall.h"
#include "Ladder.h"
#include "Rope.h"
#include "Coin.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Macros.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include <experimental/vector>
#include "GameStats.h"
#include "SmartEnemy.h"
#include "Menu.h"

class Player;
class GameStats;

class GameController {
private:

	//time handling
	Timer m_timer2;
	sf::Font m_font;
	sf::Clock m_timeClock;
	sf::Clock m_clock;
	sf::Time m_currentsecond;

	//game objects vectors
	std::vector<Wall*> m_wallPtrs;
	std::unique_ptr<Player> m_player;
	std::vector<GameStats> m_statsBoard;
	std::vector<std::unique_ptr<Enemy>>m_dynamicObject;
	std::unique_ptr<StaticObject> m_board;
	std::vector<std::vector<std::unique_ptr<StaticObject>>> m_staticObjects;
	std::vector<std::string> m_currMap;

	//menu and buttons
	Menu m_menu;
	Button m_musicMuteButton;
	Button m_soundMuteButton;

	//sounds and textures
	sf::SoundBuffer m_hitSound;
	sf::SoundBuffer m_coinSound;
	sf::SoundBuffer m_clapsSound;
	sf::SoundBuffer m_digSound;
	sf::SoundBuffer m_touchSound;
	sf::SoundBuffer m_losingSound;
	sf::SoundBuffer m_lifeTakeSound;
	sf::SoundBuffer m_enemyBornSound;
	sf::SoundBuffer m_TimeBonusSound;
	sf::SoundBuffer m_ScoreBonusSound;
	sf::Music m_menuMusic;
	sf::Music m_musicKit;
	sf::Sound m_sC;

	sf::Texture m_muteTexture;
	sf::Texture m_unmuteTexture;
	sf::Texture m_giftsTexture;
	sf::Texture m_playerTexture;
	sf::Texture m_wallTexture;
	sf::Texture m_coinTexture;
	sf::Texture m_ladderTexture;
	sf::Texture m_ropeTexture;
	sf::Texture m_boardTexture;
	sf::Texture m_enemyTexture;
	sf::Texture m_endScreen;
	sf::Texture m_endScreenT;
	sf::Texture m_soundTexture;
	sf::Texture m_muteSoundTexture;

	//size and locations
	sf::Vector2f m_playerLocation;
	sf::Vector2f m_size;
	sf::Vector2f m_mapsize;

	//map files
	std::ifstream m_file;

	//window object
	sf::RenderWindow m_window;

	int m_timer;
	float currentTime = 0;
	float m_DT;
	int m_currCoins;
	bool m_endGame;
	bool m_isMute;
	bool m_isMuteEffect;

	//functions to create game objects of different types
	std::unique_ptr<Enemy> createDynamicObject(const char&, const unsigned int&, const unsigned int&, const sf::Vector2f&, const sf::Texture&);
	std::unique_ptr<StaticObject> createStaticObject(const char&, const unsigned int&, const unsigned int&, const sf::Vector2f&, const sf::Texture&);

	//to find the right sprite for building objects functions
	sf::Texture findSprite(char);

	//handling game functions
	void initalizeMuteButton();
	void createObject(char, unsigned int, unsigned int);
	void restartLevel();
	void BuildStatsBar();
	void updateStats();
	void nextLevel();
	void clearObjects();
	void resetGame();
	bool m_gravityOn;
	void openGift();
	void Dig();
	void finishGame();
	void displayEndScreen();
	void muteSound(const bool&);
	void muteEffect(const bool&);
	void loadTexture();
	void loadBuffer();
	bool sameCenter(GameObject&);
	void BuildLevel();
	void updateDT();
	bool checkForPollEvents();
	void drawObjects();
	void MenuMode();
	void MenuSound();
	void MenuDisplay();
	void PlayMode();

	//checks collisions of objects
	void handleCollisions(DynamicObject&);
	
public:

	//get the delta time
	float getDT()const;

	//constructor
	GameController();

protected:

	int m_currLevel;

};