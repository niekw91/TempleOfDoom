#include "stdafx.h"

#include <iostream>
#include <ctime>

#include "GameStateManager.h"
#include "FightingState.h"
#include "ExploringState.h"
#include "Game.h"
#include "Options.h"
#include "NPC.h"
#include "Character.h"

namespace TOD {
	FightingState FightingState::instance;

	void FightingState::Init() {
		srand(time(NULL));
	}

	void FightingState::Cleanup() {

	}

	void FightingState::Update(Game *game) {

	}

	void FightingState::Render(Game *game) {
		// Clear screen
		ClearScreen();
		// Create main menu banner
		Generate(game);
		// Handle input
		Do(game);
	}

	void FightingState::Generate(Game *game) {
		// Create header
		Header();

		// Get npcs
		auto npcs = *game->GetCurrentRoom()->GetNPC();
		for (auto npc : npcs) {
			std::cout << "\tThe " + npc->GetName() + " has " + std::to_string(npc->getHP()) + " hp left.\n";
		}
		std::cout << "\n";

		// Handle input
		bool HandleInput = true;
		while (HandleInput) {
			// Create options
			Options *options = new Options("attack;run;item", true);
			enum optionsenum { ATTACK, RUN, ITEM };

			// Handle choice
			switch (options->GetChoice()) {
			case ATTACK:
				std::cout << "\tNothing happened..." << std::endl;
				std::cout << "\t";
				PauseScreen();
				HandleInput = false;
				break;
			case RUN:
				// Change to exploring state
				game->StateManager()->ChangeState(ExploringState::Instance());
				HandleInput = false;
				break;
			case ITEM:
				std::cout << "\tNothing happened..." << std::endl;
				std::cout << "\t";
				PauseScreen();
				HandleInput = false;
				break;
			default:
				std::cout << "\tThat's not an option..." << std::endl;
				break;
			}
		}
	}

	void FightingState::Do(Game *game) {

	}

	void FightingState::Header() {
		std::cout << "\n\n";
		std::cout << "\tTEMPLE OF DOOM > FIGHT \n";
		std::cout << "\t----------------------------------------------------------------\n\n";
	}
}
