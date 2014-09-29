#include "stdafx.h"
#include <vector>

#include "Game.h"
#include "GameStateManager.h"
#include "GameState.h"

GameStateManager::GameStateManager()
{
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::Init(){
}

void GameStateManager::Cleanup(){

	// Cleanup states
	while (!states.empty()){
		states.back()->~GameState();
		states.pop_back();
	}
}

void GameStateManager::ChangeState(GameState* state){

	// cleanup the current state
	if (!states.empty()) {
		states.back()->~GameState();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameStateManager::PushState(GameState* state){

	states.push_back(state);
}

void GameStateManager::PopState(){

	// cleanup the current state
	if (!states.empty()) {
		//states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if (!states.empty()) {
		//states.back()->Resume();
	}
}

void GameStateManager::HandleEvents(){

	states.back()->HandleEvents();
}

void GameStateManager::Update(){

	states.back()->Update();
}

void GameStateManager::Render(){

	states.back()->Render();
}