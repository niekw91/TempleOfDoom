#pragma once
#include "GameState.h"

namespace TOD {
	// Forward declaration
	class Game;

	class VictoryState : public GameState
	{
	public:
		void Init(Game *game);
		void Cleanup(Game *game);

		void Update(Game *game);
		void Render(Game *game);

		static VictoryState *Instance() { return &instance; }

	protected:
		VictoryState() { }

	private:
		static VictoryState instance;

		void Generate(Game *game);
		void Do(Game *game);
	};
}