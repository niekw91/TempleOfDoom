#include "stdafx.h"
#include "Player.h"
#include "Weapon.h"
#include "Armor.h"

namespace TOD {
	Player::Player(std::string name) : Character(name) 
	{
		this->level = 1;
		this->maxhp = 10;
		this->hp = maxhp;
		this->xp = 0;
		this->attack = 4;
		this->defense = 5;
		this->vigilance = 6;
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

	void Player::TakeDamage(int attack) {
		// Calculate total defense
		int totaldefense = defense;
		if (armor != nullptr)
			totaldefense += armor->GetDefense();

		// Calculate damage
		int damage = totaldefense - attack < 0 ? (totaldefense - attack) * -1 : 0;

		// Calculate new hp
		hp = hp - damage > 0 ? hp - damage : 0;

		// Check if player is dead
		this->_isDead = hp > 0 ? false : true;
	}
}
