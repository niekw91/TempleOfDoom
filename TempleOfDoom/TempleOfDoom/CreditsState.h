#pragma once
#include "GameState.h"

namespace TOD {
	// Forward declaration
	class Game;

	class CreditsState : public GameState
	{
	public:
		void Init(Game *game);
		void Cleanup(Game *game);

		void Update(Game *game);
		void Render(Game *game);

		static CreditsState *Instance() { return &instance; }

	protected:
		CreditsState() { }

	private:
		static CreditsState instance;

		void Generate(Game *game);
		void Do(Game *game);

	};
}