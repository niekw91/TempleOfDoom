#pragma once
#include "Wearable.h"

#include <string>

namespace TOD {
	class ItemType;

	class Weapon :
		public Wearable
	{

	public:
		Weapon(ItemType *type);
		virtual ~Weapon();

		int GetDamage();
		std::string ToString();
	private:
		int damage;
	};
}

