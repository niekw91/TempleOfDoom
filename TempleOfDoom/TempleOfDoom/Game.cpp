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
	stateManager->ChangeState(this, MainMenuState::Instance());

	Running = true;
}

void Game::Cleanup(){

}

void Game::Start() {
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

void Game::NewWorld(int levels, int size) {
	// Create new world
	world = new World(levels, size);

	Start();
}