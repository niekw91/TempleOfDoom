#pragma once
#include "Character.h"

namespace TOD {
	class NPCType;

	class NPC :
		public Character
	{

	public:
		NPC(NPCType *type);
		virtual ~NPC();


	private:

	};
}

