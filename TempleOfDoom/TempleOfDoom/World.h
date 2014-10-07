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

		GameObjectFactory *factory;
		int floorCount;
		int size;

	private:
		std::vector<Floor*> floors;
	};
}

