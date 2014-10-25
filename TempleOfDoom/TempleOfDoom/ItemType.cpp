#include "stdafx.h"
#include "ItemType.h"
#include "Item.h"
#include "ItemKind.h"
#include "Weapon.h"
#include "Armor.h"
#include "Medkit.h"

namespace TOD {
	Weapon* ItemType::CreateWeapon() {
		return new Weapon(this);
	}

	Armor* ItemType::CreateArmor() {
		return new Armor(this);
	}

	Medkit* ItemType::CreateMedkit() {
		return new Medkit(this);
	}

	ItemType::~ItemType()
	{
	}

	int ItemType::GetRating() {
		return rating;
	}

	bool ItemType::GetRare() {
		return rare;
	}

	std::string ItemType::GetName() {
		return name;
	}
}