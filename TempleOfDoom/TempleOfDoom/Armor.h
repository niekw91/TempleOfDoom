#pragma once
#include "Wearable.h"

namespace TOD {
	class ItemType;

	class Armor :
		public Wearable
	{

	public:
		Armor(ItemType *type);
		virtual ~Armor();
	};
}

