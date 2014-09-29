#pragma once

#include "GameState.h"

namespace TOD {
	class MainMenuState : public GameState
	{
	public:
		void Init();
		void Cleanup();

		void HandleEvents();
		void Update();
		void Render();

		void ClearScreen();

		static MainMenuState* Instance() {
			return &m_MainMenuState;
		}

	protected:
		MainMenuState() { }

	private:
		static MainMenuState m_MainMenuState;
	};
}