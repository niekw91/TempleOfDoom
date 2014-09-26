#pragma once

namespace TOD {
	class GameState
	{

	public:
		GameState();
		virtual ~GameState();

		virtual void Init() = 0;
		virtual void Cleanup() = 0;

		//virtual void Update(Game* game) = 0;
		//virtual void Render(Game* game) = 0;

		//void ChangeState(Game* game, GameState* state) {
			//game->ChangeState(state);
		//}
	};
}

