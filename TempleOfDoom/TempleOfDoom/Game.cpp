#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

#include "Game.h"
#include "GameStateManager.h"
#include "MainMenuState.h"
#include "World.h"

namespace TOD {
	Game::Game() {
	}

	Game::~Game() {
	}

	void Game::Init(){
		// Create statemanager
		stateManager = new GameStateManager();
	}

	void Game::Cleanup(){

	}

	void Game::Start() {
		Running = true;
		// Start game
		while (Running) {
			Update();
			Render();
		}
	}

	void Game::Stop() {
		// Stop game
		Running = false;
	}

	void Game::Update() {
		// update
		this->stateManager->Update(this);
	}

	void Game::Render() {
		// render
		this->stateManager->Render(this);
	}

	void Game::CreateWorld(int floorCount, int size) {
		// Create new world
		this->world = new World(floorCount, size);
	}
}