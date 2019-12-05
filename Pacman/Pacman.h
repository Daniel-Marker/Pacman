#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

// Just need to include main header file
#include "S2D/S2D.h"
#include "Maze.h"
#include "Direction.h"
#include "Enemy.h"
#include "Player.h"
#include "Menu.h"

// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;

// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.
const int _enemyCount = 4;

class Pacman : public Game
{
private:
	Enemy* _enemies[_enemyCount];

	Player* _pacman;

	//Pacman constants
	const float _cPacmanSpeed;
	const float _cPacmanPosOffset;
	const int _cPacmanFrameTime;

	//Score constants
	const int _cPelletValue;
	const int _cPowerPelletValue;
	const int _cEnemyValue;
	const int _cCherryValue;

	//Time constants
	const int _cLevelEndDelay;
	const int _cLevelStartDelay;
	const int _cPoweredUpTime;

	//Data for pellet animation
	const int _cPelletFrameTime;
	int _currentPelletFrameTime;
	int _pelletFrame;

	//Data for cherry
	bool _cherryGivenToPlayer;
	const int _cCherryX;
	const int _cCherryY;
	const float _cProportionOfPelletsRequired;

	//Screenswrapping data
	float leftLimit;
	float rightLimit;

	//Level data
	int _pelletsCollected;
	int _level;
	bool _levelEnd;

	//Delay data
	int _delayInMilli;
	bool _delay;

	//Powered up data
	bool _poweredUp;
	int _powerTimer;

	// Position for String output
	Vector2* _stringPosition;

	Menu* _pauseMenu;
	Menu* _startMenu;

	//Data for overlay
	Texture2D* _overlay;
	Rect* _overlayRect;

	//Data for maze
	Texture2D* _mazeTileset;
	Rect* _mazeTileRect;
	Vector2* _backgroundPos;
	int _noPelletsAvailable;
	mazeUnits _maze[cMazeHeight][cMazeWidth];
	Color* _backgroundColor;
	Vector2* _backgroundColorVector;

	//Data for sound/music
	SoundEffect* _intro;
	SoundEffect* _munch;

	//Functions
	void Input(int elapsedTime, Input::KeyboardState* state);
	void CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey);
	void CheckStart(Input::KeyboardState* state, Input::Keys startKey);
	void UpdatePacman(int elapsedTime);
	bool CollisionCheck(float pacmanX, float pacmanY, direction directionOfMovement);
	void LoadMaze(mazeUnits (&maze)[cMazeHeight][cMazeWidth], const mazeUnits(&mazeToCopy)[cMazeHeight][cMazeWidth]);
	int GetNoOfPellets(mazeUnits(&mazeToCheck)[cMazeHeight][cMazeWidth]);
	void PelletCollisionCheck();
	void CherryGiveCheck();
	void ScreenWrapCheck();
	void LevelWinCheck();
	void ResetLevel();
	void ResetMaze();
	void DelayCountdown(int elapsedTime);
	void CreateAndInitGhosts();
	void PacmanDeath();

public:
	/// <summary> Constructs the Pacman class. </summary>
	Pacman(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);
};