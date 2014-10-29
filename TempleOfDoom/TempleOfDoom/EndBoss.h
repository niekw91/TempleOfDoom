#pragma once
#include "NPC.h"

namespace TOD {
	class NPCType;

	class EndBoss :
		public NPC
	{
	public:
		EndBoss(NPCType *type);
		virtual ~EndBoss();
	};
}

