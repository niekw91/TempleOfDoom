#pragma once
#include "GameState.h"

#include <string>
#include <vector>

namespace TOD {
	class MapState :
		public GameState
	{

	public:
		void Init();
		void Cleanup();

		void Update(Game *game);
		void Render(Game *game);

		static MapState *Instance() { return &instance; }

	protected:
		MapState() { }

	private:
		static MapState instance;

		std::string map;

		void Generate(Game *game);
		void Do(Game *game);

		enum input { INVALID, BACK };

		void Header();
		std::string StringMerger(std::string leftstring, std::string rightstring);
		std::vector<std::string> MapState::SplitIntoLines(std::string text);
	};
}
