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

		Floor* GetCurrentFloor();
		int GetWorldSize();
		int GetFloorCount();
	private:
		std::vector<Floor*> floors;
		GameObjectFactory *factory;
		int floorCount;
		int size;

		int Random(int start, int end);
	};
}

