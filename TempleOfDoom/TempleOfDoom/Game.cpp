#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

#include "Game.h"
#include "GameStateManager.h"
#include "MainMenuState.h"

namespace TOD {
	Game::Game() {
	}

	Game::~Game() {
	}

	void Game::Init(){
		// Create gamestatemanager
		stateManager = new GameStateManager();

		// Create and change current state 
		stateManager->ChangeState(MainMenuState::Instance());

		// Create game world
		CreateWorld(5, 10);
	}

	void Game::Cleanup(){

	}

	void Game::Start() {
		Running = true;
		// Start game
		while (Running) {
			HandleEvents();
			Update();
			Render();
		}
	}

	void Game::Stop() {
		// Stop game
		Running = false;
	}

	void Game::HandleEvents(){
		// handle events
		this->stateManager->HandleEvents();
	}

	void Game::Update() {
		// update
		stateManager->Update();
	}

	void Game::Render() {
		// render
		stateManager->Render();
	}

	void Game::CreateWorld(int floorCount, int size) {
		// Create new world
		world = new World(floorCount, size);
	}
}