#include "stdafx.h"
#include "Options.h"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <unordered_set>

namespace TOD 
{
	Options::Options(std::string optionsstring, bool showmenu = true) {
		// Process options
		ProcessOptions(optionsstring);

		// Generate options menu
		if (showmenu)
			GenerateMenu();

		// Handle input
		HandleInput(options);
	}

	Options::~Options()
	{
	}

	void Options::ProcessOptions(std::string optionsstring) {
		std::stringstream ss(optionsstring);
		std::string to;

		if (!optionsstring.empty()) {
			while (std::getline(ss, to, ';')) {
				std::transform(to.begin(), to.end(), to.begin(), ::toupper);
				this->options.push_back(to);
			}
		}
	}

	void Options::GenerateMenu() {
		std::string menu = "\t[ ";
		for (auto option : this->options) {
			menu += option + " | ";
		}
		menu.erase(menu.size() - 3);
		menu += " ]\n\n";
		std::cout << menu;
	}

	void Options::HandleInput(std::vector<std::string> options)
	{
		std::cout << "\t";
		std::string input;
		std::getline(std::cin, input);
		std::transform(input.begin(), input.end(), input.begin(), ::toupper);
		
		for (size_t i = 0, size = options.size(); i < size; i++) {
			if (options[i] == input) {
				this->choice = i + 1;
				break;
			}
		}
	}
}