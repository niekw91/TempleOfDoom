// TempleOfDoom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// Create game object
	TOD::Game *game = new TOD::Game();
	game->CreateWorld();

	return 0;
}

