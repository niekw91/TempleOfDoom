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
		stateManager = new GameStateManager(this);

		// Create game object factory
		factory = new GameObjectFactory();

		// Load xml files
		factory->LoadNPCFromFile("XML/npc.xml");
		factory->LoadItemsFromFile("XML/items.xml");
		factory->LoadSceneryFromFile("XML/scenery.xml");
		factory->LoadTrapsFromFile("XML/traps.xml");
	}

	void Game::Cleanup(){
		this->stateManager->Cleanup(this);
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
		this->world = new World(floorCount, size, factory);
	}

	Floor *Game::GetCurrentFloor() {
		return this->GetWorld()->GetCurrentFloor();
	}

	Room *Game::GetCurrentRoom() {
		return this->GetCurrentFloor()->GetCurrentRoom();
	}

	Player *Game::GetPlayer() {
		return this->GetCurrentRoom()->GetPlayer();
	}
}