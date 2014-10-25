#include "stdafx.h"
#include "Item.h"
#include "ItemType.h"

namespace TOD {
	Item::Item(std::string name, bool rare) : GameObject(name) {
		this->rare = rare;
	}

	Item::Item(ItemType *type) : GameObject(type->GetName()) {
		rare = type->GetRare();
	}

	bool Item::GetRare() {
		return rare;
	}

	Item::~Item()
	{
	}
}
