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
#include "EndBoss.h"

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
		void LoadBossFromFile(std::string fileName);
		void LoadExitsFromFile(std::string fileName);

		Weapon* GetRandomWeapon();
		Armor* GetRandomArmor();
		Medkit* GetRandomMedkit();
		Scenery* GetRandomScenery();
		NPC* GetRandomNPC(int minLevel, int maxLevel);
		Trap* GetRandomTrap();
		EndBoss* GetRandomBoss();
		std::string GetRandomExitString();

	private:
		std::vector<ItemType*> tempTypes;
		std::vector<NPCType*> tempNPC;

		std::vector<std::string> exitVector;

		std::vector<NPC*> npcVector;
		std::vector<Scenery*> sceneryVector;
		std::vector<Trap*> trapVector;
		std::vector<EndBoss*> bossVector;

		// Item vectors
		std::vector<Weapon*> weaponVector;
		std::vector<Armor*> armorVector;
		std::vector<Medkit*> medkitVector;
	};
}

