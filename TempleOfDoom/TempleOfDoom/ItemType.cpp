#include "stdafx.h"
#include "ItemType.h"
#include "Item.h"
#include "ItemKind.h"
#include "Weapon.h"

namespace TOD {
	Item* ItemType::CreateItem() {
		switch (kind)
		{
		case WEAPON:
			return new Weapon(this);
			break;
		default:
			break;
		}
		return new Item(this);
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