#pragma once

#include <string>

namespace TOD {
	class NPC;
	class EndBoss;

	class NPCType
	{

	public:
		NPCType(std::string name, int hp, int attack, int defense, int level)
			: name(name), hp(hp), attack(attack), defense(defense), level(level)
		{}
		virtual ~NPCType();

		int getHP();
		int getAttack();
		int getDefense();
		int getLevel();
		std::string getName();

		TOD::NPC* createNPC();
		TOD::EndBoss* createBoss();
	private:
		std::string name;
		int hp;
		int attack;
		int defense;
		int level;
	};
}

