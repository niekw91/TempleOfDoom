#include "stdafx.h"
#include "InventoryState.h"
#include "ExploringState.h"
#include "Game.h"
#include "GameStateManager.h"
#include "Player.h"
#include "Item.h"

#include <string>
#include <iostream>

namespace TOD {
	InventoryState InventoryState::instance;

	void InventoryState::Init() {

	}

	void InventoryState::Cleanup() {

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
		//std::vector<Item*> items = game->GetWorld()->GetCurrentFloor()->GetCurrentRoom()->GetPlayer()->GetInventory();

		//for (auto i : items) {
		//	inventory.append(i->GetName() + "\n");
		//}
	}

	void InventoryState::Do(Game* game){
		std::cout << "\t";
		PauseScreen();
		// Change to map state
		game->StateManager()->ChangeState(ExploringState::Instance());
	}

	void InventoryState::Header(){
		std::cout << "\n\n";
		std::cout << "\tTEMPLE OF DOOM > INVENTORY \n";
		std::cout << "\t----------------------------------------------------------------\n\n";
	}
}
