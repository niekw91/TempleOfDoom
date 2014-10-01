#pragma once

#include <vector>

namespace TOD {
	// Forward declaration
	class Game;
	class GameState;

	class GameStateManager
	{
	public:
		GameStateManager();
		virtual ~GameStateManager();

		void Init();
		void Cleanup();

		void ChangeState(GameState *state);
		void PushState(GameState *state);
		void PopState();

		void Update(Game *game);
		void Render(Game *game);

	private:
		std::vector<GameState*> states;
	};
}