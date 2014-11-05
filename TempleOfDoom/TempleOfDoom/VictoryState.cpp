#include "stdafx.h"
#include "VictoryState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "GameStateManager.h"

#include <iostream>
#include <fstream>
#include <string>


namespace TOD {
	VictoryState VictoryState::instance;

	void VictoryState::Init(Game *game) {

	}

	void VictoryState::Cleanup(Game *game) {

	}

	void VictoryState::Update(Game *game) {

	}

	void VictoryState::Render(Game *game) {
		// Clear screen
		ClearScreen();
		// Create game over screen
		Generate(game);
		// Handle input
		Do(game);
	}

	void VictoryState::Generate(Game *game) {
		const std::string textfile("assets/screens/victory.txt");
		std::ifstream input_file(textfile);

		std::string line;
		while (getline(input_file, line)) {
			std::cout << line << '\n';
		}
	}

	void VictoryState::Do(Game *game) {
		std::cout << "\n\t";
		PauseScreen();

		game->StateManager()->ChangeState(game, MainMenuState::Instance());
	}
}