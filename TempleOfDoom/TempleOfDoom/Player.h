#pragma once
#include "Character.h"
#include "Weapon.h"
#include "Armor.h"

namespace TOD {
	class Player :
		public Character
	{
	public:
		Player(std::string name);
		virtual ~Player();

		int GetVigilance() { return vigilance; }
		std::vector<Item*> GetInventory() {return inventory; }

		bool PickUp(Item *item);
		void Equip(Weapon *weapon);
		void Equip(Armor *armor);
		Weapon* GetWeapon() { return weapon; }
		Armor* GetAmor() { return armor;  }
	private:
		int vigilance;
		
		Weapon *weapon;
		Armor *armor;
		std::vector<Item*> inventory;

		// Inventory size
		const int invSize = 20;
	};
}

