#include "stdafx.h"

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Game.h"
#include "GameStateManager.h"
#include "ExploringState.h"
#include "MapState.h"
#include "MainMenuState.h"
#include "Floor.h"
#include "Room.h"
#include "Player.h"
#include "Scenery.h"
#include "NPC.h"

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
		Room *currRoom = game->GetWorld()->GetCurrentFloor()->GetCurrentRoom();
		Header();
		std::string room;

		// Show scenery
		room += "\n";
		room += "\tYou're standing in a room. There is a";// with a table in the middle. \n\tThe table has four chairs. \n\tThere is a box in the corner. \n\n";
		for (auto i : *currRoom->GetScenery()) {
			room += " " + i->GetName();
		}
		room += "\n\n";
		
		// Show exits
		//room += "\tSouth is the temple exit, you can almost taste the outdoor air. \n\tNorth there is a solid door. \n\tEast there is a hallway. \n\n";
		room += "\tThere is an exit to the";
		if (currRoom->GetNorth() != nullptr) { room += " North"; }
		if (currRoom->GetSouth() != nullptr) { room += " South"; }
		if (currRoom->GetEast() != nullptr) { room += " East"; }
		if (currRoom->GetWest() != nullptr) { room += " West"; }
		room += "\n\n";

		// Show npcs
		//room += "\tThree rats look at you with their bloodshot eyes. \n\n";
		room += "\tThere is a";
		for (auto i : *currRoom->GetNPC()) {
			room += " " + i->GetName();
		}
		room += " in the room\n\n";

		// Show options
		room += "\tWhat are you going to do? \n\n";
		room += "\t[ FIGHT | RUN | EXPLORE | REST | OPEN INVENTORY | CHECK MAP ] \n\n";
		/*room += "\tAction: run \n\n";
		room += "\tWhat direction? \n\n";
		room += "\t[ NORTH | EAST | SOUTH ] \n\n";*/

		std::cout << room;
	}

	void ExploringState::Do(Game* game){
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
			std::vector<std::string> *actions = new std::vector<std::string>({ "invalid", "fight", "run", "explore", "rest", "inventory", "map", "quit" });

			for (int i = 0; i < actions->size(); i++){
				std::size_t found = action.find(actions->at(i));
				if (found != std::string::npos || action == std::to_string(i)){ 
					choice = input(i); 
					break;
				}
			}

			// Handle choice
			switch (choice){
			case FIGHT:
				std::cout << "\tNothing happened..." << std::endl;
				std::cout << "\t";
				system("PAUSE");
				HandleInput = false;
				break;
			case RUN:
				/*std::cout << "\tNothing happened..." << std::endl;
				std::cout << "\t";
				system("PAUSE");*/
				ActionRun(game);
				HandleInput = false;
				break;
			case EXPLORE:
				std::cout << "\tNothing happened..." << std::endl;
				std::cout << "\t";
				system("PAUSE");
				HandleInput = false;
				break;
			case REST:
				std::cout << "\tNothing happened..." << std::endl;
				std::cout << "\t";
				system("PAUSE");
				HandleInput = false;
				break;
			case INVENTORY:
				std::cout << "\tNothing happened..." << std::endl; 
				std::cout << "\t";
				system("PAUSE");
				HandleInput = false;
				break;
			case MAP:
				// Change to map state
				game->StateManager()->ChangeState(MapState::Instance());
				HandleInput = false;
				break;
			case QUIT:
				std::cout << "\tTsk tsk.. Quiting already? What would Indiana Jones say!!" << std::endl;
				std::cout << "\t";
				system("PAUSE");
				game->StateManager()->ChangeState(MainMenuState::Instance());
				HandleInput = false;
				break;
			default:
				std::cout << "\tThat's not an option..." << std::endl;
				break;
			}
		}
	}

	void ExploringState::Header() {
		const std::string textfile("Header.txt");
		std::ifstream input_file(textfile);

		std::string line;
		while (getline(input_file, line)) {
			std::cout << line << '\n';
		}
	}

	void ExploringState::ActionRun(Game *game){
		std::cout << "\tWhere to?";
		// Read input
		std::cout << "\t";
		std::string action;
		std::getline(std::cin, action);
	}
}

