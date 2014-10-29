#include "stdafx.h"
#include "NPCType.h"
#include "NPC.h"
#include "EndBoss.h"

namespace TOD {
	TOD::NPC* NPCType::createNPC() {
		return new NPC(this);
	}

	TOD::EndBoss* NPCType::createBoss() {
		return new EndBoss(this);
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
