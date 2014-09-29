#pragma once

#include "GameStateManager.h"
#include "World.h"

// Forward declaration
class GameStateManager;
class World;

namespace TOD {
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

		void CreateWorld(int floorCount, int size);

	private:
		GameStateManager* stateManager;
		World *world;

		bool Running;
	};
}