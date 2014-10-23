#pragma once

#include <vector>

namespace TOD {
	// Forward declaration
	class Game;
	class GameState;

	class GameStateManager
	{
	public:
		GameStateManager(Game *game);
		virtual ~GameStateManager();

		void Init(Game *game);
		void Cleanup(Game *game);

		void ChangeState(Game *game, GameState *state);
		void PushState(Game *game, GameState *state);
		void PopState(Game *game);

		void Update(Game *game);
		void Render(Game *game);

	private:
		std::vector<GameState*> states;
	};
}