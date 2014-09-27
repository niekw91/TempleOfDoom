#pragma once

#include "World.h"
#include "GameStateManager.h"

class GameStateManager;

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

	void NewWorld(int levels, int size);

private:
	GameStateManager* stateManager;
	World *world;

	bool Running;

	void MainMenu();
};