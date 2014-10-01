#pragma once

#include "GameState.h"

namespace TOD {
	// Forward declaration
	class Game;

	class MainMenuState : public GameState
	{
	public:
		void Init();
		void Cleanup();

		void Update(Game *game);
		void Render(Game *game);

		static MainMenuState *Instance() { return &instance; }

	protected:
		MainMenuState() { }

	private:
		static MainMenuState instance;

		void Generate(Game *game);
		void Do(Game *game);

		enum input { NEWGAME = 1, LOADGAME, CREDITS, INVALID };
		input Hash(std::string const& inString);

		void NewGame(Game *game);
		void LoadGame(Game *game);
		void Credits(Game *game);
	};
}