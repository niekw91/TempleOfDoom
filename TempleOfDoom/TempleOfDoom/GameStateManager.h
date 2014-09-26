#pragma once
#include "GameState.h"

#include <vector>
using namespace std;

namespace TOD {
	class GameStateManager
	{
	public:
		GameStateManager();
		virtual ~GameStateManager();
		void Init();

		void ChangeState(GameState* state);
		void PushState(GameState* state);
		void PopState();

	private:
		vector<GameState*> states;
	};
}

