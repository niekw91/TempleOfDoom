#pragma once

#include "GameStateManager.h"
#include "World.h"

// Forward declaration
class GameStateManager;
class World;

class Game
{
public:
	Game();
	virtual ~Game();

	void Init();
	void Cleanup();

	void HandleEvents();
	void Update();
	void Render();

	void Start();
	void Stop();

	GameStateManager* StateManager() { return stateManager; }

	void NewWorld(int levels, int size);

private:
	GameStateManager* stateManager;
	World *world;

	bool Running;
};