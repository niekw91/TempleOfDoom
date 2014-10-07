#pragma once

#include <string>

namespace TOD {
	class GameObject
	{

	public:
		GameObject();
		virtual ~GameObject();

	protected:
		std::string name;
	};
}

