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

	int World::Random(int start, int end) {
		std::default_random_engine dre;
		std::uniform_int_distribution<int> dist(start, end);

		return dist(dre);
	}

	void World::Generate() {
		floors = std::vector<Floor*>();

		for (int i = 0; i < this->floorCount; i++)
		{
			floors.push_back(new Floor(size, factory));
		}
		// Set roomtypes
		int index = 0;
		for (auto *f : floors)
		{
			std::vector<Room*> rooms = f->GetRooms();
			int size = rooms.size() - 1;
			
			Room* r = rooms.at(Random(0, size));
			if (index == 0) {
				r->SetRoomType(START);
				r = rooms.at(Random(0, size));
				r->SetRoomType(ST_UP);
			}
			else if (index == floors.size() - 1) {
				r->SetRoomType(END);
				r = rooms.at(Random(0, size));
				r->SetRoomType(ST_DOWN);
			}
			else {
				r->SetRoomType(ST_UP);
				r = rooms.at(Random(0, size));
				r->SetRoomType(ST_DOWN);
			}
			index++;
		}
	}

	Floor* World::GetCurrentFloor() {
		return floors[0];
	}

	int World::GetWorldSize() {
		return size;
	}

	int World::GetFloorCount() {
		return floorCount;
	}
}