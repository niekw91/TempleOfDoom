#include "stdafx.h"

#include <iostream>
#include <random>
#include <vector>

#include "World.h"
#include "GameObjectFactory.h"

namespace TOD {
	World::World(int floorCount, int size, GameObjectFactory *factory) {
		this->floorCount = floorCount;
		this->size = size;
		this->factory = factory;

		Generate();
	}

	World::~World() {
	}

	void World::Generate() {
		floors = std::vector<Floor*>();

		for (int i = 0; i < this->floorCount; i++)
		{
			floors.push_back(new Floor(size, factory));
		}
	}
}