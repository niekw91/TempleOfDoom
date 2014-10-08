#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

#include "Game.h"
#include "GameStateManager.h"
#include "GameObjectFactory.h"
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

		// Create game object factory
		factory = new GameObjectFactory();

		// Load xml files
		factory->LoadNPCFromFile("C:/Users/Niek Willems/Documents/GitHub/TempleOfDoom/TempleOfDoom/TempleOfDoom/Debug/npc.xml");
		factory->LoadItemsFromFile("C:/Users/Niek Willems/Documents/GitHub/TempleOfDoom/TempleOfDoom/TempleOfDoom/Debug/items.xml");
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
		this->world = new World(floorCount, size, factory);
	}
}