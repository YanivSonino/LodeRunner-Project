#include <SFML/Graphics.hpp>
#pragma once

#define GRAY sf::Color(255, 255, 255, 100)

#define PLAYER_COLOR sf::Color::Red
#define PLAYER_SELECT_COLOR sf::Color(255, 102, 102)

#define ENEMY_COLOR sf::Color::Yellow
#define ENEMY_SELECT_COLOR sf::Color(255, 255, 102)

#define COIN_COLOR sf::Color::Magenta
#define COIN_SELECT_COLOR sf::Color(255, 102, 255)

#define WALL_COLOR sf::Color::Cyan
#define WALL_SELECT_COLOR sf::Color(153, 255, 255)

#define ROPE_COLOR sf::Color::Blue
#define ROPE_SELECT_COLOR sf::Color(102, 102, 255)

#define LADDER_COLOR sf::Color(255,128,0)
#define LADDER_SELECT_COLOR sf::Color(255,178,102)

#define DELETE_COLOR GRAY
#define DELETE_SELECT_COLOR sf::Color(224, 224, 224)

#define NEW_LEVEL_COLOR sf::Color(255,255,255)
#define NEW_LEVEL_SELECT_COLOR sf::Color(255,255,255)

#define SAVE_COLOR sf::Color::Green
#define SAVE_SELECT_COLOR sf::Color(102,255,102)

#define DARKGRAY sf::Color(64,64,64)




const float WIDTH = 1920.f;
const float HEIGHT = 1080.f;

const unsigned int NUM_OF_BUTTONS = 9;
const sf::Vector2f CharactersSize(142.222,80);
const sf::Vector2f GRIDSIZE(30, 30);
const sf::Vector2f LADDERSIZE(30, 30);
const float PIXEL = 30;
const int NUMOFSTATS = 3;
const int NUM_OF_MENU_BUTTONS = 2;
const int TEXTSIZE = 30;
const float SCORE_TEXT = 100;
const int MESSAGETEXTSIZE = 55;
const sf::Vector2i RESOLUTION(1920, 1080);
const sf::Vector2f RESOLUTION_SIZE(1920, 1080);
const sf::Vector2f SPACESCALE(0, 0);
const sf::Vector2f GRAYSCALE(0,0);
const sf::Vector2f PLAYERSCALE(7.3, 4.7);
const sf::Vector2f ENEMYSCALE(7.4, 4.9);
const sf::Vector2f WALLSCALE(5.3, 3.7);
const sf::Vector2f LADDERSCALE(35, 20);
const sf::Vector2f ROPESCALE(155, 85);
const sf::Vector2f COINSCALE(1.7, 1);
const sf::Vector2f STATSIZE(RESOLUTION.x / NUMOFSTATS, RESOLUTION.y - (RESOLUTION.y / 10));
const sf::Vector2f QUIT_BUTTON_SIZE(150,150);
const sf::Vector2f START_BUTTON_SIZE(300, 100);

const sf::Vector2f STARTLOCATION(RESOLUTION.x / 2.f- START_BUTTON_SIZE.x/2.f, RESOLUTION.y - 400);
const sf::Vector2f QUITLOCATION(RESOLUTION.x - QUIT_BUTTON_SIZE.x, RESOLUTION.y- QUIT_BUTTON_SIZE.y);

//char signed:
const char GIFT = '+';
const char PLAYER = '@';
const char ENEMY = '%';
const char WALL = '#';
const char COIN = '*';
const char LADDER = 'H';
const char ROPE = '-';
const char SPACE = ' ';
const size_t one = 1, two = 2;
