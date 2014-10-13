// TempleOfDoom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"

int _tmain(int argc, _TCHAR* argv[])
{
	// Set window size
	system("MODE CON: COLS=80 LINES=40");

	// Create game
	TOD::Game game;
	
	// Initialize game
	game.Init();

	// Start game
	game.Start();

	// Cleanup game
	game.Cleanup();

	return 0;
}

