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
		std::vector<std::string> GetOptions() { return options; }

	private:
		int choice;
		std::vector<std::string> options;

		void ProcessOptions(std::string optionsstring);
		void GenerateMenu();
		void HandleInput(std::vector<std::string> options);
	};
}