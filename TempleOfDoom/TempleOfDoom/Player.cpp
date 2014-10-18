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
			if (inventory.size() < (size_t)invSize) {
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
				break;
			}
			if (!equiped)
				index++;
		}
		if (equiped) inventory.erase(inventory.begin() + index);
	}

	void Player::Equip(Armor *armor) {
		bool equiped = false;
		int index = 0;
		for (auto i : inventory) {
			if (i->GetName() == armor->GetName()) {
				if (this->armor) {
					inventory.push_back(this->armor);
					this->armor = nullptr;
				}
				this->armor = armor;
				equiped = true;
			}
			if (!equiped)
				index++;
		}
		if (equiped) inventory.erase(inventory.begin() + index);
	}
}
