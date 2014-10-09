#pragma once
#include "GameObject.h"

namespace TOD {
	class Trap :
		public GameObject
	{

	public:
		Trap(std::string name, int damage);
		virtual ~Trap();
	private:
		int damage;
	};
}

