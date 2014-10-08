#pragma once
#include "Item.h"

namespace TOD {
	class ItemType;
	class Item;

	class Wearable :
		public Item
	{

	public:
		Wearable(ItemType *type);
		virtual ~Wearable();
	};
}

