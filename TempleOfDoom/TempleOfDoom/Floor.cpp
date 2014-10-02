#include "stdafx.h"
#include "Floor.h"
#include "Direction.h"

#include <vector>
#include <random>

namespace TOD {
	Floor::Floor(int size) {
		rooms = std::vector<Room*>();
		// Create all empty rooms
		for (int z = 0; z < size * size; z++)
			rooms.push_back(new Room());
		// Keep track of current index
		int currentIndex = 0;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				// Get possible directions
				std::vector<Direction> possibleDirections = Floor::GetPossibleDirections(i, j, size);
				// Get random direction from possible values
				Direction dir = Floor::GetRandomDirection(possibleDirections);
				// Retrieve room
				Room *room = rooms.at(currentIndex);
				// Retrieve index from direction
				int index = Floor::GetRoomIndexByDirection(dir, currentIndex, size);
				// Retrieve room to connect to
				Room *connect = rooms.at(index);
				// Link rooms
				room->SetDirectionPath(dir, connect);
				connect->SetDirectionPath(GetOppositeDirection(dir), room);
				// Increment current index
				currentIndex++;
			}
		}
	}

	Floor::~Floor() {
	}

	std::vector<Direction> Floor::GetPossibleDirections(int rowIndex, int columnIndex, int size) {
		// Create vector with all directions
		std::vector<Direction> directions = std::vector<Direction>();
		// Add all directions
		directions.push_back(NORTH);
		directions.push_back(EAST);
		directions.push_back(SOUTH);
		directions.push_back(WEST);
		// Delete direction from vector if not possible
		if (rowIndex == 0)
			directions.erase(GetPosition(directions, NORTH));
		if (columnIndex == 0)
			directions.erase(GetPosition(directions, WEST));
		if (rowIndex == size - 1)
			directions.erase(GetPosition(directions, SOUTH));
		if (columnIndex == size - 1)
			directions.erase(GetPosition(directions, EAST));
		// Return possible directions
		return directions;
	}

	Direction Floor::GetRandomDirection(std::vector<Direction> possibleDirections) {
		int size = possibleDirections.size() - 1;

		std::default_random_engine dre;
		std::uniform_int_distribution<int> dist(0, size);

		int random = dist(dre);

		return possibleDirections.at(random);
	}

	std::vector<Direction>::iterator Floor::GetPosition(std::vector<Direction> &vector, Direction direction) {
		return std::find(vector.begin(), vector.end(), direction);
	}

	int Floor::GetRoomIndexByDirection(Direction direction, int currentIndex, int size) {
		int index = 0;

		switch (direction) {
		case NORTH:
			index = currentIndex - size;
			break;
		case EAST:
			index = currentIndex + 1;
			break;
		case SOUTH:
			index = currentIndex + size;
			break;
		case WEST:
			index = currentIndex - 1;
			break;
		}
		return index;
	}

	Direction Floor::GetOppositeDirection(Direction direction) {
		Direction dir;
		switch (direction) {
		case NORTH:
			dir = SOUTH;
			break;
		case EAST:
			dir = WEST;
			break;
		case SOUTH:
			dir = NORTH;
			break;
		case WEST:
			dir = EAST;
			break;
		}
		return dir;
	}
}
