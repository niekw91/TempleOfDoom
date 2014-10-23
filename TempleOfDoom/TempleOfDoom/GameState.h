#pragma once

namespace TOD {
	// Forward declaration
	class Game;

	class GameState
	{
	public:
		virtual void Init(Game *game) = 0;
		virtual void Cleanup(Game *game) = 0;

		virtual void Update(Game *game) = 0;
		virtual void Render(Game *game) = 0;

		void ChangeState(Game* game, GameState* state);

		void ClearScreen();
		void PauseScreen();

	protected:
		GameState() { }
	};
}