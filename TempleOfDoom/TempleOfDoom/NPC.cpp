#include "stdafx.h"
#include "NPC.h"
#include "NPCType.h"

namespace TOD {
	NPC::NPC(NPCType *type) {
		name = type->getName();
		hp = type->getHP();
		attack = type->getAttack();
		defense = type->getDefense();
		level = type->getLevel();
	}

	NPC::~NPC()
	{
	}
}