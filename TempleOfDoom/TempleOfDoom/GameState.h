#pragma once

#include "GameStateManager.h"

class GameState
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	/*void ChangeState(GameStateManager* gameStateManager, GameState* state) {
		gameStateManager->ChangeState(state);
	}*/

protected:
	GameState() { }
};