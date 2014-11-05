#include "stdafx.h"
#include "Player.h"
#include "Weapon.h"
#include "Armor.h"
#include "Random.h"
#include "Trap.h"

namespace TOD {
	Player::Player(std::string name, int level, int attack, int defense, int xp, int hp, int maxHp, int vigilance) : Character(name) {
		this->level = level;
		this->maxhp = maxHp;
		this->hp = hp;
		this->xp = xp;
		this->attack = attack;
		this->defense = defense;
		this->vigilance = vigilance;
		inventory = new std::vector<Item*>();
	}

	Player::Player(std::string name) : Character(name) {
		this->level = 1;
		this->maxhp = 1;
		this->hp = maxhp;
		this->xp = 0;
		this->attack = 24;
		this->defense = 24;
		this->vigilance = 26;
		inventory = new std::vector<Item*>();
	}

	Player::~Player() {
		vector<Item*>::iterator it;
		for (it = inventory->begin(); it != inventory->end();) {
			delete *it;
			it = inventory->erase(it);
		}
		delete inventory;
	}

	bool Player::PickUp(Item *item) {
		bool pickedUp = false;
		if (item) {
			// Check if inventory not full
			if (inventory->size() < (size_t)invSize) {
				inventory->push_back(item);
				pickedUp = true;
			}
		}
		return pickedUp;
	}

	void Player::Equip(Weapon *weapon) {
		bool equiped = false;
		int index = 0;
		for (auto i : *inventory) {
			if (i->GetName() == weapon->GetName()) {
				if (this->weapon) {
					inventory->push_back(this->weapon);
					this->weapon = nullptr;
				}
				this->weapon = weapon;
				equiped = true;
				break;
			}
			if (!equiped)
				index++;
		}
		if (equiped) inventory->erase(inventory->begin() + index);
	}

	void Player::Equip(Armor *armor) {
		bool equiped = false;
		int index = 0;
		for (auto i : *inventory) {
			if (i->GetName() == armor->GetName()) {
				if (this->armor) {
					inventory->push_back(this->armor);
					this->armor = nullptr;
				}
				this->armor = armor;
				equiped = true;
			}
			if (!equiped)
				index++;
		}
		if (equiped) inventory->erase(inventory->begin() + index);
	}

	/* Returns integer with the amount of damage done, if 0 attack missed */
	int Player::Attack(Character *c) {
		int multiplier = (int)(level - c->GetLevel()) * 0.4; // Damage multiplier
		int damage = 1; // Damage default

		int left = attack - c->GetDefense();
		if (left <= 0)
		{
			// NPC defense is higher than player attack
			left = Random::Next(0, 1);
			if (left == 0) return 0;
		}

		if (weapon) // If player has weapon get weapon damage
			damage = this->weapon->GetDamage() * left;
		return damage + (damage * multiplier);
	}

	/* Returns true if trap found, false if not */
	bool Player::SearchTrap(Room *room) {
		std::vector<Trap*> *traps = room->GetTraps();
		if (traps->size() == 0) return false; // No traps in room

		Trap *trap = traps->at(0);
		int damage = trap->GetDamage();
		if (vigilance > damage)
		{
			// Trap successfully found
			room->DisarmTrap(); // Disarm
			return true; 
		}
		return false;		
	}

	void Player::ReceiveXp(int givenxp){ 
		// Raise xp
		this->xp += givenxp; 
		// Raise level
		if (xp > NextLevel() && level < 10)
			this->level++;
	}

	int Player::NextLevel() {
		// Set base xp
		int basenextlevelxp = 24;
		// Return xp needed to level up
		return basenextlevelxp * level + basenextlevelxp;
	}

	int Player::Rest() {
		int gain = 15;
		return GainHp(gain);
	}

	void Player::Heal(Medkit *medkit) {
		int gain = medkit->GetHp();
		GainHp(gain);
	}

	int Player::GainHp(int gain) {
		hp += gain;
		if (hp > maxhp)
			hp = maxhp;
		return hp;
	}
}
