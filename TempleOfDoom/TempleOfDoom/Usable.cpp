#include "stdafx.h"
#include "Usable.h"

namespace TOD {
	Usable::Usable(ItemType *type) : Item(type) {
	}


	Usable::~Usable()
	{
	}

	std::string Usable::ToString() {
		return name;
	}
}
