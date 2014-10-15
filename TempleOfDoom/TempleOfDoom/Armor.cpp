#include "stdafx.h"
#include "Armor.h"
#include "ItemType.h"

namespace TOD {
	Armor::Armor(ItemType *type) : Wearable(type) {
		this->defense = type->GetRating();
	}


	Armor::~Armor()
	{
	}

	std::string Armor::ToString() {
		return name + " - defense [" + std::to_string(defense) + "]";
	}
}
