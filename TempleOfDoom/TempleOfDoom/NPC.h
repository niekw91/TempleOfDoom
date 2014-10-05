#pragma once
#include "Character.h"

namespace TOD {
	class NPCType;

	class NPC :
		public Character
	{

	public:
		NPC(NPCType& type) : type(type)
		{
			//hp = type.getHP();
			//name = type.getName();
			//attack = type.getAttack();
			//defense = type.getDefense();
			//level = type.getLevel();
		}
		virtual ~NPC();


	private:
		NPCType& type;
	};
}

