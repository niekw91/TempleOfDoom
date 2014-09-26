#pragma once
#include "Character.h"

namespace TOD {
	class Player :
		public Character
	{

	public:
		Player();
		virtual ~Player();

	private:
		int vigilance;
		int xp;
	};
}

