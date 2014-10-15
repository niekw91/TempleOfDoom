#pragma once
#include "Item.h"

#include <string>

namespace TOD {
	class ItemType;

	class Usable :
		public Item
	{

	public:
		Usable(ItemType *type);
		virtual ~Usable();

		std::string ToString();
	};
}

