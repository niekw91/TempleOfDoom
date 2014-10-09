#pragma once

#include <string>

namespace TOD {
	class GameObject
	{

	public:
		GameObject(std::string name);
		virtual ~GameObject();

	protected:
		std::string name;
	};
}

