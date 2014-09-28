#pragma once

#include <vector>

#include "Game.h"
#include "GameState.h"

// Forward declaration
class Game;
class GameState;

class GameStateManager
{
public:
	GameStateManager();
	virtual ~GameStateManager();

	void Init();
	void Cleanup();

	void ChangeState(Game *game, GameState *state);
	void PushState(GameState *state);
	void PopState();

	void HandleEvents();
	void Update();
	void Render();

private:
	std::vector<GameState*> states;
	Game *gameEngine;
};