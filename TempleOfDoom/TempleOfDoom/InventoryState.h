#pragma once
#include "GameState.h"

#include <string>
#include <vector>

namespace TOD {
	class Game;
	class Player;
	class Options;

	class InventoryState :
		public GameState
	{
	public:
		void Init(Game *game);
		void Cleanup(Game *game);

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
		void ActionEquip(Game *game);
		void ActionDelete(Game *game);
		void ActionUse(Game *game);

		void RemoveItem(Player *player, int index);

		std::string inventory;
	};
}

