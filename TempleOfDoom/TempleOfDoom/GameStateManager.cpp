#include "stdafx.h"
#include <vector>

#include "Game.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "MainMenuState.h"

namespace TOD {
	GameStateManager::GameStateManager(Game *game)
	{
		ChangeState(game, MainMenuState::Instance());
	}

	GameStateManager::~GameStateManager()
	{
	}

	void GameStateManager::Init(Game *game){
	}

	void GameStateManager::Cleanup(Game *game){
		// Cleanup states
		while (!states.empty()){
			states.back()->~GameState();
			states.pop_back();
		}
	}

	void GameStateManager::ChangeState(Game *game, GameState* state){

		// cleanup the current state
		if (!states.empty()) {
			states.back()->Cleanup(game);
			states.pop_back();
		}

		// store and init the new state
		states.push_back(state);
		states.back()->Init(game);
	}

	void GameStateManager::PushState(Game *game, GameState* state){
		states.push_back(state);
		states.back()->Init(game);
	}

	void GameStateManager::PopState(Game *game){

		// cleanup the current state
		if (!states.empty()) {
			states.back()->Cleanup(game);
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