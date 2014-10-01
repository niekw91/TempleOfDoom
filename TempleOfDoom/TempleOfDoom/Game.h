#pragma once

namespace TOD {
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

		void Update();
		void Render();

		void Start();
		void Stop();

		GameStateManager *StateManager() { return stateManager; }

		void CreateWorld(int floorCount, int size);

	private:
		GameStateManager *stateManager;
		World *world;

		bool Running;
	};
}