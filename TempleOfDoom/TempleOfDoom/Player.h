#pragma once
#include "Character.h"
#include "Weapon.h"
#include "Armor.h"
#include "NPC.h"
#include "Room.h"
#include "Medkit.h"

namespace TOD {
	class Player :
		public Character
	{
	public:
		Player(std::string name, int level, int attack, int defense, int xp, int hp, int maxHp, int vigilance);
		Player(std::string name);
		virtual ~Player();

		int GetVigilance() { return vigilance; }
		std::vector<Item*> *GetInventory() { return inventory; }

		bool PickUp(Item *item);
		void Equip(Weapon *weapon);
		void Equip(Armor *armor);
		int Attack(Character *c);
		bool SearchTrap(Room *room);
		void Heal(Medkit *medkit);
		int Rest();

		Weapon* GetWeapon() { return weapon; }
		Armor* GetAmor() { return armor;  }

		void ReceiveXp(int givenxp);

	private:
		int vigilance;
		
		Weapon *weapon;
		Armor *armor;
		std::vector<Item*> *inventory;

		// Inventory size
		const int invSize = 20;

		int NextLevel();
		int GainHp(int hp);
		void GainStats();
	};
}

