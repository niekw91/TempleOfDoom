#include "stdafx.h"
#include "Item.h"
#include "ItemType.h"

namespace TOD {
	Item::Item(ItemType *type) {
		name = type->GetName();
		rare = type->GetRare();
	}


	Item::~Item()
	{
	}
}
