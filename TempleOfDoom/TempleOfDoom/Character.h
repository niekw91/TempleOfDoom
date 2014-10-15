#pragma once
#include "GameObject.h"

#include <vector>

namespace TOD {
	class Item;

	class Character :
		public GameObject
	{

	public:
		Character(std::string name);
		virtual ~Character();

		int getHP() { return hp; }
		int getAttack() { return attack; }
		int getDefense() { return defense; }
		int getLevel() { return level; }

	protected:
		int hp;
		int accuracy;
		int agility;
		int attack;
		int defense;
		std::vector<Item*> inventory;
		int level;
	};
}

