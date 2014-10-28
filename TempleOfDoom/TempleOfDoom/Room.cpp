#include "stdafx.h"
#include "GameObjectFactory.h"
#include "Room.h"
#include "Size.h"
#include "Random.h"

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

		player = nullptr;

		Populate();
	}

	Room::~Room() {
		vector<Scenery*>::iterator sIt;
		for (sIt = scenery->begin(); sIt != scenery->end();) {
			delete *sIt;
			sIt = scenery->erase(sIt);
		}

		vector<Item*>::iterator iIt;
		for (iIt = items->begin(); iIt != items->end();) {
			delete *iIt;
			iIt = items->erase(iIt);
		}

		vector<NPC*>::iterator nIt;
		for (nIt = npcs->begin(); nIt != npcs->end();) {
			delete *nIt;
			nIt = npcs->erase(nIt);
		}

		vector<Trap*>::iterator tIt;
		for (tIt = traps->begin(); tIt != traps->end();) {
			delete *tIt;
			tIt = traps->erase(tIt);
		}

		delete scenery;
		delete items;
		delete npcs;
		delete traps;
		delete player;
	}

	void Room::Populate() {
		// Set random room size
		SetSizeRandom();
		// Set random room lighting
		SetDarkRandom();
		// Set random room tidiness
		SetCleanRandom();
		
		// Set random room scenery, with a maximum of 2 items
		for (int i = 0; i < 2; i++) {
			SetScenery();
		}

		// Set random npc's, with a maximum of 3
		for (int i = 0; i < 3; i++) {
			SetNPC();
		}

		// Set random Items
		SetItems();
		// Set random trap
		SetTrap();
	}

	void Room::SetTrap() {
		if (HasObjectType()) {
			traps->push_back(factory->GetRandomTrap());
		}
	}

	void Room::SetItems() {
		if (HasObjectType()) {
			int r = Random::Next(1, 3);
			switch (r)
			{
			case 1:
				items->push_back(factory->GetRandomArmor());
				break;
			case 2:
				items->push_back(factory->GetRandomWeapon());
				break;
			case 3:
				items->push_back(factory->GetRandomMedkit());
				break;
			default:
				break;
			}
		}
	}

	void Room::SetNPC() {
		if (HasObjectType()) {
			npcs->push_back(factory->GetRandomNPC());
		}
	}

	void Room::SetScenery() {
		if (HasObjectType()) {
			Scenery *item = factory->GetRandomScenery();
			// Only add scenery item if not already contains
			if (std::find(scenery->begin(), scenery->end(), item) == scenery->end()) {
				scenery->push_back(item);
			}
		}
	}

	bool Room::RandomBool() {
		std::random_device device;
		std::mt19937 gen(device());
		std::bernoulli_distribution coin_flip(0.5);
		return coin_flip(gen);
	}

	bool Room::HasObjectType() {
		return RandomBool();
	}

	void Room::SetCleanRandom() {
		bool r = RandomBool();
		if (r)
			this->isClean = true;
		else
			this->isClean = false;
	}

	void Room::SetDarkRandom() {
		bool r = RandomBool();
		if (r)
			this->isDark = true;
		else
			this->isDark = false;
	}

	void Room::SetSizeRandom() {
		int r = Random::Next(1, 3);
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

	bool Room::HasDirectionPath(Direction dir) {
		bool hasDir = false;
		switch (dir)
		{
		case NORTH:
			if (GetNorth()) hasDir = true;
			break;
		case EAST:
			if (GetEast()) hasDir = true;
			break;
		case SOUTH:
			if (GetSouth()) hasDir = true;
			break;
		case WEST:
			if (GetWest()) hasDir = true;
			break;
		}
		return hasDir;
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

	void Room::SetDown(Room *room) {
		this->down = room;
	}

	void Room::SetUp(Room *room) {
		this->up = room;
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
	
	Room* Room::GetUp() {
		return up;
	}

	Room* Room::GetDown() {
		return down;
	}

	void Room::SetRoomType(RoomType type) {
		this->type = type;
	}

	RoomType Room::GetRoomType() {
		return type;
	}

	bool Room::GetDark() {
		return isDark;
	}

	bool Room::GetClean() {
		return isClean;
	}

	Size Room::GetSize() {
		return size;
	}

	void Room::DisarmTrap() {
		vector<Trap*>::iterator tIt;
		for (tIt = traps->begin(); tIt != traps->end();) {
			delete *tIt;
			tIt = traps->erase(tIt);
		}
	}
}
