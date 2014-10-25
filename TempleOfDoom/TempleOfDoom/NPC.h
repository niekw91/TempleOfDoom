#pragma once
#include "Character.h"

namespace TOD {
	class NPCType;

	class NPC :
		public Character
	{

	public:
		NPC(std::string name, int hp, int attack, int defense, int level);
		NPC(NPCType *type);
		virtual ~NPC();


	private:

	};
}

