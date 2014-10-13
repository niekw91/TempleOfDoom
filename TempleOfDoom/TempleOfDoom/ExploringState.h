#pragma once
#include "GameState.h"

namespace TOD {
	// Forward declaration
	class Game;

	class ExploringState : public GameState
	{
	public:
		void Init();
		void Cleanup();

		void Update(Game *game);
		void Render(Game *game);

		static ExploringState *Instance() { return &instance; }

	protected:
		ExploringState() { }

	private:
		static ExploringState instance;

		void Generate(Game *game);
		void Do(Game *game);

		enum input { INVALID, FIGHT, RUN, EXPLORE, REST, INVENTORY, MAP, QUIT };

		void Header();
		void ActionRun(Game *game);
	};
}