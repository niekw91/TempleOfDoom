#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sys/stat.h>

#include "Game.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "ExploringState.h"
#include "CreditsState.h"
#include "Floor.h"
#include "Room.h"
#include "Player.h"
#include "GameObjectFactory.h"
#include "Options.h"

namespace TOD {

	MainMenuState MainMenuState::instance;

	void MainMenuState::Init(Game *game) {
	}


	void MainMenuState::Cleanup(Game *game) {

	}

	void MainMenuState::Update(Game *game) {

	}

	void MainMenuState::Render(Game *game) {
		// Clear screen
		ClearScreen();
		// Create main menu banner
		Generate(game);
		// Handle input
		Do(game);
	}

	void MainMenuState::Generate(Game *game){
		const std::string textfile("assets/screens/mainmenu.txt");
		std::ifstream input_file(textfile);

		std::string line;
		while (getline(input_file, line)) {
			std::cout << line << '\n';
		}
	}

	void MainMenuState::Do(Game* game){
		std::cout << "\t\t\t";
		// Handle input
		bool HandleInput = true;
		while (HandleInput)
		{
			Options op = Options("new game;load game;credits;quit", false);
			enum optionsenum { NEWGAME = 1, LOADGAME, CREDITS, QUIT };

			// Handle choice
			switch (op.GetChoice()){
			case NEWGAME:
				NewGame(game);
				HandleInput = false;
				break;
			case LOADGAME:
				LoadGame(game);
				HandleInput = false;
				break;
			case CREDITS:
				Credits(game);
				HandleInput = false;
				break;
			case QUIT:
				game->Stop();
				HandleInput = false;
				break;
			default:
				std::cout << "\t\t\t\t" << "That's not an option..." << std::endl;
				break;
			}
		}
	}

	void MainMenuState::LoadGame(Game *game) {
		std::string save = "assets/save/savegame.xml";
		// Check if save file exitst
		struct stat buffer;
		if (stat(save.c_str(), &buffer) == 0) {
			Player *player = game->GetFactory()->LoadPlayerFromFile(save);
			if (player) {
				std::cout << "\n\t\t\t\tSuccessfully loaded player: " + player->GetName() + "\n\t\t\t\t";
				NewGame(game, player, true);
			}
		}
		else {
			std::cout << "\n\t\t\t\tError: no save game found\n\t\t\t\t";
			PauseScreen();
		}
	}

	void MainMenuState::NewGame(Game* game, Player *player, bool skipName) {
		if (!skipName) {
			// Set player name
			std::cout << "\n\t\t\t\tWhat is your name?\n\t\t\t\t";
			std::string name;
			std::getline(std::cin, name);
			player = new Player(name);
		}
		// Set world size
		std::cout << "\n\t\t\t\tChoose world size: [5 - 15]\n\t\t\t\t";
		std::string sizeStr;
		std::getline(std::cin, sizeStr);
		int size = std::atoi(sizeStr.c_str()) > 0 ? std::atoi(sizeStr.c_str()) : 0;
		if (size > 15 || size < 5) {
			std::cout << "\n\t\t\t\tInvalid size entered, default size set (10)\n\t\t\t\t";
			size = 10;
			PauseScreen();
		}

		// Generate world
		game->CreateWorld(5, size);

		// Add player to world
		Floor *firstFloor = game->GetWorld()->GetFloor(0);
		for (auto room : firstFloor->GetRooms()) {
			// Search for startposition
			if (room->GetRoomType() == 1) {
				// Create new player
				room->SetPlayer(player);

				// Give random items to player
				room->GetPlayer()->PickUp(game->GetFactory()->GetRandomWeapon());
				room->GetPlayer()->PickUp(game->GetFactory()->GetRandomMedkit());
			}
		}

		// Change state
		game->StateManager()->ChangeState(game, ExploringState::Instance());
	}

	void MainMenuState::Credits(Game *game) {
		game->StateManager()->PushState(game, CreditsState::Instance());
	}
}