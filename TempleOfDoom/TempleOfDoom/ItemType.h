#pragma once

#include <string>
#include "ItemKind.h"
#include "Weapon.h"
#include "Armor.h"
#include "Medkit.h"

namespace TOD {
	class Item;

	class ItemType
	{
	public:
		ItemType(std::string name, int rating, bool rare, ItemKind kind)
			: name(name), rating(rating), rare(rare), kind(kind)
		{}
		virtual ~ItemType();

		bool GetRare();
		int GetRating();
		std::string GetName();

		Weapon* CreateWeapon();
		Armor* CreateArmor();
		Medkit* CreateMedkit();
	private:
		ItemKind kind;
		std::string name;
		int rating;
		bool rare;
	};
}

