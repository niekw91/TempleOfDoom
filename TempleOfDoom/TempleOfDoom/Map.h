#pragma once
#include "Usable.h"

#include <string>

namespace TOD {
	class ItemType;

	class Map :
		public Usable
	{

	public:
		Map(ItemType *type);
		virtual ~Map();

		std::string ToString();
	};
}

