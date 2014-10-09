#pragma once
#include "Character.h"

namespace TOD {
	class Player :
		public Character
	{

	public:
		Player(std::string name);
		virtual ~Player();

	private:
		int vigilance;
		int xp;
	};
}

