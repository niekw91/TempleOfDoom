#include "stdafx.h"
#include "GameOverState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "GameStateManager.h"

#include <iostream>
#include <fstream>
#include <string>

namespace TOD {
	GameOverState GameOverState::instance;

	void GameOverState::Init(Game *game) {

	}

	void GameOverState::Cleanup(Game *game) {

	}

	void GameOverState::Update(Game *game) {

	}

	void GameOverState::Render(Game *game) {
		// Clear screen
		ClearScreen();
		// Create game over screen
		Generate(game);
		// Handle input
		Do(game);
	}

	void GameOverState::Generate(Game *game) {
		const std::string textfile("assets/screens/gameover.txt");
		std::ifstream input_file(textfile);

		std::string line;
		while (getline(input_file, line)) {
			std::cout << line << '\n';
		}
	}

	void GameOverState::Do(Game *game) {
		std::cout << "\n\t";
		PauseScreen();

		// Delete save game
		game->DeleteSaveGame();

		game->StateManager()->ChangeState(game, MainMenuState::Instance());
	}
}