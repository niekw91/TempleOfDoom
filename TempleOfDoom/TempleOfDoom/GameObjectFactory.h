#pragma once

#include <vector>
#include "NPC.h"
#include "Item.h"
#include "ItemKind.h"
#include "Scenery.h"
#include "Trap.h"

namespace TOD {
	class GameObjectFactory
	{
	public:
		GameObjectFactory();
		virtual ~GameObjectFactory();
		
		ItemKind GetItemKind(std::string str);

		void LoadNPCFromFile(std::string fileName);
		void LoadItemsFromFile(std::string fileName);
		void LoadSceneryFromFile(std::string fileName);
		void LoadTrapsFromFile(std::string fileName);
		Item* GetRandomItem();
		Scenery* GetRandomScenery();
		NPC* GetRandomNPC();
		Trap* GetRandomTrap();

	private:
		std::vector<NPC*> npcVector;
		std::vector<Item*> itemVector;
		std::vector<Scenery*> sceneryVector;
		std::vector<Trap*> trapVector;
	};
}

