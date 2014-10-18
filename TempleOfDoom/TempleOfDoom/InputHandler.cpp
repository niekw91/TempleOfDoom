#include "stdafx.h"
#include "InputHandler.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>

namespace TOD {
	InputHandler::InputHandler()
	{
		// Read input
		std::getline(std::cin, input);
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	}

	InputHandler::~InputHandler()
	{
	}

	std::vector<std::string> InputHandler::GetCommands() {
		std::vector<std::string> commands;

		// Create commands
		std::stringstream ss(input);
		std::string to;

		if (!input.empty()) {
			while (std::getline(ss, to, ' ')) {
				std::transform(to.begin(), to.end(), to.begin(), ::tolower);
				commands.push_back(to);
			}
		}

		return commands;
	}
}