#include "stdafx.h"
#include "GameStateManager.h"
#include "GameState.h"

namespace TOD {
	GameStateManager::GameStateManager()
	{
	}


	GameStateManager::~GameStateManager()
	{
		// Cleanup states
		while (!states.empty()){
			states.back()->~GameState();
			states.pop_back();
		}
	}

	//void GameStateManager::Init();

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

	}
}
