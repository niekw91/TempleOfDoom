#include "stdafx.h"
#include <iostream>
#include "Game.h"

namespace TOD {
	Game::Game() {

	}

	void Game::CreateWorld() {
		// create world
		world = new World(4, 10);

		Start();
	}

	Game::~Game() {
	}

	void Game::Start() {
		running = true;

		while (running) {
			Update();
			Render();
		}

	}

	void Game::Stop() {
		running = false;
	}

	void Game::Update() {
		// update
	}

	void Game::Render() {
		// render
	}
}
