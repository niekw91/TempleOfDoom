#pragma once
#include "GameState.h"

namespace TOD {
	// Forward declaration
	class Game;

	class GameOverState : public GameState
	{
	public:
		void Init(Game *game);
		void Cleanup(Game *game);

		void Update(Game *game);
		void Render(Game *game);

		static GameOverState *Instance() { return &instance; }

	protected:
		GameOverState() { }

	private:
		static GameOverState instance;

		void Generate(Game *game);
		void Do(Game *game);
	};
}