#include "stdafx.h"
#include "Item.h"
#include "ItemType.h"

namespace TOD {
	Item::Item(ItemType *type) : GameObject(type->GetName()) {
		rare = type->GetRare();
	}


	Item::~Item()
	{
	}
}
