#pragma once
#include "World.h"

namespace TOD {
	class Game
	{

	public:
		Game();
		virtual ~Game();
		void CreateWorld();

	private:
		bool running;
		World *world;

		void Start();
		void Stop();
		void Update();
		void Render();
	};
}


