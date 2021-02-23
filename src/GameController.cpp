#include "GameController.h"

GameController::GameController() :
    m_size(0, 0), m_window(sf::VideoMode(RESOLUTION.x, RESOLUTION.y), "LodeRunner",sf::Style::Fullscreen), 
    m_playerLocation({ 0,0 }), m_currLevel(0), m_currCoins(0), m_endGame(false), m_musicMuteButton(m_muteTexture, { 0,0 }, { 90,90 }), m_isMute(true), m_isMuteEffect(true),
    m_soundMuteButton(m_muteTexture, { 0,0 }, { -90,90 })
{

    //init font and load it to timer
    m_font.loadFromFile("C:/Windows/Fonts/Impact.ttf");
    m_timer2.setFont(m_font);

    //open the maps file.
    m_file.open("Board.txt");
    srand(time(NULL));

    
    loadTexture();
    loadBuffer();
    //make smart ptrs to player and board
    m_board = std::make_unique<Board>(sf::Vector2f(RESOLUTION.x, RESOLUTION.y), m_boardTexture);
    m_player = std::make_unique<Player>(sf::Vector2f(PIXEL, PIXEL), sf::Vector2f(0, 0), m_playerTexture, PLAYER, sf::Vector2f(0, 0), m_font);

    
    BuildLevel();
    MenuSound();
    initalizeMuteButton();
    MenuMode();
}

bool GameController::checkForPollEvents() 
{
    //function is responsable for key pressed events and 
    //windows closing.
    for (auto event = sf::Event(); m_window.pollEvent(event); )
    {

        auto event2 = sf::Event();
        m_window.pollEvent(event2);

        switch (event.type)
        {
        //for closing window
        case sf::Event::Closed:
            m_menuMusic.setLoop(false);
            m_window.close();
            return true;

        //keyboard buttons for digging or sucide.
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Q) 
            {
                m_player->setKeyPressed(event.key.code);
                m_player->setDirectionDig({ -1,0 });
            }
            if (event.key.code == sf::Keyboard::E) 
            {
                m_player->setKeyPressed(event.key.code);
                m_player->setDirectionDig({ 1,0 });
            }
            if (event.key.code == sf::Keyboard::Z) 
            {
                m_player->setKeyPressed(event.key.code);
                m_player->setDirectionDig({ -1,0 });
            }
            if (event.key.code == sf::Keyboard::X) 
            {
                m_player->setKeyPressed(event.key.code);
                m_player->setDirectionDig({ 1,0 });
            }
            if (event.key.code == sf::Keyboard::K ) 
            {
                m_player->setDisposed(1);
            }
            if (event.key.code == sf::Keyboard::Escape)
            {
                resetGame();
                return true;
            }
            break;

        
        case sf::Event::MouseButtonReleased:

            auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
            //for mute button
            switch (event.mouseButton.button) 
            {
            case sf::Mouse::Button::Left:
                if (m_musicMuteButton.getGlobalBounds().contains(location)) 
                {
                    muteSound(false);
                }
                if (m_soundMuteButton.getGlobalBounds().contains(location))
                {
                    muteEffect(false);
                }
            }
        }
    }  
}

void GameController::drawObjects()
{
    /// <summary>
    ///  clears the screen and draws all object.
    /// </summary>
   
    m_window.clear();
    m_timer2.draw(m_window);
    m_board->draw(m_window);
    
    //static objects draw
    for (auto i = 0; i < m_staticObjects.size(); i++) {
        for (auto j = 0; j < m_staticObjects[i].size(); j++) {
            if(m_staticObjects[i][j])
            m_staticObjects[i][j]->draw(m_window);
        }
    }

    //draw status bar
    for (auto i = 0; i < m_statsBoard.size(); i++) {
        m_statsBoard[i].draw(m_window);
    }

    m_player->draw(m_window);

    //draw enemies
    for (auto i = 0; i < m_dynamicObject.size(); i++)
    {
        m_dynamicObject[i]->draw(m_window);
    }
    m_musicMuteButton.draw(m_window);
    m_soundMuteButton.draw(m_window);
    m_window.display();
}

void GameController::MenuMode()
{
    //function is responsable for key pressed events and 
    //windows closing.
    while (m_window.isOpen())
    {
       
        MenuDisplay();

        auto touch = true;

        for (auto event = sf::Event(); m_window.pollEvent(event); )
        {
            
            switch (event.type)
            {

            case sf::Event::Closed:
                m_window.close();
                return;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    m_window.close();
                    return;
                }
                if (event.key.code == sf::Keyboard::Enter)
                {
                    m_sC.setBuffer(m_touchSound);
                    m_sC.play();
                    PlayMode();
                }
            case sf::Event::MouseButtonReleased:
                auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                switch (event.mouseButton.button) {
                case sf::Mouse::Button::Left:
                    if (m_menu.getGlobalStart().contains(location))
                    {
                        m_sC.setBuffer(m_touchSound);
                        m_sC.play();
                        PlayMode();
                    }
                    else if (m_menu.getGlobalQuit().contains(location))
                    {
                        m_menuMusic.setLoop(false);
                        m_window.close();
                        return;
                    }
                    else if (m_musicMuteButton.getGlobalBounds().contains(location)) {
                        muteSound(true);
                    }
                    else if (m_soundMuteButton.getGlobalBounds().contains(location))
                    {
                        muteEffect(true);
                    }

                }

            }

            
            if (m_menu.getGlobalStart().contains(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y)) {
                m_menu.ChangeStartMarkedSpirte();
            }
            else {
                m_menu.ChangeStartSpirte();
            }
            if (m_menu.getGlobalQuit().contains(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y)) {
                m_menu.ChangeQuitMarkedSpirte();
            }
            else {
                m_menu.ChangeQuitSpirte();
            }   
        }

    }
}
void GameController::MenuSound() {
    m_sC.setVolume(60);
    m_menuMusic.setVolume(60);
    m_menuMusic.setLoop(true);
    m_musicKit.setVolume(15);
    m_musicKit.setLoop(true);
    m_menuMusic.play();

}


void GameController::MenuDisplay() {
    m_window.clear();
    m_menu.draw(m_window);
    m_musicMuteButton.draw(m_window);
    m_soundMuteButton.draw(m_window);
    m_window.display();
}

void GameController::PlayMode()
{
    m_menuMusic.stop();
    if(m_isMute)
    m_musicKit.play();

    auto moved = false;
    m_currentsecond = m_timeClock.restart();

    while (m_window.isOpen())
    {
        if (checkForPollEvents()) {
            break;
        }

        updateDT();
        updateStats();
        drawObjects();

        for (int i = 0; i < m_wallPtrs.size(); i++)
        {
            m_wallPtrs[i]->reBuild();

            if (!m_wallPtrs[i]->getDig() && m_wallPtrs[i]->checkCenter(m_player->getGlobalBounds())) 
            {
                drawObjects();
                m_player->setDisposed(true);
                break;
            }
        }

        if (moved) {
            if ((int)m_timeClock.getElapsedTime().asSeconds() != (int)m_currentsecond.asSeconds()) {
                m_currentsecond = m_timeClock.restart();
                m_timer2.UpdateTimer(m_timer2.getTimer() - (int)m_currentsecond.asSeconds());
            }

            if (m_timer2.getTimer() == 0) {
                m_player->setDisposed(true);
                m_currentsecond = m_timeClock.restart();
                //continue;
            }
        }
        if (m_player->isDisposed())
        {
            m_sC.setBuffer(m_hitSound);
            m_sC.play();
            m_player->lifeLost();

            if (m_player->getLife() == 0)
            {
                resetGame();
                break;
            }
            else 
            {
                restartLevel();
                m_currentsecond = m_timeClock.restart();
            }
            moved = false;
        }

        m_playerLocation = m_player->getLocation();
        m_player->move(*this);

        if (m_player->getDirection() != sf::Vector2f(0, 0)) 
        {
            moved = true;
        }
        handleCollisions(*m_player);

        if (m_player->getKeyPressed() == sf::Keyboard::Q || m_player->getKeyPressed() == sf::Keyboard::E ||
            m_player->getKeyPressed() == sf::Keyboard::X || m_player->getKeyPressed() == sf::Keyboard::Z) 
        {
            Dig();
        }
        if (moved)
        {
            for (auto& movable : m_dynamicObject)
            {
                movable->setPlayerLocation(m_playerLocation);
                movable->nextMove();
                movable->move(*this);
                handleCollisions(*movable);
                if (movable->checkCollision(m_player->getGlobalBounds())) 
                {
                    m_player->handleCollision(*movable);
                }
                for (auto& movable2 : m_dynamicObject) 
                {
                    if (movable->checkCollision(movable2->getGlobalBounds())) 
                    {
                        movable->handleCollision(*movable2);
                    }
                }
            }
        }

        if (m_currCoins == 0) {
            drawObjects();
            nextLevel();
            moved = false;
            if (m_endGame)
            {
                m_endGame = false;
                finishGame();

                if (m_isMute)
                    m_menuMusic.play();
                break;
            }
        }
    }

}




   
void GameController::BuildLevel()
{
    m_currLevel++;
    int levelTime;
    //get boundings from file
    m_file >> m_size.y >> m_size.x >> levelTime;

    m_timer2.setGenralTime(levelTime);
    m_timer2.UpdateTimer(levelTime);
    //check if there are more maps
    m_file.get();

    //run on each row and copy
    m_board = std::make_unique<Board>(sf::Vector2f(m_size.x * PIXEL, m_size.y * PIXEL),m_boardTexture);
    m_timer2.setLocation({ m_board->getGlobalBounds().left +
       (m_board->getGlobalBounds().width / 2) - PIXEL ,  m_board->getGlobalBounds().top - PIXEL });
    if (m_file.eof()) 
    {
        displayEndScreen();
        return;
    }
    for (unsigned int i = 0; i < m_size.y; i++)
    {
        m_staticObjects.push_back({});
        //to get each line
        auto line = std::string();
        std::getline(m_file, line);
        m_currMap.push_back(line);
        for (unsigned int j = 0;j < m_size.x;j++)
        {
            if (line[j] == PLAYER) {
                m_player->setLocation(sf::Vector2f(((RESOLUTION.x - m_size.x * PIXEL) / 2) + (j * PIXEL),
                    ((RESOLUTION.y - m_size.y * PIXEL) / 2) + (i * PIXEL)));
                m_staticObjects[i].push_back(nullptr);
            }

            else
            {
                createObject(line[j], i, j);
            }

        }
        
    }
    BuildStatsBar();
    //std::cout << m_coinsCounter << std::endl;
}

void GameController::updateDT()
{

    m_DT = m_clock.restart().asSeconds();

    if (m_DT > 1 / 20.f) {
        m_DT = 1 / 20.f;
    }   
}

 std::unique_ptr<Enemy> GameController::createDynamicObject(const char& type, const unsigned int& i, const unsigned int& j, const sf::Vector2f& size, const sf::Texture& texture)
{
    switch (type) {
    case ENEMY:
        switch (rand() % 3) {
        case 0:
            return std::make_unique<RandomEnemy>(sf::Vector2f(PIXEL, PIXEL), sf::Vector2f(((RESOLUTION.x - size.x * PIXEL) / 2) + (j * PIXEL),
                ((RESOLUTION.y - size.y * PIXEL) / 2) + (i * PIXEL)), texture, ENEMY, sf::Vector2f(0, 0));
        case 1:
            return std::make_unique<ConstEnemy>(sf::Vector2f(PIXEL, PIXEL), sf::Vector2f(((RESOLUTION.x - size.x * PIXEL) / 2) + (j * PIXEL),
                ((RESOLUTION.y - size.y * PIXEL) / 2) + (i * PIXEL)), texture, ENEMY, sf::Vector2f(0, 0));
        case 2:
            return std::make_unique<SmartEnemy>(sf::Vector2f(PIXEL, PIXEL), sf::Vector2f(((RESOLUTION.x - size.x * PIXEL) / 2) + (j * PIXEL),
                ((RESOLUTION.y - size.y * PIXEL) / 2) + (i * PIXEL)), texture, ENEMY, sf::Vector2f(0, 0));
        }
    }
    return nullptr;

}

std::unique_ptr<StaticObject> GameController::createStaticObject(const char& type, const unsigned int& i, const unsigned int& j, const sf::Vector2f& size, const sf::Texture& texture)
{
    switch (type)
    {
    case WALL:
        return std::make_unique<Wall>(sf::Vector2f(((RESOLUTION.x - size.x * PIXEL) / 2) + (j * PIXEL),
            ((RESOLUTION.y - size.y * 29.9) / 2) + (i * PIXEL)),texture);

    case COIN:
        return std::make_unique<Coin>(sf::Vector2f(((RESOLUTION.x - size.x * PIXEL) / 2) + (j * PIXEL),
            ((RESOLUTION.y - size.y * PIXEL) / 2) + (i * PIXEL)), texture);
    case LADDER:
        return std::make_unique<Ladder>(sf::Vector2f(((RESOLUTION.x - size.x * PIXEL) / 2) + (j * PIXEL),
            ((RESOLUTION.y - size.y * PIXEL) / 2) + (i * PIXEL)), texture);
    case ROPE:
        return std::make_unique<Rope>(sf::Vector2f(((RESOLUTION.x - size.x * PIXEL) / 2) + (j * PIXEL),
            ((RESOLUTION.y - size.y * PIXEL + 30 ) / 2) + (i * PIXEL)),texture);
    case GIFT:
        return std::make_unique<Gifts>(sf::Vector2f(((RESOLUTION.x - size.x * PIXEL + 10) / 2) + (j * PIXEL),
            ((RESOLUTION.y - size.y * PIXEL + 10) / 2) + (i * PIXEL)), texture);
    }
    return nullptr;
}



void GameController::initalizeMuteButton()
{
    m_musicMuteButton.setTexture(m_muteTexture);
    m_musicMuteButton.setLocation({RESOLUTION_SIZE.x - m_musicMuteButton.getSize().x -PIXEL ,90});

    m_soundMuteButton.setTexture(m_soundTexture);
    m_soundMuteButton.setLocation({ RESOLUTION_SIZE.x - PIXEL  ,m_musicMuteButton.getSize().y + 120 });
}

void GameController::createObject(char type, unsigned int i, unsigned int j)
{
    std::unique_ptr<Enemy> movable = createDynamicObject(type, i, j, m_size,findSprite(type));
    if (movable)
    {
        m_dynamicObject.push_back(std::move(movable));
        m_staticObjects[i].push_back(nullptr);
        return;
    }

    std::unique_ptr<StaticObject> unmovable = createStaticObject(type, i, j, m_size,findSprite(type));
    {
        switch (type) {
        case WALL:
            m_staticObjects[i].push_back(std::move(unmovable));
            break;
        case LADDER:
            m_staticObjects[i].push_back(std::move(unmovable));
            break;
        case COIN:
            m_currCoins++;
            m_staticObjects[i].push_back(std::move(unmovable));
            break;
        case ROPE:
            m_staticObjects[i].push_back(std::move(unmovable));
            break;
        case GIFT:
            m_staticObjects[i].push_back(std::move(unmovable));
            break;
        case SPACE:
            m_staticObjects[i].push_back(nullptr);
        }
    
        return;

    }

    std::cerr << "Unrecognized char in the file: " << type << std::endl;
    exit(EXIT_FAILURE);
}

float GameController::getDT() const
{
    return m_DT;
}



void GameController::loadTexture()
{
    m_playerTexture.loadFromFile("Player.PNG");
    m_wallTexture.loadFromFile("Wall.PNG");
    m_coinTexture.loadFromFile("Coin.PNG");
    m_ropeTexture.loadFromFile("Rope.PNG");
    m_ladderTexture.loadFromFile("Ladder.PNG");
    m_boardTexture.loadFromFile("Board.jpg");
    m_enemyTexture.loadFromFile("Enemy.PNG");
    m_giftsTexture.loadFromFile("Gifts.PNG");
    m_endScreen.loadFromFile("Winner.PNG");
    m_endScreenT.loadFromFile("WinnerT.PNG");

    m_muteTexture.loadFromFile("Mute.PNG");
    m_unmuteTexture.loadFromFile("Unmute.PNG");

    m_soundTexture.loadFromFile("Sound.PNG");
    m_muteSoundTexture.loadFromFile("MuteSound.PNG");
}

void GameController::loadBuffer()
{
    m_coinSound.loadFromFile("coin1.ogg");
    m_clapsSound.loadFromFile("claps.WAV");
    m_digSound.loadFromFile("dig.WAV");
    m_musicKit.openFromFile("rythem.ogg");
    m_touchSound.loadFromFile("touch.WAV");
    m_lifeTakeSound.loadFromFile("LifeTake.ogg");
    m_TimeBonusSound.loadFromFile("TimeBonus.ogg");
    m_ScoreBonusSound.loadFromFile("ScoreBonus.ogg");
    m_enemyBornSound.loadFromFile("EnemyBorn.ogg");
    m_menuMusic.openFromFile("menuSound.WAV");
    m_losingSound.loadFromFile("losingSound.ogg");
    m_hitSound.loadFromFile("hit.ogg");
}

void GameController::handleCollisions(DynamicObject& gameObject)
{
    int objectIndexX,objectIndexY ;
    
    int playerIndexX = ((gameObject.getGlobalBounds().left + gameObject.getGlobalBounds().width / 2)- ((RESOLUTION.x - m_board->getGlobalBounds().width) / 2 )) / PIXEL;
    int playerIndexY = ((gameObject.getGlobalBounds().top + gameObject.getGlobalBounds().height / 2) - ((RESOLUTION.y - m_board->getGlobalBounds().height) / 2)) / PIXEL;
    gameObject.init();
    bool touchObject = 0;
    gameObject.setOnLadder(false);
    for (objectIndexY = playerIndexY - 1; objectIndexY > -1 && objectIndexY < m_staticObjects.size() && (objectIndexY < playerIndexY + 2); objectIndexY++) {
        for (objectIndexX = playerIndexX - 1; objectIndexX > -1 && objectIndexX < m_staticObjects[objectIndexY].size() && (objectIndexX < playerIndexX + 2); objectIndexX++) {

            if ((m_staticObjects[objectIndexY][objectIndexX]) && gameObject.checkCollision(m_staticObjects[objectIndexY][objectIndexX]->getGlobalBounds())) {
                gameObject.handleCollision(*m_staticObjects[objectIndexY][objectIndexX]);
                if (!gameObject.getOnDigged())
                touchObject = 1;
                if (m_staticObjects[objectIndexY][objectIndexX]->isDisposed()) { 
                    if (m_staticObjects[objectIndexY][objectIndexX]->getShape() == COIN) {
                        m_sC.setBuffer(m_coinSound);
                        m_sC.play();
                        m_currCoins--;
                    }
                    if (m_staticObjects[objectIndexY][objectIndexX]->getShape() == GIFT) {
                        openGift();
                    }
                    m_staticObjects[objectIndexY][objectIndexX].reset();
                }
            
            }
            
        }
    }
    gameObject.handleCollision(*m_board);
   

    if (
        playerIndexY > - 2 && playerIndexY + 1  < m_staticObjects.size() &&
        playerIndexX > -1 && playerIndexX < m_staticObjects[playerIndexY + 1].size() &&
        m_staticObjects[playerIndexY + 1][playerIndexX] &&
        m_staticObjects[playerIndexY + 1][playerIndexX]->getShape() == LADDER)
        gameObject.setLadderBenith(true);
    else gameObject.setLadderBenith(false);
    if (
        playerIndexY > 0 && playerIndexY - 1 < m_staticObjects.size() &&
        playerIndexX > -1 && playerIndexX < m_staticObjects[playerIndexY - 1].size() &&
        m_staticObjects[playerIndexY - 1][playerIndexX] &&
        m_staticObjects[playerIndexY - 1][playerIndexX]->getShape() == LADDER)
        gameObject.setLadderAbove(true);
    else gameObject.setLadderAbove(false);
    if (!touchObject && !gameObject.getOnGround())
        gameObject.setFalling(1);
    
}

bool GameController::sameCenter(GameObject& gameObject)
{

        if (gameObject.checkCenter(m_board->getGlobalBounds()) && m_board->getShape() == 'H')
        {
            return 0;
        }
    
    return 1;

}



sf::Texture GameController::findSprite(char type) {
    switch (type)
    {
    case PLAYER:
        return m_playerTexture;
    case WALL:
        return m_wallTexture;
    case COIN:
         return m_coinTexture;
    case LADDER:
        return m_ladderTexture;
    case ROPE:
        return m_ropeTexture;
    case ENEMY:
        return m_enemyTexture;
    case GIFT:
        return m_giftsTexture;
    }
    return m_boardTexture;
}


void GameController::restartLevel() 
{
    m_board.reset();
    m_dynamicObject.clear();
    m_timer2.UpdateTimer(m_timer2.getGenralTime());
    m_player->setDisposed(false);
    m_staticObjects.clear();
    m_wallPtrs.clear();
    
    m_currCoins = 0;
    m_board = std::make_unique<Board>(sf::Vector2f(m_size.x * PIXEL, m_size.y * PIXEL), m_boardTexture);
    for (int i = 0; i < m_size.y; i++) {
        m_staticObjects.push_back({});
        for (unsigned int j = 0; j < m_size.x; j++)
        {
            if (m_currMap[i][j] == PLAYER) {
                m_player->setLocation(sf::Vector2f(((RESOLUTION.x - m_size.x * PIXEL) / 2) + (j * PIXEL),
                    ((RESOLUTION.y - m_size.y * PIXEL) / 2) + (i * PIXEL)));
                m_staticObjects[i].push_back(nullptr);
            }

            else
            {
                createObject(m_currMap[i][j], i, j);
            }
        }
    }

    
}

void GameController::BuildStatsBar()
{
    auto a = GRAY;
    std::string b;

    for (auto i = 0; i < NUMOFSTATS; i++) {
        switch (i) {
        case(0):
            b = "LIVES:";
            m_statsBoard.push_back(GameStats(b, 3, i, a, m_player->getLife(), m_font));
            break;
        case(1):
            b = "LEVEL:";
            m_statsBoard.push_back(GameStats(b, 3, i, a, m_currLevel, m_font));
            break;
        case(2):
            b = "SCORE:";
            m_statsBoard.push_back(GameStats(b, 3, i, a, m_player->getScore(m_currLevel), m_font));
            break;

        }

        
    }

}

void GameController::updateStats() {



    for (auto i = 0; i < NUMOFSTATS; i++) {
        switch (i) {
        case(0):
            m_statsBoard[i].setStat(m_player->getLife());
            break;
        case(1):
            m_statsBoard[i].setStat(m_currLevel);
            break;
        case(2):
            m_statsBoard[i].setStat(m_player->getScore(m_currLevel));
            break;

        }


    }
}

void GameController::nextLevel()
{
    m_player->BonusLevel(m_currLevel);
    clearObjects();
    BuildLevel();
}
void GameController::clearObjects() {
    m_dynamicObject.clear();
    m_board.reset();
    m_statsBoard.clear();
    m_staticObjects.clear();
    m_currMap.clear();
    m_wallPtrs.clear();

} 

void GameController::resetGame() 
{
    m_musicKit.stop();
    m_sC.setBuffer(m_losingSound);
    m_sC.play();
    m_player.reset();
    m_player = std::make_unique<Player>(sf::Vector2f(PIXEL, PIXEL), sf::Vector2f(0, 0), m_playerTexture, PLAYER, sf::Vector2f(0, 0), m_font);
    clearObjects();
    m_currCoins = 0;
    m_file.close();
    m_file.open("Board.txt");
    m_currLevel = 0;
    BuildLevel();
    
    sf::sleep(sf::milliseconds(900)); 
    if (m_isMute) {
        m_menuMusic.play();
    }
}

void GameController::openGift() {
    switch (rand() % 4) {
    case 0:
        m_sC.setBuffer(m_TimeBonusSound);
        m_sC.play();
        m_timer2.UpdateTimer(m_timer2.getGenralTime() + (rand() % 20 + 10));
        break;
    case 1:
        m_sC.setBuffer(m_lifeTakeSound);
        m_sC.play();
        m_player->lifeGift();
        break;
    case 2:
        m_sC.setBuffer(m_ScoreBonusSound);
        m_sC.play();
        m_player->scoreGift();
        break;
    case 3:
        m_sC.setBuffer(m_enemyBornSound);
        m_sC.play();
        std::unique_ptr<Enemy> movable = createDynamicObject(ENEMY,
            1, 3, m_size, findSprite(ENEMY));
        m_dynamicObject.push_back(std::move(movable));
        break;

    }
}

void GameController::Dig()
{
    auto dig = false;
    int objectIndexX, objectIndexY;
    int playerIndexX = ((m_player->getGlobalBounds().left + m_player->getGlobalBounds().width / 2) - ((RESOLUTION.x - m_board->getGlobalBounds().width) / 2)) / PIXEL;
    int playerIndexY = ((m_player->getGlobalBounds().top + m_player->getGlobalBounds().height / 2) - ((RESOLUTION.y - m_board->getGlobalBounds().height) / 2)) / PIXEL;

    if (m_player->getDirectionDig().x == 1) {
        if (
            playerIndexY > -1 && playerIndexY < m_staticObjects.size() -1 &&
            playerIndexX > -1 && playerIndexX < m_staticObjects[playerIndexY].size() - 1 &&
            /*!m_giftsObjects[playerIndexY][playerIndexX + 1] &&*/
            m_staticObjects[playerIndexY + 1][playerIndexX + 1]
            && m_staticObjects[playerIndexY + 1][playerIndexX + 1]->getShape() == WALL)
        {
           
            if (!m_staticObjects[playerIndexY][playerIndexX + 1]) {
                dig = true;
            }   

            else if (m_staticObjects[playerIndexY][playerIndexX + 1]->getShape() == WALL) {
                StaticObject* object = m_staticObjects[playerIndexY][playerIndexX + 1].release();
                Wall* wall = dynamic_cast<Wall*>(object);
                if (wall->getDig()) {
                    dig = true;

                }
                m_staticObjects[playerIndexY][playerIndexX + 1] = std::unique_ptr<StaticObject>(wall);
            }
            if (dig) {
                StaticObject* object = m_staticObjects[playerIndexY + 1][playerIndexX + 1].release();
                Wall* wall = dynamic_cast<Wall*>(object);
                wall->setDig(true);
                wall->startTimer();
                m_wallPtrs.push_back(wall);
                m_staticObjects[playerIndexY + 1][playerIndexX + 1] = std::unique_ptr<StaticObject>(wall);
                m_sC.setBuffer(m_digSound);
                m_sC.play();
            }

        }
    }
    else if (m_player->getDirectionDig().x == -1) {
        if (
            playerIndexY > -1 && playerIndexY < m_staticObjects.size() - 1 &&
            playerIndexX > -2 && playerIndexX < m_staticObjects[playerIndexY].size()-1&&
             m_staticObjects[playerIndexY+1][playerIndexX - 1]
            && m_staticObjects[playerIndexY + 1][playerIndexX - 1]->getShape() == WALL) 
        {
            if (!m_staticObjects[playerIndexY][playerIndexX - 1]) {
                dig = true;
            }
            else if (m_staticObjects[playerIndexY][playerIndexX - 1]->getShape() == WALL) {
                StaticObject* object = m_staticObjects[playerIndexY][playerIndexX - 1].release();
                Wall* wall = dynamic_cast<Wall*>(object);
                if (wall->getDig()) {
                    dig = true;
                }
                m_staticObjects[playerIndexY][playerIndexX - 1] = std::unique_ptr<StaticObject>(wall);
            }
            if (dig) {
                StaticObject* object = m_staticObjects[playerIndexY + 1][playerIndexX - 1].release();
                Wall* wall = dynamic_cast<Wall*>(object);
                wall->setDig(true);
                wall->startTimer();
                m_wallPtrs.push_back(wall);
                m_staticObjects[playerIndexY + 1][playerIndexX - 1] = std::unique_ptr<StaticObject>(wall);
                m_sC.setBuffer(m_digSound);
                m_sC.play();
            }  

        }
    }
    if (dig) {
        m_sC.setBuffer(m_digSound);
        m_sC.play();
    }

    m_player->setKeyPressed(sf::Keyboard::P);

}

void GameController::finishGame()
{
    m_player.reset();
    m_player = std::make_unique<Player>(sf::Vector2f(PIXEL, PIXEL), sf::Vector2f(0, 0), m_playerTexture, PLAYER, sf::Vector2f(0, 0), m_font);
    clearObjects();
    m_currLevel = 0;
    BuildLevel();
}

void GameController::displayEndScreen()
{

    sf::Sprite endScreenSprite(m_endScreen);
    sf::Sprite endScreenSprite2(m_endScreenT);

    std::string my_score = "Score: ";
    my_score += std::to_string(m_player->getScore(m_currLevel));
    sf::Text score(my_score, m_font, SCORE_TEXT);
    score.setColor(sf::Color::White);
    score.setPosition(RESOLUTION_SIZE.x / 2 - SCORE_TEXT * 2, RESOLUTION_SIZE.y * 1 / 3.f);

    sf::Time winning;
    sf::Clock clock;

    m_musicKit.stop();
    m_sC.setBuffer(m_clapsSound);
    m_sC.play();

    clock.restart();

    while (((int)clock.getElapsedTime().asSeconds() - (int)winning.asSeconds() != 4))
    {
        m_window.clear();
        m_window.draw(endScreenSprite);
        m_window.draw(score);
        m_window.display();
        sf::sleep(sf::milliseconds(500));
        m_window.clear();
        m_window.draw(endScreenSprite2);
        m_window.draw(score);
        m_window.display();
        sf::sleep(sf::milliseconds(500));

    }
    m_file.clear();
    m_file.seekg(0);
    m_endGame = true;
}

void GameController::muteSound(const bool& menu)
{
    
    if (m_isMute) {
        if(!menu)
        m_musicKit.pause();
        else
        m_menuMusic.pause();
        m_musicMuteButton.setTexture(m_unmuteTexture);
        m_isMute = false;
    }
    else {
        if (!menu)
        m_musicKit.play();
        else
        m_menuMusic.play();
        m_musicMuteButton.setTexture(m_muteTexture);
        m_isMute = true;
    }
}
void GameController::muteEffect(const bool& menu)
{

    if (m_isMuteEffect) {
        if (!menu)
            m_sC.setVolume(0);
        else
            m_sC.setVolume(0);
        m_soundMuteButton.setTexture(m_muteSoundTexture);
        m_isMuteEffect = false;
    }
    else {
        if (!menu)
            m_sC.setVolume(60);
        else
            m_sC.setVolume(60);
        m_soundMuteButton.setTexture(m_soundTexture);
        m_isMuteEffect = true;
    }
}