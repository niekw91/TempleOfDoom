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
		SetRoomTypes();
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
	}

	void World::SetRoomTypes() {
		int index = 0;
		int size = floors.size() - 1;

		for (auto *f : floors)
		{
			std::vector<Room*> rooms = f->GetRooms();

			Room* r = GetRandomRoom(rooms, nullptr);
			if (index == 0) {
				r->SetRoomType(START);
				r = GetRandomRoom(rooms, r);
				r->SetRoomType(ST_UP);
			}
			else if (index == size) {
				r->SetRoomType(END);
				r = GetRandomRoom(rooms, r);
				r->SetRoomType(ST_DOWN);
			}
			else {
				r->SetRoomType(ST_UP);
				r = GetRandomRoom(rooms, r);
				r->SetRoomType(ST_DOWN);
			}
			index++;
		}

		for (int i = 0; i < floors.size() - 1; i++)
		{
			std::vector<Room*> rooms = floors.at(i)->GetRooms();
			for (auto r : rooms) {
				if (r->GetRoomType() == ST_UP) {
					std::vector<Room*> nextFloor = floors.at(i + 1)->GetRooms();
					for (auto down : nextFloor) {
						if (down->GetRoomType() == ST_DOWN) {
							r->SetUp(down);
							down->SetDown(r);
						}
					}
				}
			}
		}
	}

	Room* World::GetRandomRoom(std::vector<Room*> rooms, Room* room) {
		Room* r;
		do
		{
			r = rooms.at(Random(0, rooms.size() - 1));
		} while (room == r);
		return r;

	}

	Floor* World::GetCurrentFloor() {
		for (auto currentFloor : floors)
			if (currentFloor->GetCurrentRoom() != nullptr)
				return currentFloor;
	}

	int World::GetWorldSize() {
		return size;
	}

	int World::GetFloorCount() {
		return floorCount;
	}
}