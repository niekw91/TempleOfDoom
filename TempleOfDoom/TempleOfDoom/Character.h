#pragma once
#include "GameObject.h"

#include <vector>

namespace TOD {
	class Item;
	class Player;

	class Character :
		public GameObject
	{

	public:
		Character(std::string name);
		virtual ~Character();

		int getLevel() { return level; }
		int getMaxHP() { return maxhp * level; }
		int getHP() { return hp; }
		int getXp() { return xp; }
		int getAttack() { return attack * level; }
		int getDefense() { return defense * level; }
		
		bool isDead() { return _isDead; }
		void TakeDamage(int attack) { 
			hp = hp - attack > 0 ? hp - attack : 0;
			this->_isDead = hp > 0 ? false : true; 
		}

		int Attack(Player* c);
		int GiveXp();
		
	protected:
		int level;
		int maxhp;
		int hp;
		int xp;
		int attack;
		int defense;

		std::vector<Item*> inventory;

		bool _isDead = false;
	};
}

