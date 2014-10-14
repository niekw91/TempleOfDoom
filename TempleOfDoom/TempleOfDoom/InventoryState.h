#pragma once
#include "GameState.h"

#include <string>

namespace TOD {
	class Game;

	class InventoryState :
		public GameState
	{
	public:
		void Init();
		void Cleanup();

		void Update(Game *game);
		void Render(Game *game);

		static InventoryState *Instance() { return &instance; }

	protected:
		InventoryState() { }

	private:
		static InventoryState instance;

		void Generate(Game *game);
		void Do(Game *game);

		void Header();

		std::string inventory;
	};
}

