#include "stdafx.h"
#include "Medkit.h"

namespace TOD {
	Medkit::Medkit(ItemType *type) : Usable(type) {
	}


	Medkit::~Medkit()
	{
	}

	std::string Medkit::ToString() {
		return name;
	}
}
