#include "stdafx.h"
#include "Trap.h"

namespace TOD {
	Trap::Trap(std::string name, int damage) : GameObject(name) {
		this->damage = damage;
	}

	Trap::~Trap()
	{
	}
}
