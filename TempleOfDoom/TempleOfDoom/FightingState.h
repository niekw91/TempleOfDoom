#pragma once
#include "GameState.h"

namespace TOD {

	// Forward declaration
	class Game;
	class InputHandler;

	class FightingState : public GameState
	{
	public:
		void Init(Game *game);
		void Cleanup(Game *game);

		void Update(Game *game);
		void Render(Game *game);

		static FightingState *Instance() { return &instance; }

	protected:
		FightingState() { }

	private:
		static FightingState instance;

		void Generate(Game *game);
		void Do(Game *game);

		void Header();

		bool juststarted;

		InputHandler *input;
	};
}

