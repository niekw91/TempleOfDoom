#pragma once
#include "Wearable.h"

#include <string>

namespace TOD {
	class ItemType;

	class Armor :
		public Wearable
	{

	public:
		Armor(ItemType *type);
		virtual ~Armor();

		std::string ToString();
	private:
		int defense;
	};
}

