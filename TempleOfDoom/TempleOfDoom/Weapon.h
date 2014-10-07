#pragma once
#include "Wearable.h"

namespace TOD {
	class ItemType;

	class Weapon :
		public Wearable
	{

	public:
		Weapon(ItemType *type);
		virtual ~Weapon();
	private:
		int damage;
	};
}

