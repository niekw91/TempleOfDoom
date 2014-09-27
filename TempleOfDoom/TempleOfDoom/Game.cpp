#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

#include "Game.h"
#include "GameStateManager.h"
#include "MainMenuState.h"

Game::Game() { 
}

Game::~Game() {
}

void Game::Init(){
	// Create gamestatemanager
	stateManager = new GameStateManager();

	// Create and change current state 
	stateManager->ChangeState(MainMenuState::Instance());

	Running = true;
}

void Game::NewWorld(int levels, int size) {
	// Create new world
	world = new World(levels, size);

	Start();
}

void Game::Start() {
	while (Running) {
		HandleEvents();
		Update();
		Render();
	}
}

void Game::Stop() {
	Running = false;
}

void Game::HandleEvents(){
	// handle events
	stateManager->HandleEvents();
}

void Game::Update() {
	// update
	stateManager->Update();
}

void Game::Render() {
	// render
	stateManager->Render();
}