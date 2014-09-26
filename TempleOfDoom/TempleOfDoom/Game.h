#pragma once
#include "World.h"
#include "GameStateManager.h"

namespace TOD {
	class Game
	{

	public:
		Game();
		virtual ~Game();
		void CreateWorld();
		void Init();
		void ChangeState(GameState* state);
		void Start();

	private:
		bool running;
		World *world;
		GameStateManager *stateManager;
		void MainMenu();
		void Stop();
		void Update();
		void Render();
	};
}


