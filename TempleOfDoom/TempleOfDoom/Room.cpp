#include "stdafx.h"
#include "GameObjectFactory.h"
#include "Room.h"
#include "Size.h"

#include <random>
#include <iostream>
#include <fstream>
#include <string>

namespace TOD {
	Room::Room(GameObjectFactory *factory) {
		this->factory = factory;

		scenery = new std::vector<Scenery*>();
		items = new std::vector<Item*>();
		traps = new std::vector<Trap*>();
		npcs = new std::vector<NPC*>();

		Populate();
	}

	Room::~Room() {
	}

	void Room::Populate() {
		// Set random room size
		SetSizeRandom();
		// Set random room lighting
		SetDarkRandom();
		// Set random room tidiness
		SetCleanRandom();
		// Set random room scenery
		SetScenery();
		// Set random npc's
		SetNPC();
	}

	void Room::SetNPC() {
		if (HasObjectType()) {
			npcs->push_back(factory->GetRandomNPC());
		}
	}

	void Room::SetScenery() {
		if (HasObjectType()) {

		}
	}

	int Room::Random(int from, int top) {
		std::default_random_engine dre;
		std::uniform_int_distribution<int> dist(from, top);

		return dist(dre);
	}

	bool Room::HasObjectType() {
		int r = Random(1, 2);
		if (r = 1)
			return true;
		else
			return false;
	}

	void Room::SetCleanRandom() {
		int r = Random(1, 2);
		if (r = 1)
			this->isClean = true;
		else
			this->isClean = false;
	}

	void Room::SetDarkRandom() {
		int r = Random(1, 2);
		if (r = 1)
			this->isDark = true;
		else
			this->isDark = false;
	}

	void Room::SetSizeRandom() {
		int r = Random(1, 3);
		switch (r)
		{
		case 1:
			this->size = SMALL;
			break;
		case 2:
			this->size = MEDIUM;
			break;
		case 3:
			this->size = LARGE;
			break;
		default:
			break;
		}
	}

	void Room::SetDirectionPath(Direction dir, Room *room) {
		switch (dir)
		{
		case NORTH:
			this->SetNorth(room);
			break;
		case EAST:
			this->SetEast(room);
			break;
		case SOUTH:
			this->SetSouth(room);
			break;
		case WEST:
			this->SetWest(room);
			break;
		}
	}

	void Room::SetNorth(Room *room) {
		this->north = room;
	}

	void Room::SetEast(Room *room) {
		this->east = room;
	}

	void Room::SetSouth(Room *room) {
		this->south = room;
	}

	void Room::SetWest(Room *room) {
		this->west = room;
	}

	Room* Room::GetNorth() {
		return north;
	}

	Room* Room::GetEast() {
		return east;
	}

	Room* Room::GetSouth() {
		return south;
	}

	Room* Room::GetWest() {
		return west;
	}
}
