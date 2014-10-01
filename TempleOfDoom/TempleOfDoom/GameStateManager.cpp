#include "stdafx.h"
#include <vector>

#include "Game.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "MainMenuState.h"

namespace TOD {
	GameStateManager::GameStateManager()
	{
		ChangeState(MainMenuState::Instance());
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
			states.back()->Cleanup();
			states.pop_back();
		}

		// resume previous state
		if (!states.empty()) {
			//states.back()->Resume();
		}
	}

	void GameStateManager::Update(Game *game){

		states.back()->Update(game);
	}

	void GameStateManager::Render(Game *game){

		states.back()->Render(game);
	}
}