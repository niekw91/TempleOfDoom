// TempleOfDoom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Game *game = new Game();
	
	// Initialize game
	game->Init();

	// Create world
	//game->NewWorld(3, 5);

	// Start game
	game->Start();

	return 0;
}
