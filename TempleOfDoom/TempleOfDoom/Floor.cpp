#include "stdafx.h"
#include "Floor.h"
#include "Direction.h"
#include "Random.h"

#include <vector>
#include <random>
#include <ctime>

namespace TOD {
	Floor::Floor(int level, int size, GameObjectFactory *factory) {
		this->size = size;
		this->level = level;
		this->factory = factory;

		CreateRooms();
	}

	Floor::~Floor() {
		vector<Room*>::iterator rIt;
		for (rIt = rooms.begin(); rIt != rooms.end();) {
			delete *rIt;
			rIt = rooms.erase(rIt);
		}
	}

	void Floor::CreateRooms() {
		rooms = std::vector<Room*>();
		// Create all empty rooms
		for (int z = 0; z < size * size; z++)
			rooms.push_back(new Room(level, size, factory));
		// Keep track of current index
		int currentIndex = 0;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				// Get possible directions
				std::vector<Direction> possibleDirections = Floor::GetPossibleDirections(i, j, size);
				
				int handled = 0;

				while (possibleDirections.size() != 0 && handled < 2) {
					Direction dir = SetDirection(possibleDirections, currentIndex);
					// Delete handled direction
					possibleDirections.erase(GetPosition(possibleDirections, dir));

					handled++;
				}
				// Increment current index
				currentIndex++;
			}
		}
	}

	Direction Floor::SetDirection(std::vector<Direction> possibleDirections, int currentIndex) {
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
		// Set room type to normal
		room->SetRoomType(NORMAL);

		return dir;
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
		int low = 0;

		int random = Random::Next(low, size);

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

	std::vector<Room*> Floor::GetRooms() {
		return rooms;
	}

	Room* Floor::GetCurrentRoom() {
		for (auto currentRoom : rooms) {
			if (currentRoom->GetPlayer() != nullptr) {
				return currentRoom;
			}
		}
		return nullptr;
	}
}
