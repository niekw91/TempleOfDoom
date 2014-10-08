#pragma once

#include <vector>
#include "NPC.h"
#include "Item.h"
#include "ItemKind.h"

namespace TOD {
	class GameObjectFactory
	{
	public:
		GameObjectFactory();
		virtual ~GameObjectFactory();
		
		ItemKind GetItemKind(std::string str);

		void LoadNPCFromFile(std::string fileName);
		void LoadItemsFromFile(std::string fileName);
		Item* GameObjectFactory::GetRandomItem();
		NPC* GetRandomNPC();

	private:
		std::vector<NPC*> npcVector;
		std::vector<Item*> itemVector;
	};
}

