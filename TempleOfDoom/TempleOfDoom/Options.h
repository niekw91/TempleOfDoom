#pragma once

#include <string>
#include <vector>

namespace TOD {

	class Options
	{
	public:
		Options(std::string options, bool showmenu);
		virtual ~Options();

		int GetChoice() { return choice; }

	private:
		int choice;

		std::vector<std::string> ProcessOptions(std::string optionsstring);
		void GenerateMenu(std::vector<std::string> options);
		void HandleInput(std::vector<std::string> options);
	};
}