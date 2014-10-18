#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

#include "Game.h"
#include "GameStateManager.h"
#include "GameObjectFactory.h"
#include "MainMenuState.h"
#include "World.h"
#include "Floor.h"
#include "Room.h"
#include "Player.h"

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
		factory->LoadNPCFromFile("XML/npc.xml");
		factory->LoadItemsFromFile("XML/items.xml");
		factory->LoadSceneryFromFile("XML/scenery.xml");
		factory->LoadTrapsFromFile("XML/traps.xml");
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
		Floor *firstFloor = this->world->GetFloor(0);
		for (auto room : firstFloor->GetRooms()) {
			// Search for startposition
			if (room->GetRoomType() == 1) {
				// Create new player
				std::cout << "\t\t\t\tWhat is your name? ";
				std::string name;
				std::getline(std::cin, name);
				room->SetPlayer(new Player(name));

				// Give random items to player
				room->GetPlayer()->PickUp(factory->GetRandomItem());
				room->GetPlayer()->PickUp(factory->GetRandomItem());
				room->GetPlayer()->PickUp(factory->GetRandomItem());

			}
		}
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