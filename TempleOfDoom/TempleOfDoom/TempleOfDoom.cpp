// TempleOfDoom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"

#include "tinyxml2.h"
#include <string>

int _tmain(int argc, _TCHAR* argv[])
{
	// Open XML
	tinyxml2::XMLDocument doc;
	doc.Parse("npc.xml");

	tinyxml2::XMLElement *npc = doc.FirstChildElement("name");
	std::string text = npc->GetText();
	printf(text.c_str());

	//// Create game
	//TOD::Game game;
	//
	//// Initialize game
	//game.Init();

	//// Start game
	//game.Start();

	//// Cleanup game
	//game.Cleanup();




	return 0;
}

