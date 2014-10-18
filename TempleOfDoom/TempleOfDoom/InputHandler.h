#pragma once

#include <vector>
#include <string>

namespace TOD {
	class InputHandler
	{
	public:
		InputHandler();
		virtual ~InputHandler();

		std::vector<std::string> GetCommands();
	private:
		std::string input;
	};
}