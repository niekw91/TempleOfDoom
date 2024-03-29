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
		factory->LoadNPCFromFile("assets/objects/npc.xml");
		factory->LoadItemsFromFile("assets/objects/items.xml");
		factory->LoadSceneryFromFile("assets/objects/scenery.xml");
		factory->LoadTrapsFromFile("assets/objects/traps.xml");
		factory->LoadBossFromFile("assets/objects/boss.xml");
		factory->LoadExitsFromFile("assets/objects/exits.xml");
	}

	void Game::Cleanup(){
		this->stateManager->Cleanup(this);

		delete world;
		delete factory;
		delete stateManager;
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

	bool Game::SaveGame(Player *player) {
		return this->factory->SavePlayerToFile(player);
	}

	void Game::DeleteSaveGame() {
		remove("assets/save/savegame.xml");
	}
}