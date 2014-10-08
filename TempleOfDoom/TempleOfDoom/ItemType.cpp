#include "stdafx.h"
#include "ItemType.h"
#include "Item.h"
#include "ItemKind.h"
#include "Weapon.h"
#include "Armor.h"
#include "Medkit.h"

namespace TOD {
	Item* ItemType::CreateItem() {
		switch (kind)
		{
		case WEAPON:
			return new Weapon(this);
			break;
		case ARMOR:
			return new Armor(this);
			break;
		case MEDKIT:
			return new Medkit(this);
			break;
		default:
			break;
		};
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