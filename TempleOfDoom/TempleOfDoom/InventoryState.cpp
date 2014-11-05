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
		options = std::vector<Options*>();
	}

	void InventoryState::Cleanup(Game *game) {
		std::vector<Options*>::iterator it;
		for (it = options.begin(); it != options.end();) {
			delete *it;
			it = options.erase(it);
		}
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
		
		int ind = 1;
		for (auto i : items) {
			inventory.append("\t[" + std::to_string(ind++));
			inventory.append("] " + i->ToString() + "\n");
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
			Options *op = new Options("equip;use;delete;back", true);
			options.push_back(op);
			enum optionsenum { EQUIP = 1, USE, DELETE, BACK };

			// Handle choice
			switch (op->GetChoice()) {
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
		int index = std::atoi(input.c_str()) == 0 ? 0 : std::atoi(input.c_str());
		if (index > 0 && index <= player->GetInventory()->size()) {
			// Heal
			Medkit *medkit = dynamic_cast<Medkit*>(player->GetInventory()->at(index - 1));
			if (medkit) {
				player->Heal(medkit);

				RemoveItem(player, index);
			}
			else
				std::cout << "\n\tInvalid item chosen\n\n\t";
		}
		else
			std::cout << "\n\tInvalid index entered\n\n\t";
	}

	void InventoryState::ActionDelete(Game *game) {
		Player *player = game->GetWorld()->GetCurrentFloor()->GetCurrentRoom()->GetPlayer();

		std::cout << "\n\tWhat item do you want to delete? (index)\n\n\t";

		std::string input;

		std::getline(std::cin, input);
		int index = std::atoi(input.c_str()) == 0 ? 0 : std::atoi(input.c_str());
		if (index > 0 && index <= player->GetInventory()->size())
			RemoveItem(player, index - 1);
		else
			std::cout << "\n\tInvalid index entered\n\n\t";
	}

	void InventoryState::ActionEquip(Game *game) {
		Player *player = game->GetWorld()->GetCurrentFloor()->GetCurrentRoom()->GetPlayer();

		std::cout << "\n\tWhat would you like to equip? (weapon/armor)\n\n";

		std::string input;

		// Handle input
		bool HandleInput = true;
		while (HandleInput) {
			// Create options
			Options *op = new Options("weapon;armor", true);
			options.push_back(op);
			enum optionsenum { WEAPON = 1, ARMOR };
			switch (op->GetChoice()) {
			case WEAPON: {
				std::cout << "\n\tWhich weapon do you wish to equip? (index)\n\n\t";

				std::getline(std::cin, input);
				int index = std::atoi(input.c_str()) == 0 ? 0 : std::atoi(input.c_str());
				if (index > 0 && index <= player->GetInventory()->size()) {
					Weapon *weapon = dynamic_cast<Weapon*>(player->GetInventory()->at(index - 1));
					if (weapon)
						player->Equip(weapon);
					else
						std::cout << "\n\tInvalid item chosen\n\n\t";
				}
				HandleInput = false;
				break;
			}
			case ARMOR: {
				std::cout << "\n\tWhich armor piece would you like to equip? (index)\n\n\t";

				std::getline(std::cin, input);
				int index = std::atoi(input.c_str()) == 0 ? 0 : std::atoi(input.c_str());
				if (index > 0 && index <= player->GetInventory()->size()) {
					Armor *armor = dynamic_cast<Armor*>(player->GetInventory()->at(index - 1));
					if (armor)
						player->Equip(armor);
					else
						std::cout << "\n\tInvalid item chosen\n\n\t";
				}
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
