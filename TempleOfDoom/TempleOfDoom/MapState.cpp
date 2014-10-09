#include "stdafx.h"
#include "MapState.h"
#include "Game.h"
#include "World.h"
#include "ExploringState.h"
#include "GameStateManager.h"

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

namespace TOD {
	MapState MapState::instance;

	void MapState::Init() {
		
	}

	void MapState::Cleanup() {

	}

	void MapState::Update(Game *game) {
		if (map.empty()) {
			// Generate map
			Generate(game);
		}
	}

	void MapState::Render(Game *game) {
		// Clear screen
		ClearScreen();
		// Render map
		std::cout << "\tTemple Of Doom Map: \n\n";
		std::cout << map;
		// Render choices
		std::cout << "\n\n \tWhat are you going to do? \n\n";
		std::cout << "\t[ BACK ] \n\n";
		
		Do(game);
	}

	void MapState::Generate(Game *game) {
		// Generate map
		std::vector<Room*> rooms = game->GetWorld()->GetCurrentFloor()->GetRooms();
		int size = game->GetWorld()->GetWorldSize();

		int index = 0;

		for (auto r : rooms) {
			if (index == 0) map.append("\t. ");
			else map.append(". ");
			index++;
			if (index == size) {
				map.append("\n");
				index = 0;
			}
		}	

	}

	void MapState::Do(Game *game) {
		// Handle input
		bool HandleInput = true;
		while (HandleInput){
			// Read input
			std::cout << "\t";
			std::string action;
			std::getline(std::cin, action);
			std::transform(action.begin(), action.end(), action.begin(), ::tolower); // to lowercase

			// Determine choice
			input choice = INVALID;
			std::vector<std::string> *actions = new std::vector<std::string>({ "invalid", "back" });

			for (int i = 0; i < actions->size(); i++){
				std::size_t found = action.find(actions->at(i));
				if (found != std::string::npos || action == std::to_string(i)){
					choice = input(i);
					break;
				}
			}

			// Handle choice
			switch (choice){
			case BACK:
				// Change to map state
				game->StateManager()->ChangeState(ExploringState::Instance());
				HandleInput = false;
				break;
			default:
				std::cout << "\tThat's not an option..." << std::endl;
				break;
			}
		}
	}
}
