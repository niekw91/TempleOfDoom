#pragma once
#include "GameState.h"

#include "Room.h"

namespace TOD {
	// Forward declaration
	class Game;

	class ExploringState : public GameState
	{
	public:
		void Init();
		void Cleanup();

		void Update(Game *game);
		void Render(Game *game);

		static ExploringState *Instance() { return &instance; }

	protected:
		ExploringState() { }

	private:
		static ExploringState instance;

		void Generate(Game *game);
		void Do(Game *game);

		void Header();
		void ActionRun(Game *game);
		void MoveTo(Room *currRoom, Room *room);

		std::string RenderScenery(Room* currRoom);
		std::string RenderExits(Room* currRoom);
		std::string RenderNPCs(Room* currRoom);

		std::string RandomExitString();
	};
}