#pragma once

#include <vector>

#include "GameState.h"

class GameState;

class GameStateManager
{
public:
	GameStateManager();
	virtual ~GameStateManager();

	void Init();
	void Cleanup();

	void ChangeState(GameState *state);
	void PushState(GameState *state);
	void PopState();

	void HandleEvents();
	void Update();
	void Render();

private:
	std::vector<GameState*> states;
};