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
#include "GameOverState.h"
#include "Floor.h"
#include "Room.h"
#include "Trap.h"
#include "Player.h"
#include "Scenery.h"
#include "NPC.h"
#include "Options.h"

namespace TOD {
	ExploringState ExploringState::instance;

	void ExploringState::Init(Game *game) {

	}

	void ExploringState::Cleanup(Game *game) {

	}

	void ExploringState::Update(Game *game) {

	}

	void ExploringState::Render(Game *game) {
		// Clear screen
		ClearScreen();
		// Create main menu banner
		Generate(game);
		// Check if player is alive
		if (!game->GetPlayer()->isDead()) {
			// Handle input
			Do(game);
		}
		else {
			game->StateManager()->ChangeState(game, GameOverState::Instance());
		}

	}

	void ExploringState::Generate(Game *game){
		Room *currRoom = game->GetWorld()->GetCurrentFloor()->GetCurrentRoom();
		Header();
		std::string room = "\tYou're standing in a room. ";

		room += RenderScenery(currRoom);

		room += "\tThe room seems to be ";
		room += currRoom->GetClean() == true ? "clean\n\n" : "dirty\n\n";

		room += currRoom->GetDark() == true ? "\tIt's hard to see anything in the darkness\n\n" : "\tA burning torch makes the room visible\n\n";

		room += RenderExits(currRoom);
		room += RenderNPCs(currRoom);

		room += "\tWhat are you going to do? \n\n";

		std::cout << room;
	}

	std::string ExploringState::RenderNPCs(Room* currRoom) {
		std::string npc;
		std::vector<NPC*> *npcs = currRoom->GetNPC();
		int size = currRoom->GetNPC()->size();

		// If no npc return empty string
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
			if (npcs->at(0)->getLevel() > 10) { // If npc is boss
				npc.clear();
				return npc.append("\t!!! FINAL BOSS REACHED !!!\n\n\tName: " + npcs->at(0)->GetName() + "\n\n");
			}
			else
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

	std::string ExploringState::RenderItems(Room* currRoom) {
		std::string items;
		std::vector<Item*> *it = currRoom->GetItems();
		int size = it->size();

		// If no items return empty string
		if (size == 0) { return items.append("\tYou find nothing of interest\n"); }
		items += "\tItems found: ";
		for (auto i : *it) {
			items += "[";
			items += i->GetName();
			items += "] ";
		}
		return items.append("\n");
	}

	void ExploringState::Do(Game* game) {
		// Handle input
		bool HandleInput = true;
		while (HandleInput) {
			// Create options
			Options *options = new Options("fight;move;search;rest;inventory;map;quit;cheat", true);
			enum optionsenum { FIGHT, MOVE, SEARCH, REST, INVENTORY, MAP, QUIT, CHEAT };

			//TODO: remove cheat code 
			std::vector<Room*> rms = game->GetWorld()->GetCurrentFloor()->GetRooms();
			Room *currRoom = game->GetWorld()->GetCurrentFloor()->GetCurrentRoom();

			// Handle choice
			switch (options->GetChoice()) {
			case FIGHT:
				// Change to fight state
				if (!game->GetWorld()->GetCurrentFloor()->GetCurrentRoom()->GetNPC()->empty()) {
					game->StateManager()->PushState(game, FightingState::Instance());
				}
				else {
					std::cout << "\tYou start to shadowbox, but feel lame while doing it...\n\t";
					PauseScreen();
				}
				HandleInput = false;
				break;
			case MOVE:
				ActionRun(game);
				HandleInput = false;
				break;
			case SEARCH:
				ActionSearch(game);
				HandleInput = true;
				break;
			case REST:
				std::cout << "\tNothing happened...\n\t";
				PauseScreen();
				HandleInput = false;
				break;
			case INVENTORY:
				game->StateManager()->PushState(game, InventoryState::Instance());
				HandleInput = false;
				break;
			case MAP:
				game->StateManager()->PushState(game, MapState::Instance());
				HandleInput = false;
				break;
			case QUIT:
				std::cout << "\tTsk tsk.. Quiting already? What would Indiana Jones say!!\n\t";
				PauseScreen();
				game->StateManager()->ChangeState(game, MainMenuState::Instance());
				HandleInput = false;
				break;
			case CHEAT:
				for (auto r : rms) {
					if (r->GetRoomType() == ST_UP) {
						r->SetPlayer(currRoom->GetPlayer());
						currRoom->SetPlayer(nullptr);
						break;
					}
					if (r->GetRoomType() == END) {
						r->SetPlayer(currRoom->GetPlayer());
						currRoom->SetPlayer(nullptr);
						break;
					}
				}
				HandleInput = false;
				break;
			default:
				std::cout << "\tThat's not an option...\n";
				break;
			}
		}
	}

	void ExploringState::Header() {
		std::cout << "\n\n\tTEMPLE OF DOOM\n";
		std::cout << "\t----------------------------------------------------------------\n\n";
	}

	void ExploringState::MoveTo(Room *currRoom, Room *room) {
		// Check for traps
		if (currRoom->GetTraps()->size() > 0) {

			currRoom->GetPlayer()->TakeDamage(currRoom->GetTraps()->at(0)->GetDamage());

			std::cout << "\n\tA trap went off and did ";
			std::cout << currRoom->GetTraps()->at(0)->GetDamage();
			std::cout << " hp damage\n\n\t";

			if (currRoom->GetPlayer()->isDead()) {
				std::cout << "You died!\n\n\t";
				
			}

			PauseScreen();
		}

		room->SetPlayer(currRoom->GetPlayer());
		room->SetIsExplored(true);
		currRoom->SetPlayer(nullptr);
	}

	std::string ExploringState::SearchTrap(Game *game) {
		Player *player = game->GetPlayer();
		Room *room = game->GetCurrentRoom();

		std::string traps;
		std::vector<Trap*> *tr = room->GetTraps();

		bool trapFound = player->SearchTrap(room);
		if (trapFound)
			traps.append("\tA trap was found and successfully disarmed!\n");
		else
			traps.append("\tThe exits seem to be safe..\n");
		return traps.append("\n");
	}

	void ExploringState::ActionSearch(Game *game) {
		// Get current room
		Room *currRoom = game->GetWorld()->GetCurrentFloor()->GetCurrentRoom();

		std::string items = "\n\tYou search the room...\n\n";

		items += SearchTrap(game);

		items += RenderItems(currRoom);

		std::cout << items << std::endl;

		if (currRoom->GetItems()->size() > 0) {
			std::cout << "\tWhat do you want to do? (pickup/pass)\n\n";
			// Handle input
			bool HandleInput = true;
			while (HandleInput) {
				// Create options
				Options *options = new Options("pickup;pass", false);
				enum optionsenum { PICKUP, PASS };

				std::string input;
				// Handle choice
				switch (options->GetChoice()) {
				case PICKUP: {
					std::cout << "\n\tWhich item do you want to pick-up? (index)\n\n\t";

					std::getline(std::cin, input);
					int index = std::atoi(input.c_str());
					Item *item = currRoom->GetItems()->at(index);
					currRoom->GetPlayer()->PickUp(item);
					currRoom->GetItems()->erase(currRoom->GetItems()->begin() + index);

					HandleInput = false;
					break;
				}
				case PASS:
					HandleInput = false;
					break;
				default:
					std::cout << "\tThat's not an option...\n";
					break;
				}
			}
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
					MoveTo(currRoom, currRoom->GetNorth());
					HandleInput = false;
				}
				else {
					std::cout << "\tYou can't go there, that's not an exit.\n";
				}
				break;
			case EAST:
				if (currRoom->GetEast()) {
					MoveTo(currRoom, currRoom->GetEast());
					HandleInput = false;
				}
				else {
					std::cout << "\tYou can't go there, that's not an exit.\n";
				}
				break;
			case SOUTH:
				if (currRoom->GetSouth()) {
					MoveTo(currRoom, currRoom->GetSouth());
					HandleInput = false;
				}
				else {
					std::cout << "\tYou can't go there, that's not an exit.\n";
				}
				break;
			case WEST:
				if (currRoom->GetWest()) {
					MoveTo(currRoom, currRoom->GetWest());
					HandleInput = false;
				}
				else {
					std::cout << "\tYou can't go there, that's not an exit.\n";
				}
				break;
			case UP:
				if (currRoom->GetUp()) {
					MoveTo(currRoom, currRoom->GetUp());
					HandleInput = false;
				}
				else {
					std::cout << "\tYou can't go there, that's not an exit.\n";
				}
				break;
			case DOWN:
				if (currRoom->GetDown()) {
					MoveTo(currRoom, currRoom->GetDown());
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

