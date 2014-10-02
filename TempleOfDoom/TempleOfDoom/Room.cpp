#include "stdafx.h"
#include "Room.h"

namespace TOD {
	Room::Room() {
		scenery = new std::vector<Scenery*>();
		items = new std::vector<Item*>();
		traps = new std::vector<Trap*>();
		npcs = new std::vector<NPC*>();
	}

	Room::~Room() {
	}

	void Room::Populate() {

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
