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

		std::string GetName(){ return name; }
		int GetLevel() { return level; }
		int GetHP() { return hp; }
		int GetXP() { return xp; }
		int GetStr() { return str; }
		int GetDef() { return def; }
		int GetVigilance() { return vigilance; }
		std::vector<Item*> GetInventory() {return inventory; }

		bool PickUp(Item *item);
		void Equip(Weapon *weapon);
		void Equip(Armor *armor);
		Weapon* GetWeapon() { return weapon; }
		Armor* GetAmor() { return armor;  }
	private:
		std::string name;
		int level;
		int hp;
		int xp;
		int str;
		int def;
		int vigilance;
		
		Weapon *weapon;
		Armor *armor;
		std::vector<Item*> inventory;

		// Inventory size
		const int invSize = 20;
	};
}

