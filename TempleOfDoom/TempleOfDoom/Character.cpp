#include "stdafx.h"
#include "Character.h"
#include "Player.h"
#include "Item.h"

#include <vector>

namespace TOD {
	Character::Character(std::string name) : GameObject(name) {
		inventory = std::vector<Item*>();
	}


	Character::~Character()
	{
	}

	int Character::Attack(Player* c) {
		//// Calculate total defense
		//int totaldefense = defense;
		//if (c->GetAmor() != nullptr)
		//	totaldefense += c->GetAmor()->GetDefense();

		//// Calculate damage
		//int damage = totaldefense - attack < 0 ? (totaldefense - attack) * -1 : 0;

		int multiplier = (level - c->getLevel()) * 0.4; // Damage multiplier
		int damage = 1;
		damage += (c->getDefense() - attack) * -1;
		
		return damage + (damage * multiplier);
	}
}
