#include "stdafx.h"
#include "Wearable.h"

namespace TOD {
	Wearable::Wearable(ItemType *type) : Item(type) {
		
	}


	Wearable::~Wearable()
	{
	}

	std::string Wearable::ToString() {
		return name;
	}
}
