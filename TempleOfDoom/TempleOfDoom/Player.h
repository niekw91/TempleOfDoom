#pragma once
#include "Character.h"

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

	private:
		std::string name;
		int level;
		int hp;
		int xp;
		int str;
		int def;
		int vigilance;
		std::vector<Item*> inventory;
	};
}

