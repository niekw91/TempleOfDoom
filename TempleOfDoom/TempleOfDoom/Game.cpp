#include "stdafx.h"
#include "Game.h"

namespace TOD {
	Game::Game()
	{
		running = true;

		Start();
	}


	Game::~Game()
	{
	}

	void Game::Start() {

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
