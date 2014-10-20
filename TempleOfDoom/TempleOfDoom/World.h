#pragma once

#include <vector>

#include "Floor.h"

namespace TOD {
	class GameObjectFactory;

	class World
	{

	public:
		World(int floorCount, int size, GameObjectFactory *factory);
		virtual ~World();
		void Generate();

		int GetWorldSize();
		int GetFloorCount();

		Floor* World::GetFloor(int number) { return floors[number]; }
		Floor* GetCurrentFloor();

	private:
		std::vector<Floor*> floors;
		GameObjectFactory *factory;
		int floorCount;
		int size;

		void SetRoomTypes();
		Room* World::GetRandomRoom(std::vector<Room*> rooms, Room* room);
	};
}

