#pragma once
#include "Item.h"

namespace TOD {
	class ItemType;

	class Usable :
		public Item
	{

	public:
		Usable(ItemType *type);
		virtual ~Usable();
	};
}

