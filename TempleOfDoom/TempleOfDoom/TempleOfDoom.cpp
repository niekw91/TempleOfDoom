// TempleOfDoom.cpp : Defines the entry point for the console application.
//
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "stdafx.h"
#include "Game.h"

int _tmain(int argc, _TCHAR* argv[])
{
	// Check for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Set window size
	system("MODE CON: COLS=80 LINES=40");

	// Create game
	TOD::Game game;
	
	// Initialize game
	game.Init();

	// Start game
	//game.Start();

	// Cleanup game
	game.Cleanup();
	//_CrtDumpMemoryLeaks();
	return 0;
}

