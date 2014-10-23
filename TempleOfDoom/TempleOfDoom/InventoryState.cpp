#include "stdafx.h"
#include "InventoryState.h"
#include "ExploringState.h"
#include "Game.h"
#include "GameStateManager.h"
#include "Player.h"
#include "Item.h"
#include "Options.h"
#include "Armor.h"
#include "Weapon.h"

#include <algorithm>
#include <string>
#include <iostream>

namespace TOD {
	InventoryState InventoryState::instance;

	void InventoryState::Init(Game *game) {

	}

	void InventoryState::Cleanup(Game *game) {

	}

	void InventoryState::Update(Game *game) {
		Generate(game);
	}

	void InventoryState::Render(Game *game) {
		// Clear screen
		ClearScreen();
		// Create header
		Header();
		// Render map
		std::cout << inventory;

		Do(game);
	}

	void InventoryState::Generate(Game *game){
		// Clear inventory string
		inventory.clear();

		std::vector<Item*> items = game->GetWorld()->GetCurrentFloor()->GetCurrentRoom()->GetPlayer()->GetInventory();
		
		int ind = 0;
		for (auto i : items) {
			inventory.append("\t[" + std::to_string(ind));
			inventory.append("] " + i->ToString() + "\n");
			ind++;
		}
		inventory.append("\n");

		Weapon *w = game->GetWorld()->GetCurrentFloor()->GetCurrentRoom()->GetPlayer()->GetWeapon();
		Armor *a = game->GetWorld()->GetCurrentFloor()->GetCurrentRoom()->GetPlayer()->GetAmor();

		std::string weaponEquiped = w == nullptr ? "none" : w->GetName();
		std::string armorEquiped = a == nullptr ? "none" : a->GetName();

		inventory.append("\t---------------------------------------------\n");
		inventory.append("\tEquiped weapon: " + weaponEquiped + "\n");
		inventory.append("\tEquiped armor: " + armorEquiped);
		inventory.append("\n\n");

	}

	void InventoryState::Do(Game* game) {
		// Handle input
		bool HandleInput = true;
		while (HandleInput) {
			// Create options
			Options *options = new Options("equip;back", true);
			enum optionsenum { EQUIP, BACK };

			// Handle choice
			switch (options->GetChoice()) {
			case EQUIP:
				ActionEquip(game);
				HandleInput = false;
				break;
			case BACK:
				game->StateManager()->PopState(game);
				HandleInput = false;
				break;
			default:
				std::cout << "\tThat's not an option..." << std::endl;
				break;
			}
		}
	}

	void InventoryState::ActionEquip(Game *game) {
		Player *player = game->GetWorld()->GetCurrentFloor()->GetCurrentRoom()->GetPlayer();

		std::cout << "\n\tWhat would you like to equip? (weapon/armor)\n\n";

		std::string input;

		// Handle input
		bool HandleInput = true;
		while (HandleInput) {
			// Create options
			Options *options = new Options("weapon;armor", true);
			enum optionsenum { WEAPON, ARMOR };
			switch (options->GetChoice()) {
			case WEAPON: {
				std::cout << "\n\tWhich weapon do you wish to equip? (index)\n\n\t";

				std::getline(std::cin, input);
				int index = std::atoi(input.c_str());
				Weapon *weapon = dynamic_cast<Weapon*>(player->GetInventory().at(index));
				player->Equip(weapon);
				HandleInput = false;
				break;
			}
			case ARMOR: {
				std::cout << "\n\tWhich armor piece would you like to equip? (index)\n\n\t";

				std::getline(std::cin, input);
				int index = std::atoi(input.c_str());
				Armor *armor = dynamic_cast<Armor*>(player->GetInventory().at(index));
				player->Equip(armor);
				HandleInput = false;
				break;
			}
			default:
				std::cout << "\tThat's not an option..." << std::endl;
				break;
			}
		}		
	}

	void InventoryState::Header(){
		std::cout << "\n\n";
		std::cout << "\tTEMPLE OF DOOM > INVENTORY \n";
		std::cout << "\t----------------------------------------------------------------\n\n";
	}
}
