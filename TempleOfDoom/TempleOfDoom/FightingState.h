#pragma once
#include "GameState.h"

namespace TOD {

	// Forward declaration
	class Game;

	class FightingState : public GameState
	{
	public:
		void Init();
		void Cleanup();

		void Update(Game *game);
		void Render(Game *game);

		static FightingState *Instance() { return &instance; }

	protected:
		FightingState() { }

	private:
		static FightingState instance;

		void Generate();
		void Do(Game *game);
	};
}

