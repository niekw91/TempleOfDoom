#pragma once

#include "GameState.h"

namespace TOD {
	// Forward declaration
	class Game;

	class MainMenuState : public GameState
	{
	public:
		void Init(Game *game);
		void Cleanup(Game *game);

		void Update(Game *game);
		void Render(Game *game);

		static MainMenuState *Instance() { return &instance; }

	protected:
		MainMenuState() { }

	private:
		static MainMenuState instance;

		void Generate(Game *game);
		void Do(Game *game);

		std::string stateOptions;

		enum input { INVALID, NEWGAME, LOADGAME, CREDITS, QUIT };
		input Hash(std::string const& inString);

		void LoadGame(Game *game);
		void NewGame(Game *game);
		void Credits(Game *game);
	};
}