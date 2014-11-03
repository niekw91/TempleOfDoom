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

		int GetLevel() { return level; }
		int GetMaxHP() { return maxhp; }
		int GetHP() { return hp; }
		int GetXp() { return xp; }
		int GetAttack() { return attack * level; }
		int GetDefense() { return defense * level; }
		
		bool IsDead() { return _isDead; }
		bool TakeDamage(int attack);

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

