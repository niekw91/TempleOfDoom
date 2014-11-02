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

		Player *player = game->GetWorld()->GetCurrentFloor()->GetCurrentRoom()->GetPlayer();

		std::vector<Item*> items = *player->GetInventory();
		
		int ind = 0;
		for (auto i : items) {
			inventory.append("\t[" + std::to_string(ind));
			inventory.append("] " + i->ToString() + "\n");
			ind++;
		}
		inventory.append("\n");

		Weapon *w = player->GetWeapon();
		Armor *a = player->GetAmor();

		std::string weaponEquiped = w == nullptr ? "none" : w->GetName();
		std::string armorEquiped = a == nullptr ? "none" : a->GetName();

		inventory.append("\t---------------------------------------------\n");
		inventory.append("\tPLAYER STATS\n");
		inventory.append("\t---------------------------------------------\n");
		inventory.append("\tEquiped weapon: " + weaponEquiped + "\n");
		inventory.append("\tEquiped armor: " + armorEquiped + "\n\n");
		inventory.append("\tLevel: " + std::to_string(player->GetLevel()) + "\n");
		inventory.append("\tHP: " + std::to_string(player->GetHP()) + " of " + std::to_string(player->GetMaxHP()) + "\n");
		inventory.append("\tAttack: " + std::to_string(player->GetAttack()) + "\n");
		inventory.append("\tDefense: " + std::to_string(player->GetDefense()) + "\n");
		inventory.append("\tXP: " + std::to_string(player->GetXp()) + "\n");
		inventory.append("\n\n");
	}

	void InventoryState::Do(Game* game) {
		// Handle input
		bool HandleInput = true;
		while (HandleInput) {
			// Create options
			Options *options = new Options("equip;use;delete;back", true);
			enum optionsenum { EQUIP, USE, DELETE, BACK };

			// Handle choice
			switch (options->GetChoice()) {
			case EQUIP:
				ActionEquip(game);
				HandleInput = false;
				break;
			case USE:
				ActionUse(game);
				HandleInput = false;
				break;
			case DELETE:
				ActionDelete(game);
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

	void InventoryState::ActionUse(Game *game) {
		Player *player = game->GetWorld()->GetCurrentFloor()->GetCurrentRoom()->GetPlayer();

		std::cout << "\n\tWhat item do you want to use? (index)\n\n\t";

		std::string input;

		std::getline(std::cin, input);
		int index = std::atoi(input.c_str());

		// Heal
		Medkit *medkit = dynamic_cast<Medkit*>(player->GetInventory()->at(index));
		player->Heal(medkit);

		RemoveItem(player, index);
	}

	void InventoryState::ActionDelete(Game *game) {
		Player *player = game->GetWorld()->GetCurrentFloor()->GetCurrentRoom()->GetPlayer();

		std::cout << "\n\tWhat item do you want to delete? (index)\n\n\t";

		std::string input;

		std::getline(std::cin, input);
		int index = std::atoi(input.c_str());

		RemoveItem(player, index);
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
				Weapon *weapon = dynamic_cast<Weapon*>(player->GetInventory()->at(index));
				player->Equip(weapon);
				HandleInput = false;
				break;
			}
			case ARMOR: {
				std::cout << "\n\tWhich armor piece would you like to equip? (index)\n\n\t";

				std::getline(std::cin, input);
				int index = std::atoi(input.c_str());
				Armor *armor = dynamic_cast<Armor*>(player->GetInventory()->at(index));
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

	void InventoryState::RemoveItem(Player *player, int index) {
		// Erase item from inventory
		if (player->GetInventory()->size() > 0) {
			if (player->GetInventory()->size() == 1)
				player->GetInventory()->pop_back();
			else
				player->GetInventory()->erase(player->GetInventory()->begin() + index);
		}
	}

	void InventoryState::Header(){
		std::cout << "\n\n";
		std::cout << "\tTEMPLE OF DOOM > INVENTORY \n";
		std::cout << "\t----------------------------------------------------------------\n\n";
	}
}
