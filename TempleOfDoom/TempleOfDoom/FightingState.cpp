#include "stdafx.h"

#include <iostream>
#include <string>
#include <ctime>

#include "GameStateManager.h"
#include "FightingState.h"
#include "ExploringState.h"
#include "InventoryState.h"
#include "GameOverState.h"
#include "VictoryState.h"
#include "Game.h"
#include "Options.h"
#include "NPC.h"
#include "Character.h"
#include "InputHandler.h"
#include "Player.h"
#include "Random.h"

namespace TOD {
	FightingState FightingState::instance;

	void FightingState::Init(Game *game) {
		juststarted = Random::Next(1, 10) == 1 ? true : false;
	}

	void FightingState::Cleanup(Game *game) {
	}

	void FightingState::Update(Game *game) {

	}

	void FightingState::Render(Game *game) {
		// Clear screen
		ClearScreen();
		// Create main menu banner
		Generate(game);
		if (!game->GetPlayer()->IsDead())
			Do(game);
		else {
			// If player is dead go to GameOverstate
			game->StateManager()->ChangeState(game, GameOverState::Instance());
		}
	}

	void FightingState::Generate(Game *game) {
		// Create header
		Header();

		// Get npcs
		std::cout << "\tYou're fighting with\n\n";
		auto npcs = *game->GetCurrentRoom()->GetNPC();
		int id = 1;
		std::string npcGetStatus = "unscathed";
		std::string npcGetMindstate = "aggressive";
		for (auto npc : npcs) {
			std::cout << "\t" + std::to_string(id++) + ". An " + npcGetMindstate + " " + npc->GetName() + " and it's " + npcGetStatus + "(" + std::to_string(npc->GetHP()) + " HP).\n";
		}
		std::cout << "\n";

		// NPC attack
		auto room = game->GetCurrentRoom();
		auto player = game->GetPlayer();
		int counterdamage = 0;
		if (!juststarted) {
			// NPC attack
			for (auto npc : npcs) {
				int damage = npc->Attack(player);
				counterdamage += damage;
				std::cout << "\tThe " << npc->GetName() << " did " << damage << " health points of damage.\n";
			}
			std::cout << "\n";

			// Player damage
			player->TakeDamage(counterdamage);
		}
		juststarted = false;

		if (player->IsDead())
			std::cout << "\tYou died!\n\n\t";
		else
			std::cout << "\tYou have " << game->GetPlayer()->GetHP() << " out of " << game->GetPlayer()->GetMaxHP() << " health points.\n\n";
	}

	void FightingState::Do(Game *game) {
		// Handle input
		bool HandleInput = true;
		while (HandleInput) {

			std::cout << "\tWhat are you going to do?\n\n";

			// Create options
			std::cout << "\t[ ATTACK | RUN | INVENTORY ]\n\n";
			std::vector<std::string> options = { "attack", "run", "inventory" };

			// Read input
			std::cout << "\t";
			InputHandler input = InputHandler();
			std::cout << "\n";

			// Get commands
			std::vector<std::string> commands = input.GetCommands();

			auto room = game->GetCurrentRoom();
			auto player = game->GetPlayer();

			auto npcs = room->GetNPC();

			int target = 0;
			// Fight
			if (!commands.empty() && commands[0] == options[0]) {
				// Check if command has valid index parameter
				if (commands.size() > 1 && std::atoi(commands[1].c_str()) > 0 && std::atoi(commands[1].c_str()) <= npcs->size()) {
					target = std::stoi(commands[1]);
				}
				// Check if command has valid npc name parameter
				else if (commands.size() > 1) {
					int i = 0;
					for (auto npc : *npcs) {
						if (commands[1] == npc->GetName()) {
							target = i + 1;
							break;
						}
						i++;
					}
				}
				else {
					std::cout << "\tWho are you going to attack?\n\n\t";
					std::string targetString;
					std::getline(std::cin, targetString);
					if (std::atoi(targetString.c_str()) > 0 && std::atoi(targetString.c_str()) <= npcs->size())
						target = std::stoi(targetString);
				}
				if (target > 0) {
					// Attack target
					auto npc = npcs->at(target - 1);

					int damage = player->Attack(npc);

					// Show damage
					npc->TakeDamage(damage);
					std::cout << "\tYou attack the " << npc->GetName() << " and do " << damage << " health points of damage.\n\n";

					// Check if enemy is defeated
					if (npc->IsDead()) {
						std::cout << "\tThe " << npc->GetName() << " is dead. You receive " << npc->GiveXp() << " experience points.\n\n";
						player->ReceiveXp(npc->GiveXp());
						npcs->erase(npcs->begin() + (target - 1));
					}
					bool finalbattle = false;
					if (npc->GetLevel() > 10)
						finalbattle = true;

					// Check if all enemies are defeated
					if (npcs->empty()) {
						if (finalbattle) {
							std::cout << "\tAll the enemies in the room have been defeated.\n\n";
							game->StateManager()->PopState(game);
							game->StateManager()->ChangeState(game, VictoryState::Instance());
						}
						else {
							std::cout << "\tAll the enemies in the room have been defeated.\n\n";
							game->StateManager()->PopState(game);
						}
					}
				}
				std::cout << "\t";
				PauseScreen();
				HandleInput = false;
			}
			// Run
			else if (!commands.empty() && commands[0] == options[1]) {
				game->StateManager()->PopState(game);
				HandleInput = false;
			}
			// Inventory
			else if (!commands.empty() && commands[0] == options[2]) {
				game->StateManager()->PushState(game, InventoryState::Instance());
				HandleInput = false;
			}
			else {
				std::cout << "\tThat's not an option...\n";
			}
		}
	}

	void FightingState::Header() {
		std::cout << "\n\n\tTEMPLE OF DOOM > FIGHT \n";
		std::cout << "\t----------------------------------------------------------------\n\n";
	}
}
