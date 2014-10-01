#include "stdafx.h"
#include "ActionHandler.h"
#include "Game.h"
#include <string>
#include <iostream>

namespace TOD {
	ActionHandler::ActionHandler(Game *game)
	{
		this->game = game;
	}

	ActionHandler::~ActionHandler()
	{
	}

	void ActionHandler::Do(std::string action){
		std::cout << action;
	}
}