#pragma once
#include "GameObject.h"

namespace TOD {

	class Scenery :
		public GameObject
	{

	public:
		Scenery(std::string name) : GameObject(name) {};
		virtual ~Scenery();
	};
}

