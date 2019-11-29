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

	// Data to represent Pacman
	Vector2* _pacmanPosition;
	Rect* _pacmanSourceRect;
	Texture2D* _pacmanTexture;
	direction _pacmanDirection;
	int _pacmanFrame;
	int _pacmanCurrentFrameTime;

	int _score;
	Vector2* _scorePosition;
	int _pelletsCollected;

	int _level;
	bool _levelEnd;
	const int _cLevelEndDelay;
	const int _cLevelStartDelay;

	int _delayInMilli;
	bool _delay;

	bool _poweredUp;
	int _powerTimer;
	const int _cPoweredUpTime;

	//Pacman constants
	const float _cPacmanSpeed;
	const float _cPacmanPosOffset;
	const int _cPacmanFrameTime;

	// Data to represent Munchie
	int _frameCount;
	Rect* _munchieRect;
	Texture2D* _munchieBlueTexture;
	Texture2D* _munchieInvertedTexture;

	// Position for String
	Vector2* _stringPosition;

	//Data for Pause Menu
	Texture2D* _menuBackground;
	Rect* _menuRectangle;
	Vector2* _menuStringPosition;
	bool _paused;
	bool _pKeyDown;

	//Data for Start menu
	Texture2D* _startBackground;
	bool _start;

	//Data for overlay
	Texture2D* _overlay;
	Rect* _overlayRect;

	//Data for maze
	Texture2D* _backgroundElements;
	Rect* _backgroundRect;
	Vector2* _backgroundPos;
	int _noPelletsAvailable;
	mazeUnits _maze[_mazeHeight][_mazeWidth];

	//Functions
	void Input(int elapsedTime, Input::KeyboardState* state);
	void CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey);
	void CheckStart(Input::KeyboardState* state, Input::Keys startKey);
	void UpdatePacman(int elapsedTime);
	bool CollisionCheck(float pacmanX, float pacmanY, direction directionOfMovement);
	void LoadMaze(mazeUnits (&maze)[_mazeHeight][_mazeWidth], const mazeUnits(&mazeToCopy)[_mazeHeight][_mazeWidth]);
	int GetNoOfPellets(mazeUnits(&mazeToCheck)[_mazeHeight][_mazeWidth]);
	void PelletCollisionCheck();
	void ScreenWrapCheck(const float leftLimit, const float rightLimit);
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