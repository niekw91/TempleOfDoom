#pragma once

namespace TOD {
	class Game
	{

	public:
		Game();
		virtual ~Game();

	private:
		bool running;
		void Start();
		void Stop();
		void Update();
		void Render();
	};
}


