#include "stdafx.h"
#include "InputHandler.h"
#include <vector>
#include <sstream>
#include <algorithm>

namespace TOD {
	InputHandler::InputHandler()
	{
	}

	InputHandler::~InputHandler()
	{
	}

	void InputHandler::Read(std::string input) {
		std::stringstream ss(input);
		std::string to;

		if (!input.empty()) {
			while (std::getline(ss, to, ' ')) {
				std::transform(to.begin(), to.end(), to.begin(), ::tolower);
				commands.push_back(to);
			}
		}
	}
}