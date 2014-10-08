#pragma once
#include "GameObject.h"

#include <vector>

namespace TOD {
	class Item;

	class Character :
		public GameObject
	{

	public:
		Character();
		virtual ~Character();

		int getHP();
		int getAttack();
		int getDefense();
		int getLevel();

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

