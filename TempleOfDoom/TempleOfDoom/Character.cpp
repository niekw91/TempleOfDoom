#include "stdafx.h"
#include "Character.h"
#include "Item.h"

#include <vector>

namespace TOD {
	Character::Character() {
		inventory = std::vector<Item*>();
	}


	Character::~Character()
	{
	}
}
