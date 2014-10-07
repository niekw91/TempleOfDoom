#include "stdafx.h"
#include "Weapon.h"
#include "ItemType.h"

namespace TOD {
	Weapon::Weapon(ItemType *type) {
		damage = type->GetRating();
	}


	Weapon::~Weapon()
	{
	}
}
