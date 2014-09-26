// TempleOfDoom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"

int _tmain(int argc, _TCHAR* argv[])
{
	TOD::Game *game = new TOD::Game();
	
	// Initialize game
	game->Init();

	// Start game
	//game->Start();

	return 0;
}
