#include "stdafx.h"
#include "Player.h"
#include "Weapon.h"
#include "Armor.h"

namespace TOD {
	Player::Player(std::string name) : Character(name) {
	}


	Player::~Player() {
	}

	bool Player::PickUp(Item *item) {
		bool pickedUp = false;
		if (item) {
			// Check if inventory not full
			if (inventory.size() < invSize) {
				inventory.push_back(item);
				pickedUp = true;
			}
		}
		return pickedUp;
	}

	void Player::Equip(Weapon *weapon) {
		bool equiped = false;
		int index = 0;
		for (auto i : inventory) {
			if (i->GetName() == weapon->GetName()) {
				if (this->weapon) {
					inventory.push_back(this->weapon);
					this->weapon = nullptr;
				}
				this->weapon = weapon;
				equiped = true;
			}
			if (!equiped)
				index++;
		}
		if (equiped) inventory.erase(inventory.begin() + index);
	}

	void Player::Equip(Armor *armor) {
		if (armor) {
			this->armor = armor;
		}
	}
}
