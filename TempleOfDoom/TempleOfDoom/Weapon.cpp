#include "stdafx.h"
#include "Weapon.h"
#include "ItemType.h"

#include <string>

namespace TOD {
	Weapon::Weapon(ItemType *type) : Wearable(type) {
		damage = type->GetRating();
	}


	Weapon::~Weapon()
	{
	}

	int Weapon::GetDamage() {
		return damage;
	}

	std::string Weapon::ToString() {
		return name + " - damage [" + std::to_string(damage) + "]";
	}
}
