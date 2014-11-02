#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sys/stat.h>

#include "Game.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "ExploringState.h"
#include "CreditsState.h"
#include "Floor.h"
#include "Room.h"
#include "Player.h"
#include "GameObjectFactory.h"

namespace TOD {

	MainMenuState MainMenuState::instance;

	void MainMenuState::Init(Game *game) {
		
	}

	void MainMenuState::Cleanup(Game *game) {

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
			std::vector<std::string> actions({ "invalid", "new", "load", "credits", "quit"});
			for (size_t i = 0, size = actions.size(); i < size; i++) {
				std::size_t found = action.find(actions.at(i));
				if (found != std::string::npos || action == std::to_string(i)) {
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
			case QUIT:
				game->Stop();
				HandleInput = false;
				break;
			default:
				std::cout << "\t\t\t\t" << "That's not an option..." << std::endl;
				break;
			}
		}
	}

	void MainMenuState::LoadGame(Game *game) {
		std::string save = "assets/save/savegame.xml";
		// Check if save file exitst
		struct stat buffer;
		if (stat(save.c_str(), &buffer) == 0) {
			std::cout << "\n\t\t\t\tLoading game..\n\t\t\t\t";
		}
		else {
			std::cout << "\n\t\t\t\tError: no save game found\n\t\t\t\t";
			PauseScreen();
		}
	}

	void MainMenuState::NewGame(Game* game) {
		// Set player name
		std::cout << "\n\t\t\t\tWhat is your name?\n\t\t\t\t";
		std::string name;
		std::getline(std::cin, name);
		// Set world size
		std::cout << "\n\t\t\t\tChoose world size: [5, 10, 15]\n\t\t\t\t";
		std::string sizeStr;
		std::getline(std::cin, sizeStr);

		// Generate world
		game->CreateWorld(5, atoi(sizeStr.c_str()));

		// Add player to world
		Floor *firstFloor = game->GetWorld()->GetFloor(0);
		for (auto room : firstFloor->GetRooms()) {
			// Search for startposition
			if (room->GetRoomType() == 1) {
				// Create new player
				room->SetPlayer(new Player(name));

				// Give random items to player
				room->GetPlayer()->PickUp(game->GetFactory()->GetRandomWeapon());
				room->GetPlayer()->PickUp(game->GetFactory()->GetRandomMedkit());
			}
		}

		// Change state
		game->StateManager()->ChangeState(game, ExploringState::Instance());
	}

	void MainMenuState::Credits(Game *game) {
		game->StateManager()->PushState(game, CreditsState::Instance());
	}
}