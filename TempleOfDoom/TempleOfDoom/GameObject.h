#pragma once

#include <string>

namespace TOD {
	class GameObject
	{

	public:
		GameObject(std::string name);
		virtual ~GameObject();

		std::string GetName() { return name; }

	protected:
		std::string name;
	};
}

