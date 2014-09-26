#pragma once
#include "Floor.h"

namespace TOD {
	class World
	{

	public:
		World(int floorCount, int size);
		virtual ~World();
		void Generate();

		int floorCount;
		int size;
	
	private:
		std::vector<Floor>* floors;
	};
}

