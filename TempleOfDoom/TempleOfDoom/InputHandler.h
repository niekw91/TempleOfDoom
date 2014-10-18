#pragma once

#include <string>
#include <vector>

namespace TOD {
	class InputHandler
	{
	public:
		InputHandler();
		virtual ~InputHandler();

		void Read(std::string);
		std::vector<std::string> GetCommands() { return commands; }

	private:
		std::vector<std::string> commands;
	};
}