#pragma once
#include "GameObject.h"

#include <string>

namespace TOD {
	class Trap :
		public GameObject
	{

	public:
		Trap(std::string name, int damage);
		virtual ~Trap();

		int GetDamage();
		std::string ToString();
	private:
		int damage;
	};
}

