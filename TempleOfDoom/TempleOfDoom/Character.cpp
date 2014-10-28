#include "stdafx.h"
#include "Character.h"
#include "Item.h"

#include <vector>

namespace TOD {
	Character::Character(std::string name) : GameObject(name) {
		inventory = std::vector<Item*>();
	}


	Character::~Character()
	{
	}

	void Character::Attack(Character* c) { 
		c->TakeDamage(this->getAttack()); 
	}
}
