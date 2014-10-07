#include "stdafx.h"
#include "NPCType.h"
#include "NPC.h"

namespace TOD {
	TOD::NPC* NPCType::createNPC() {
		return new NPC(this);
	}

	NPCType::~NPCType()
	{
	}

	int NPCType::getAttack() {
		return attack;
	}

	int NPCType::getDefense() {
		return defense;
	}

	std::string NPCType::getName() {
		return name;
	}

	int NPCType::getLevel() {
		return level;
	}

	int NPCType::getHP() {
		return hp;
	}
}
