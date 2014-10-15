#pragma once
#include "Item.h"

#include <string>

namespace TOD {
	class ItemType;
	class Item;

	class Wearable :
		public Item
	{

	public:
		Wearable(ItemType *type);
		virtual ~Wearable();

		std::string ToString();
	};
}

