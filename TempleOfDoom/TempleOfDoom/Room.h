#pragma once
#include "Direction.h"
#include <vector>
#include "Size.h"

namespace TOD {
	class GameObjectFactory;
	class Scenery;
	class Item;
	class Trap;
	class NPC;

	class Room
	{

	public:
		Room(GameObjectFactory *factory);
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

		int Random(int from, int top);
		void Populate();
		bool HasObjectType();

		void SetScenery();
		void SetNPC();
		void SetItems();
		void SetTrap();
		void SetSizeRandom();
		void SetCleanRandom();
		void SetDarkRandom();
		Size GetSize();
		bool GetClean();
		bool GetDark();

	private:
		GameObjectFactory *factory;

		Room *north;
		Room *east;
		Room *south;
		Room *west;

		// Room properties
		Size size;
		bool isClean;
		bool isDark;

		// Room item vectors
		std::vector<Scenery*> *scenery;
		std::vector<Item*> *items;
		std::vector<Trap*> *traps;
		std::vector<NPC*> *npcs;
	};
}

