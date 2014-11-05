#include "stdafx.h"
#include "CreditsState.h"
#include "Game.h"
#include "GameStateManager.h"
#include "MainMenuState.h"

#include <iostream>
#include <fstream>
#include <string>

namespace TOD {

	CreditsState CreditsState::instance;

	void CreditsState::Init(Game *game) {

	}

	void CreditsState::Cleanup(Game *game) {

	}

	void CreditsState::Update(Game *game) {

	}

	void CreditsState::Render(Game *game) {
		// Clear screen
		ClearScreen();
		// Generate credits screen
		Generate(game);
		// Handle input
		Do(game);

	}

	void CreditsState::Generate(Game *game) {
		const std::string textfile("assets/screens/credits.txt");
		std::ifstream input_file(textfile);

		std::string line;
		while (getline(input_file, line)) {
			std::cout << line << '\n';
		}
	}

	void CreditsState::Do(Game *game) {
		std::cout << "\n\t";
		PauseScreen();

		game->StateManager()->PopState(game);
	}
}