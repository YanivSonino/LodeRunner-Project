ex: 
	ex05

Names:
	 Gal Meir Malka , and Yaniv Sonino

Description:

	Lode Runner Game - The player needs to collect all diamonds from screen without being cought by an enemy.
                       The player can only walk through ground,ropes and ladders. The player can dig a holes through the ground 
                       which can cause enemys to fall inside and to stuck them untill the wall is rebuild. All walls are rebuild
                       after 10 seconds. Player Can fall into his own digs without getting stuck. Player stand inside a rebuild
                       wall after 10 seconds will cause a instant lose for him. If the enemy is inside a hole, the player can walk
                       on top of him. In order to give player think how to win the level , before Starting every level the level
                       will be freezed untill player press on a movement key. 
			   
           
Keyboard Configuration:
                IN MENU:
                       Start Game - ENTER KEY
                       Quit Game - ESCAPE KEY

                IN GAME:
                    Movement:
                        Climb - UP ARROW KEY
                        Move Left - LEFT ARROW KEY
                        Move Right - RIGHT ARROW KEY
                        Move Down - DOWN ARROW KEY
                        
                    Dig:
                        To The Left - Q , Z
                        To The Right - E , X
                        
                    More Action:
                        Commit Sucide - K
                        Escape To Menu - ESCAPE KEY
               
                        

Design:
	Gamecontroller - responsable for build and maintance the game: build the menu, buttons, levels and status bar. 

	Menu - appears at the start of the game or when user hits ESC button. inside the menu the user can choose to
	       start new game or quit to windows

	Button - builds a button by a texture and text

	GameStats - responsable for showing game status: current level , points and left lives counter.
	
	Timer - mannages the time: gets a level time and shows the time left.

	GameObject - the main class which every single game object derived from. contains the texture, size, location and shape

	DynamicObject - contains all moving objects

	Player - mannages player movement and collisions throughout the game

	Enemy - have 3 types: smart eney, constant moving enemy, and random moving enemy each trys to catch the player.
		
	StaticObject - contains all static objects

	Board - the background image behind all objects. this is the limit where player can go.

	Coin - adds points to the score when collected by player.

	Gifts - adds a time, points , life or extra enemy by random

	Ladder - enables moving objects move up or down

	Rope - enables moving objects go left or right even while they're not on the ground	
	
	Wall - limits the moving object movements. enables to move only when the moving object is above it.

Files Added:

	macros- for constant variables.

	resources-folder with picture and sound files 

Main Structures:

        m_staticObjects - contains the static objects in a unique ptr vector.
	
	    m_dynamicObjects - contains all enemies in a unique ptr vector.		       
	
Worth Mentioned Algorithems:
        Run Time Improvement:
            In order to get a good run time of the game we have kept all the map in 2 Dimenssion Vector
            That is parallel to the current level map. In that way we can check for collisions only with
            the 9 object that surronding the dynamic object.
        Digs:
            Every digged wall is being pointed by a wall object, in that case we can start his timer to rebuild
            without checking all walls status.
            
            "Wall Is Not Realy Digged" , every digged wall is staying on the map, the only difference is that
            the wall activated a boolian that say dont draw this wall, thus no need to delete walls that digged
            and create them again after rebuild. After timer is done the boolian will be disabled.

	

Known Bugs:
    Digs - When player Stand on digged wall, his movement become slower.

notes:
    none.

