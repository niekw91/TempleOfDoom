#pragma once

#include <vector>
#include "NPC.h"
#include "Item.h"
#include "ItemKind.h"
#include "Scenery.h"
#include "Trap.h"
#include "Weapon.h"
#include "Armor.h"
#include "Medkit.h"

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

		Weapon* GetRandomWeapon();
		Armor* GetRandomArmor();
		Medkit* GetRandomMedkit();
		Scenery* GetRandomScenery();
		NPC* GetRandomNPC();
		Trap* GetRandomTrap();

	private:
		std::vector<NPC*> npcVector;
		std::vector<Scenery*> sceneryVector;
		std::vector<Trap*> trapVector;

		// Item vectors
		std::vector<Weapon*> weaponVector;
		std::vector<Armor*> armorVector;
		std::vector<Medkit*> medkitVector;
	};
}

