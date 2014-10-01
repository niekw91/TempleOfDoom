#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "Game.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "ExploringState.h"

namespace TOD {

	MainMenuState MainMenuState::instance;

	void MainMenuState::Init() {

	}

	void MainMenuState::Cleanup() {

	}

	void MainMenuState::Update(Game *game) {

	}

	void MainMenuState::Render(Game *game) {
		// Clear screen
		ClearScreen();
		// Create main menu banner
		Generate(game);
		// Handle input
		Do(game);
	}

	void MainMenuState::Generate(Game *game){
		const std::string textfile("MainMenu.txt");
		std::ifstream input_file(textfile);

		std::string line;
		while (getline(input_file, line)) {
			std::cout << line << '\n';
		}
	}

	void MainMenuState::Do(Game* game){
		// Handle input
		bool HandleInput = true;
		while (HandleInput)
		{
			// Read input
			std::cout << "\t\t\t\t";
			std::string action;
			std::getline(std::cin, action);
			std::transform(action.begin(), action.end(), action.begin(), ::tolower); // to lowercase

			// Determine choice
			MainMenuState::input choice = INVALID;
			std::size_t found;
			found = action.find("new");
			if (found != std::string::npos || action == "1"){ choice = NEWGAME; }
			found = action.find("load");
			if (found != std::string::npos || action == "2"){ choice = LOADGAME; }
			found = action.find("credits");
			if (found != std::string::npos || action == "3"){ choice = CREDITS; }

			// Handle choice
			switch (choice){
			case NEWGAME:
				NewGame(game);
				HandleInput = false;
				break;
			case LOADGAME:
				LoadGame(game);
				HandleInput = false;
				break;
			case CREDITS:
				Credits(game);
				HandleInput = false;
				break;
			default:
				std::cout << "\t\t\t\t" << "That's not an option, try again..." << std::endl;
				break;
			}
		}
	}

	void MainMenuState::NewGame(Game* game) {
		// Generate world
		//game->CreateWorld(5, 5);
		// Change state
		game->StateManager()->ChangeState(ExploringState::Instance());
	}

	void MainMenuState::LoadGame(Game *game) {

	}

	void MainMenuState::Credits(Game *game) {

	}
	
	MainMenuState::input MainMenuState::Hash(std::string const& action){
		// Input to lower
		std::for_each(action.begin(), action.end(), ::tolower);
		if (action == "newgame" || action == "1") return NEWGAME;
		if (action == "loadgame" || action == "2") return LOADGAME;
		if (action == "credits" || action == "3") return CREDITS;
		return INVALID;
	}
}