#pragma once

#include "World.h"

namespace TOD {
	// Forward declaration
	class GameObjectFactory;
	class GameStateManager;
	class World;
	class Floor;
	class Room;
	class Player;

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

		World *GetWorld() { return world; }
		Floor *GetCurrentFloor();
		Room *GetCurrentRoom();
		Player *GetPlayer();
		
		bool SaveGame(Player *player);

		GameObjectFactory *GetFactory() { return factory; }

	private:
		GameStateManager *stateManager;
		GameObjectFactory *factory;
		World *world;

		bool Running;
	};
}