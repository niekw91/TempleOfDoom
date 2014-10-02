#pragma once
#include "Direction.h"
#include <vector>

class Scenery;
class Item;
class Trap;
class NPC;

namespace TOD {
	class Room
	{

	public:
		Room();
		virtual ~Room();

		void SetDirectionPath(Direction dir, Room *room);

		void SetNorth(Room *room);
		void SetEast(Room *room);
		void SetSouth(Room *room);
		void SetWest(Room *room);
		Room* GetNorth();
		Room* GetEast();
		Room* GetSouth();
		Room* GetWest();

		void Populate();

	private:
		Room *north;
		Room *east;
		Room *south;
		Room *west;
		int size;

		std::vector<Scenery*> *scenery;
		std::vector<Item*> *items;
		std::vector<Trap*> *traps;
		std::vector<NPC*> *npcs;
	};
}

