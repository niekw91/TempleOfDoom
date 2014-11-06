#pragma once

#include "GameState.h"

namespace TOD {
	// Forward declaration
	class Game;
	class Options;

	class MainMenuState : public GameState
	{
	public:
		void Init(Game *game);
		void Cleanup(Game *game);

		void Update(Game *game);
		void Render(Game *game);

		static MainMenuState *Instance() { return &instance; }

		static void StopGame(bool stop);
		static bool IsStopped() { return stopGame; }

	protected:
		MainMenuState() { }

	private:
		static MainMenuState instance;
		static bool stopGame;

		void Generate(Game *game);
		void Do(Game *game);

		std::string stateOptions;

		enum input { INVALID, NEWGAME, LOADGAME, CREDITS, QUIT };
		input Hash(std::string const& inString);

		void LoadGame(Game *game);
		void NewGame(Game *game, Player *player = nullptr, bool skipName = false);
		void Credits(Game *game);

	};
}