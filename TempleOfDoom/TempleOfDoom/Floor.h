#pragma once
#include "Room.h"

#include <vector>

namespace TOD {
	class GameObjectFactory;

	class Floor
	{

	public:
		Floor(int size, GameObjectFactory *factory);
		virtual ~Floor();

		void CreateRooms();
	private:
		int size;
		GameObjectFactory *factory;
		std::vector<Room*> rooms;

		std::vector<Direction>::iterator GetPosition(std::vector<Direction> &vector, Direction direction);
		std::vector<Direction> Floor::GetPossibleDirections(int rowIndex, int columnIndex, int size);
		Direction GetRandomDirection(std::vector<Direction> possibleDirections);
		Direction GetOppositeDirection(Direction direction);
		int GetRoomIndexByDirection(Direction direction, int currentIndex, int size);
	};
}

