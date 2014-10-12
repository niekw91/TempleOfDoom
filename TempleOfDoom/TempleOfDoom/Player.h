#pragma once
#include "Character.h"

namespace TOD {
	class Player :
		public Character
	{

	public:
		Player(std::string name);
		virtual ~Player();

		std::string GetName(){ return _name; }
		int GetLevel() { return _level; }
		int GetHP() { return _hp; }
		int GetXP() { return _xp; }
		int GetStr() { return _str; }
		int GetDef() { return _def; }
		int GetVigilance() { return _vigilance; }
		std::vector<GameObject> GetInventory() {return _inventory; }

	private:
		std::string _name;
		int _level;
		int _hp;
		int _xp;
		int _str;
		int _def;
		int _vigilance;
		std::vector<GameObject> _inventory;
	};
}

