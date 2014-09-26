#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Game.h"
using namespace std;

namespace TOD {
	Game::Game() {
		// Create main menu
		MainMenu();
	}

	void Game::Init(){
		// Create gamestatemanager
		stateManager = new GameStateManager();

		running = true;
	}

	void Game::CreateWorld() {
		// create world
		world = new World(4, 10);

		Start();
	}

	Game::~Game() {
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

	void Game::MainMenu() {

		const string textfile("MainMenuBanner.txt");
		ifstream input_file(textfile);

		string line;
		while (getline(input_file, line)) { 
			cout << line << '\n'; 
		}
		std::cin.get();
	}
}
