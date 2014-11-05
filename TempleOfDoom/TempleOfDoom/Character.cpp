#include "stdafx.h"
#include "Character.h"
#include "Player.h"
#include "Item.h"
#include "Random.h"

#include <vector>

namespace TOD {
	Character::Character(std::string name) : GameObject(name) {
		inventory = std::vector<Item*>();
	}


	Character::~Character()
	{
	}

	int Character::Attack(Player* c) {
		// calculate total defense
		int totaldefense = defense;
		if (c->GetAmor() != nullptr)
			totaldefense += c->GetAmor()->GetDefense();

		// calculate damage
		int damage = ((((2 * level / 5 + 2) * attack * (attack / 4) / totaldefense) / 50) + 2) * Random::Next(1, 100) / 100;
		
		return damage;
	}

	int Character::GiveXp() {
		// Set base xp
		int basexp = 7;
		return basexp * level;
	}

	bool Character::TakeDamage(int attack) {
		hp = hp - attack > 0 ? hp - attack : 0;
		this->_isDead = hp > 0 ? false : true;
		return _isDead;
	}
}
