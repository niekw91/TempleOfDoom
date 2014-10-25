#include "stdafx.h"
#include "Medkit.h"
#include "ItemType.h"

namespace TOD {
	Medkit::Medkit(ItemType *type) : Usable(type) {
		this->hp = type->GetRating();
	}


	Medkit::~Medkit()
	{
	}

	int Medkit::GetHp() {
		return hp;
	}

	std::string Medkit::ToString() {
		return name;
	}
}
