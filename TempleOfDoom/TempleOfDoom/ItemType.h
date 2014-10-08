#pragma once

#include <string>
#include "ItemKind.h"

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

		TOD::Item* CreateItem();
	private:
		ItemKind kind;
		std::string name;
		int rating;
		bool rare;
	};
}

