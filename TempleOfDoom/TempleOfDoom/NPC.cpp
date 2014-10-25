#include "stdafx.h"
#include "NPC.h"
#include "NPCType.h"

namespace TOD {
	NPC::NPC(std::string name, int hp, int attack, int defense, int level) : Character(name) {
		this->hp = hp;
		this->attack = attack;
		this->defense = defense;
		this->level = level;
	}

	NPC::NPC(NPCType *type) : Character(type->getName()) {
		hp = type->getHP();
		attack = type->getAttack();
		defense = type->getDefense();
		level = type->getLevel();
	}

	NPC::~NPC()
	{
	}
}