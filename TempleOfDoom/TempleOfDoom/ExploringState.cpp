#include "stdafx.h"

#include <string>
#include <fstream>
#include <iostream>

#include "Game.h"
#include "GameStateManager.h"
#include "ExploringState.h"
#include "MainMenuState.h"

namespace TOD {
	ExploringState ExploringState::instance;

	void ExploringState::Init() {

	}

	void ExploringState::Cleanup() {

	}

	void ExploringState::Update(Game *game) {

	}

	void ExploringState::Render(Game *game) {
		// Clear screen
		ClearScreen();
		// Create main menu banner
		Generate(game);
		// Handle input
		Do(game);
	}

	void ExploringState::Generate(Game *game){
		const std::string textfile("Header.txt");
		std::ifstream input_file(textfile);

		std::string line;
		while (getline(input_file, line)) {
			std::cout << line << '\n';
		}
		std::string room;
		room += "\n";
		room += "\tDescription: \n\n";
		room += "\tExits: \n\n";
		room += "\tPresent: \n\n";
		room += "\tWhat are you going to do? \n\n";
		room += "\t[ FIGHT | RUN | EXPLORE | REST | OPEN INVENTORY | CHECK MAP ] \n\n";
		room += "\tAction: run \n\n";
		room += "\tWhat direction? \n\n";
		room += "\t[ NORTH | EAST | SOUTH ] \n\n";

		std::cout << room;
		std::cout << "\t";
		std::cin;
		game->StateManager()->ChangeState(MainMenuState::Instance());
	}

	void ExploringState::Do(Game* game){
		// Read input
		std::string action;
		std::getline(std::cin, action);

		// Handle input
		/*while (true){
			switch (Hash(action)){
			case NEWGAME:
				NewGame(game);
				break;
			case LOADGAME:
				LoadGame(game);
				break;
			case CREDITS:
				Credits(game);
				break;
			default:
				std::cout << action << " is not a valid option.";
				break;
			}
		}*/
	}
}

