#include "stdafx.h"

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <ctime>

#include "Game.h"
#include "GameStateManager.h"
#include "ExploringState.h"
#include "InventoryState.h"
#include "FightingState.h"
#include "MapState.h"
#include "MainMenuState.h"
#include "Floor.h"
#include "Room.h"
#include "Player.h"
#include "Scenery.h"
#include "NPC.h"
#include "Options.h"

namespace TOD {
	ExploringState ExploringState::instance;

	void ExploringState::Init() {
		srand(time(NULL));
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
		std::string room = "\n\tYou're standing in a room. ";

		room += RenderScenery(currRoom);
		room += RenderExits(currRoom);
		room += RenderNPCs(currRoom);

		room += "\tWhat are you going to do? \n\n";

		std::cout << room;
	}

	std::string ExploringState::RenderNPCs(Room* currRoom) {
		std::string npc;
		std::vector<NPC*> *npcs = currRoom->GetNPC();
		int size = currRoom->GetNPC()->size();

		// If no scenery return empty string
		if (size == 0) { return npc; }
		npc += "\tThere is a ";
		if (size > 1) {
			for (auto n : *npcs) {
				npc += n->GetName();
				npc += " and a ";
			}
			npc = npc.substr(0, npc.size() - 7); // Cut ' and a ' off string
		}
		else {
			npc += npcs->at(0)->GetName();
		}
		npc += " in the room\n\n";
		return npc;
	}

	std::string ExploringState::RenderExits(Room* currRoom) {
		std::string exits;
		std::map<Direction, std::string> dirs;

		if (currRoom->GetNorth()) { dirs[NORTH] = "North"; }
		if (currRoom->GetSouth()) { dirs[SOUTH] = "South"; }
		if (currRoom->GetEast()) { dirs[EAST] = "East"; }
		if (currRoom->GetWest()) { dirs[WEST] = "West"; }
		if (currRoom->GetUp()) { dirs[UP] = "Up"; }
		if (currRoom->GetDown()) { dirs[DOWN] = "Down"; }

		if (dirs.size() == 1) {
			exits += "\tThere is a hallway to the " + (dirs.begin())->second;
		}
		else {
			for (auto d : dirs) {
				exits += "\t";
				exits += d.second;
				exits += " there is " + RandomExitString();
				exits += "\n";
			}
		}
		return exits.append("\n");
	}

	std::string ExploringState::RenderScenery(Room* currRoom) {
		std::string scenery;
		std::vector<Scenery*> *items = currRoom->GetScenery();
		int size = currRoom->GetScenery()->size();

		// If no scenery return empty string
		if (size == 0) { return scenery.append("\n\n"); } 
		scenery += "There is a ";
		if (size > 1) {
			for (auto i : *items) {
				scenery += i->GetName();
				scenery += " and a ";
			}
			scenery = scenery.substr(0, scenery.size() - 7); // Cut ' and a ' off string
		}
		else {
			scenery += items->at(0)->GetName();
		}
		scenery += " in the room\n\n";
		return scenery;
	}

	void ExploringState::Do(Game* game) {
		// Handle input
		bool HandleInput = true;
		while (HandleInput) {
			// Create options
			Options *options = new Options("fight;move;explore;rest;inventory;map;quit;cheat", true);
			enum optionsenum { FIGHT, MOVE, EXPLORE, REST, INVENTORY, MAP, QUIT, CHEAT };

			//temp 
			std::vector<Room*> rms = game->GetWorld()->GetCurrentFloor()->GetRooms();
			Room *currRoom = game->GetWorld()->GetCurrentFloor()->GetCurrentRoom();

			// Handle choice
			switch (options->GetChoice()) {
			case FIGHT:
				// Change to fight state
				if (!game->GetWorld()->GetCurrentFloor()->GetCurrentRoom()->GetNPC()->empty()) {
					game->StateManager()->ChangeState(FightingState::Instance());
				}
				else {
					std::cout << "\tYou start to shadowbox, but feel lame while doing it..." << std::endl;
					std::cout << "\t";
				}

				HandleInput = false;
				break;
			case MOVE:
				ActionRun(game);
				HandleInput = false;
				break;
			case EXPLORE:
				std::cout << "\tNothing happened..." << std::endl;
				std::cout << "\t";
				PauseScreen();
				HandleInput = false;
				break;
			case REST:
				std::cout << "\tNothing happened..." << std::endl;
				std::cout << "\t";
				PauseScreen();
				HandleInput = false;
				break;
			case INVENTORY:
				// Change to inventory state
				game->StateManager()->ChangeState(InventoryState::Instance());
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
				PauseScreen();
				game->StateManager()->ChangeState(MainMenuState::Instance());
				HandleInput = false;
				break;
			case CHEAT:
				for (auto r : rms) {
					if (r->GetRoomType() == ST_UP) {
						r->SetPlayer(currRoom->GetPlayer());
						currRoom->SetPlayer(nullptr);
						Room *uproom = r->GetUp();

						break;
					}
				}
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
		// Get current room
		Room *currRoom = game->GetWorld()->GetCurrentFloor()->GetCurrentRoom();

		std::cout << "\n\tWhere to?\n\n";

		// Handle input
		bool HandleInput = true;
		while (HandleInput) {
			// Create options
			Options *options = new Options("north;east;south;west;up;down", false);
			enum optionsenum { NORTH, EAST, SOUTH, WEST, UP, DOWN };

			// Handle choice
			switch (options->GetChoice()) {
			case NORTH:
				if (currRoom->GetNorth()) {
					currRoom->GetNorth()->SetPlayer(currRoom->GetPlayer());
					currRoom->SetPlayer(nullptr);
					HandleInput = false;
				}
				else {
					std::cout << "\tYou can't go there, that's not an exit.\n";
				}
				break;
			case EAST:
				if (currRoom->GetEast()) {
					currRoom->GetEast()->SetPlayer(currRoom->GetPlayer());
					currRoom->SetPlayer(nullptr);
					HandleInput = false;
				}
				else {
					std::cout << "\tYou can't go there, that's not an exit.\n";
				}
				break;
			case SOUTH:
				if (currRoom->GetSouth()) {
					currRoom->GetSouth()->SetPlayer(currRoom->GetPlayer());
					currRoom->SetPlayer(nullptr);
					HandleInput = false;
				}
				else {
					std::cout << "\tYou can't go there, that's not an exit.\n";
				}
				break;
			case WEST:
				if (currRoom->GetWest()) {
					currRoom->GetWest()->SetPlayer(currRoom->GetPlayer());
					currRoom->SetPlayer(nullptr);
					HandleInput = false;
				}
				else {
					std::cout << "\tYou can't go there, that's not an exit.\n";
				}
				break;
			case UP:
				if (currRoom->GetUp()) {
					currRoom->GetUp()->SetPlayer(currRoom->GetPlayer());
					currRoom->SetPlayer(nullptr);
					HandleInput = false;
				}
				else {
					std::cout << "\tYou can't go there, that's not an exit.\n";
				}
				break;
			case DOWN:
				if (currRoom->GetDown()) {
					currRoom->GetDown()->SetPlayer(currRoom->GetPlayer());
					currRoom->SetPlayer(nullptr);
					HandleInput = false;
				}
				else {
					std::cout << "\tYou can't go there, that's not an exit.\n";
				}
				break;
			default:
				std::cout << "\tThat's not an option..." << std::endl;
				break;
			}
		}
	}

	std::string ExploringState::RandomExitString() {
		int random = (rand() % (6 - 1 + 1) + 1);

		switch (random) {
		case 1:
			return "a fragile locked door that could be opened";
		case 2:
			return "a dark hallway";
		case 3:
			return "a window that could be climbed through";
		case 4:
			return "a door";
		case 5:
			return "a small path";
		case 6:
			return "a cracked wall";
		}
	}

}

