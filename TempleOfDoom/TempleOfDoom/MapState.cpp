#include "stdafx.h"
#include "MapState.h"
#include "Game.h"
#include "World.h"
#include "ExploringState.h"
#include "GameStateManager.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

namespace TOD {
	MapState MapState::instance;

	void MapState::Init() {

	}

	void MapState::Cleanup() {

	}

	void MapState::Update(Game *game) {
		// Clear map
		map.clear();
		// Generate map
		Generate(game);
	}

	void MapState::Render(Game *game) {
		// Clear screen
		ClearScreen();
		// Create header
		Header();
		// Render map
		std::cout << map;

		Do(game);
	}

	void MapState::Generate(Game *game) {
		// Generate map
		std::vector<Room*> rooms = game->GetWorld()->GetCurrentFloor()->GetRooms();
		int size = game->GetWorld()->GetWorldSize();

		int index = 0;
		int step = 2; // One step is 2 chars
		int length = size + size; // Length is size * 2

		for (auto r : rooms) {
			//if (index == 0) map.append("\t");
			//map.append(". ");

			std::string append;
			if (r->GetRoomType() == NORMAL) append = "N ";
			else if (r->GetRoomType() == START) append = "S ";
			else if (r->GetRoomType() == END) append = "E ";
			else if (r->GetRoomType() == ST_DOWN) append = "L ";
			else if (r->GetRoomType() == ST_UP) append = "H ";
			map.append(append);

			index += step;
			if (index == length) {
				map.append("\n");
				for (int i = 0; i < length; i++)
					map.append(" ");
				map.append("\n");
				index = 0;
			}
		}

		index = 0;

		for (auto r : rooms) {
			if (r->GetNorth() != nullptr) map.replace(index - (length + 1), 1, "|");
			if (r->GetEast() != nullptr)
				map.replace((index + 1), 1, "-");
			if (r->GetSouth() != nullptr) map.replace(index + (length + 1), 1, "|");
			if (r->GetWest() != nullptr) map.replace((index - 1), 1, "-");
			index += 2;
			if (map.at(index) == '\n') index += (length + 2);
		}

		// Insert tabs
		int countdown = 0;
		std::string tmp;
		std::string tab;
		for (auto c : map){
			if (countdown == 0){
				tab = "\t";
				countdown = 20;
			}
			else {
				tab = "";
				countdown--;
			}
			tmp.append(tab + c);
		}
		map = tmp;

		// Create legend
		std::string legend = "";
		legend += "\t\tLEGEND\n";
		legend += "\t\t|-\tHallways\n";
		legend += "\t\tS\tStartposition\n";
		legend += "\t\tE\tEnd Boss\n";
		legend += "\t\tN\tNormal Room\n";
		legend += "\t\tL\tStairs Down\n";
		legend += "\t\tH\tStairs Up\n";
		legend += "\t\t.\tUnexplored\n";

		// Merge map and legend
		map = StringMerger(map, legend);
	}

	void MapState::Do(Game *game) {
		std::cout << "\t";
		PauseScreen();
		// Change to exploring state
		game->StateManager()->ChangeState(ExploringState::Instance());
	}

	void MapState::Header(){
		std::cout << "\n\n";
		std::cout << "\tTEMPLE OF DOOM > MAP \n";
		std::cout << "\t----------------------------------------------------------------\n\n";
	}

	std::string MapState::StringMerger(std::string leftstring, std::string rightstring){
		std::string mergedString;
		std::vector<std::string> leftlines = SplitIntoLines(leftstring);
		std::vector<std::string> rightlines = SplitIntoLines(rightstring);

		for (size_t i = 0, size = leftlines.size(); i < size; i++){
			mergedString += leftlines[i] + (i < rightlines.size() ? rightlines[i] : "") + "\n";
		}

		return mergedString;
	}

	std::vector<std::string> MapState::SplitIntoLines(std::string text){
		std::stringstream ss(text);
		std::string to;
		std::vector<std::string> lines;

		if (!text.empty())
		{
			while (std::getline(ss, to, '\n')){
				lines.push_back(to);
			}
		}
		return lines;
	}
}
