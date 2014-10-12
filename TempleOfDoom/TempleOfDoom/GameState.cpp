#include "stdafx.h"
#include <iostream>

#include "Game.h"
#include "GameState.h"

namespace TOD {
	void ChangeState(Game* game, GameState* state) {
		//game->StateManager()->ChangeState(state);
	}

	void GameState::ClearScreen() {
		system("CLS");
		//std::cout << std::string(100, '\n');
	}

	void GameState::PauseScreen() {
		system("PAUSE");
	}
}