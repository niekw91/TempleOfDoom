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
			input choice = INVALID;
			std::vector<std::string> *actions = new std::vector<std::string>({ "invalid", "new", "load", "credits"});
			for (int i = 0; i < actions->size(); i++){
				std::size_t found = action.find(actions->at(i));
				if (found != std::string::npos || action == std::to_string(i)){
					choice = input(i);
					break;
				}
			}

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
				std::cout << "\t\t\t\t" << "That's not an option..." << std::endl;
				break;
			}
		}
	}

	void MainMenuState::NewGame(Game* game) {
		// Generate world
		game->CreateWorld(5, 10);

		// Change state
		game->StateManager()->ChangeState(ExploringState::Instance());
	}

	void MainMenuState::LoadGame(Game *game) {
		std::cout << "\t\t\t\t" << "Nothing happened..." << std::endl;
		std::cout << "\t\t\t\t";
		system("PAUSE");
	}

	void MainMenuState::Credits(Game *game) {
		std::cout << "\t\t\t\t" << "Nothing happened..." << std::endl;
		std::cout << "\t\t\t\t";
		system("PAUSE");
	}
}