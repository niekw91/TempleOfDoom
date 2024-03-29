#pragma once
#include "Direction.h"
#include <vector>
#include <map>
#include "Size.h"
#include "RoomType.h"

namespace TOD {
	class GameObjectFactory;
	class Scenery;
	class Item;
	class Trap;
	class NPC;
	class Player;

	class Room
	{

	public:
		Room(int floor, int floorCount, GameObjectFactory *factory);
		virtual ~Room();

		void SetDirectionPath(Direction dir, Room *room);
		bool HasDirectionPath(Direction dir);

		void DisarmTrap();

		void SetNorth(Room *room);
		void SetEast(Room *room);
		void SetSouth(Room *room);
		void SetWest(Room *room);
		void SetUp(Room *room);
		void SetDown(Room *room);
		Room* GetNorth();
		Room* GetEast();
		Room* GetSouth();
		Room* GetWest();
		Room* GetUp();
		Room* GetDown();

		void SetRoomType(RoomType type);
		RoomType GetRoomType();

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

		void InjectNPC();

		std::vector<Scenery*> *GetScenery() { return scenery; }
		std::vector<Item*> *GetItems() { return items; }
		std::vector<Trap*> *GetTraps() { return traps; }
		std::vector<NPC*> *GetNPC() { return npcs; }

		std::string GetDirectionExitString(Direction dir);

		Player *GetPlayer() { return player; }
		void SetPlayer(Player *newPlayer) { player = newPlayer; }

		void SetIsExplored(bool ex) { explored = ex; }
		bool GetIsExplored() { return explored; }

		void SetEndBoss();
		int GetFloorLevel();

	private:
		GameObjectFactory *factory;

		RoomType type;

		Room *north;
		Room *east;
		Room *south;
		Room *west;
		Room *down;
		Room *up;

		bool RandomBool();

		bool explored;

		int floorLevel;
		int floorCount;

		// Room properties
		Size size;
		bool isClean;
		bool isDark;

		// Room item vectors
		std::vector<Scenery*> *scenery;
		std::vector<Item*> *items;
		std::vector<Trap*> *traps;
		std::vector<NPC*> *npcs;
		Player *player;

		std::map<Direction, std::string> directionStrings;

		std::string RandomExitString();
	};
}

