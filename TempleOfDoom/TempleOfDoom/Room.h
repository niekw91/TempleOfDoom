#pragma once
#include "Direction.h"

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

	private:
		Room *north;
		Room *east;
		Room *south;
		Room *west;
		int size;
	};
}

