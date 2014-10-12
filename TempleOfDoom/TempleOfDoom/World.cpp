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

		int size = end;
		int low = start;

		//generate random number
		int random = (rand() % (size - low + 1) + low);

		return random;
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
		for (auto currentFloor : floors)
			if (currentFloor->GetCurrentRoom()->GetPlayer() != nullptr)
				return currentFloor;
	}

	int World::GetWorldSize() {
		return size;
	}

	int World::GetFloorCount() {
		return floorCount;
	}
}