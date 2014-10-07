#pragma once

#include <vector>
#include "NPC.h"
#include "Item.h"

namespace TOD {
	class GameObjectFactory
	{
	public:
		GameObjectFactory();
		virtual ~GameObjectFactory();
		
		void LoadNPCFromFile(std::string fileName);
		void LoadItemsFromFile(std::string fileName);
		NPC* GetRandomNPC();

	private:
		std::vector<NPC*> npcVector;
		std::vector<Item*> itemVector;
	};
}

