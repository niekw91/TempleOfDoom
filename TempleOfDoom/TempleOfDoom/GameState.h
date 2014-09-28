#pragma once

#include "Game.h"

class GameState
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	/*void ChangeState(Game* game, GameState* state) {
		game.gameEngineStateManager->ChangeState(state);
	}*/

protected:
	GameState() { }
};