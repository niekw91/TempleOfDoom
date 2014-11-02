#include "stdafx.h"
#include "GameObjectFactory.h"
#include "tinyxml2.h"
#include "NPCType.h"
#include "ItemType.h"
#include "Weapon.h"
#include "Armor.h"
#include "Medkit.h"

#include <string>
#include <random>
#include <iterator>

using namespace tinyxml2;

namespace TOD {
	GameObjectFactory::GameObjectFactory() {
		tempTypes = std::vector<ItemType*>();
		tempNPC = std::vector<NPCType*>();
	}

	/*
	 * Random number generator
	 *******************************************************************************/
		template<typename Iter, typename RandomGenerator>
		Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
			std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
			std::advance(start, dis(g));
			return start;
		}

		template<typename Iter>
		Iter select_randomly(Iter start, Iter end) {
			static std::random_device rd;
			static std::mt19937 gen(rd());
			return select_randomly(start, end, gen);
		}
	/*******************************************************************************/

	std::string GameObjectFactory::GetRandomExitString() {
		std::string exit = *select_randomly(exitVector.begin(), exitVector.end());
		return exit;
	}

	Weapon* GameObjectFactory::GetRandomWeapon() {
		Weapon *wep = *select_randomly(weaponVector.begin(), weaponVector.end());
		ItemType *type = new ItemType(wep->GetName(), wep->GetDamage(), wep->GetRare(), WEAPON);
		tempTypes.push_back(type);
		return type->CreateWeapon();
	}

	Armor* GameObjectFactory::GetRandomArmor() {
		Armor *ar = *select_randomly(armorVector.begin(), armorVector.end());
		ItemType *type = new ItemType(ar->GetName(), ar->GetDefense(), ar->GetRare(), ARMOR);
		tempTypes.push_back(type);
		return type->CreateArmor();
	}

	Medkit* GameObjectFactory::GetRandomMedkit() {
		Medkit *med = *select_randomly(medkitVector.begin(), medkitVector.end());
		ItemType *type = new ItemType(med->GetName(), med->GetHp(), med->GetRare(), MEDKIT);
		tempTypes.push_back(type);
		return type->CreateMedkit();
	}

	EndBoss* GameObjectFactory::GetRandomBoss() {
		EndBoss *boss = *select_randomly(bossVector.begin(), bossVector.end());
		NPCType *type = new NPCType(boss->GetName(), boss->GetHP(), boss->GetAttack(), boss->GetDefense(), boss->GetLevel());
		tempNPC.push_back(type);
		return new EndBoss(type);
	}

	NPC* GameObjectFactory::GetRandomNPC(int minLevel, int maxLevel) {
		NPC *npc;
		do
		{
			npc = *select_randomly(npcVector.begin(), npcVector.end());
		} while (npc->GetLevel() > maxLevel || npc->GetLevel() < minLevel);
		return new NPC(npc->GetName(), npc->GetHP(), npc->GetAttack(), npc->GetDefense(), npc->GetLevel());
	}

	Scenery* GameObjectFactory::GetRandomScenery() {
		Scenery *scen = *select_randomly(sceneryVector.begin(), sceneryVector.end());
		return new Scenery(scen->GetName());
	}

	Trap* GameObjectFactory::GetRandomTrap() {
		Trap *trap = *select_randomly(trapVector.begin(), trapVector.end());
		return new Trap(trap->GetName(), trap->GetDamage());
	}

	void GameObjectFactory::LoadTrapsFromFile(std::string fileName) {
		trapVector = std::vector<Trap*>();

		tinyxml2::XMLDocument doc;
		doc.LoadFile(fileName.c_str());
		if (doc.ErrorID() == 0)
		{
			XMLElement *tod = doc.FirstChildElement("TOD");
			XMLElement *trap = tod->FirstChildElement();

			while (trap != NULL)
			{
				XMLElement *element = trap->FirstChildElement("name");
				std::string name = element->GetText();
				element = element->NextSiblingElement();
				int damage = atoi(element->GetText());
				// Create scenery object
				Trap *t = new Trap(name, damage);
				trapVector.push_back(t);

				trap = trap->NextSiblingElement();
			}
		}
	}

	void GameObjectFactory::LoadSceneryFromFile(std::string fileName) {
		sceneryVector = std::vector<Scenery*>();

		tinyxml2::XMLDocument doc;
		doc.LoadFile(fileName.c_str());
		if (doc.ErrorID() == 0)
		{
			XMLElement *tod = doc.FirstChildElement("TOD");
			XMLElement *item = tod->FirstChildElement();

			while (item != NULL)
			{
				XMLElement *element = item->FirstChildElement("name");
				std::string name = element->GetText();
				// Create scenery object
				Scenery *scenery = new Scenery(name);
				sceneryVector.push_back(scenery);

				item = item->NextSiblingElement();
			}
		}
	}

	void GameObjectFactory::LoadItemsFromFile(std::string fileName) {
		weaponVector = std::vector<Weapon*>();
		armorVector = std::vector<Armor*>();
		medkitVector = std::vector<Medkit*>();

		tinyxml2::XMLDocument doc;
		doc.LoadFile(fileName.c_str());
		if (doc.ErrorID() == 0)
		{
			XMLElement *tod = doc.FirstChildElement("TOD");
			XMLElement *itemType = tod->FirstChildElement();

			while (itemType != NULL)
			{
				XMLElement *item = itemType->FirstChildElement();
				while (item != NULL) 
				{
					XMLElement *element = item->FirstChildElement("name");
					std::string name = element->GetText();
					element = element->NextSiblingElement();
					int rating = atoi(element->GetText());
					element = element->NextSiblingElement();
					bool rare = element->GetText() == "true" ? true : false;
					std::string iType = itemType->Name();
					ItemKind kind = GetItemKind(iType);
					ItemType *type = new ItemType(name, rating, rare, kind);
					if (kind == WEAPON) {
						weaponVector.push_back(type->CreateWeapon());
					}
					else if (kind == ARMOR) {
						armorVector.push_back(type->CreateArmor());
					}
					else if (kind == MEDKIT) {
						medkitVector.push_back(type->CreateMedkit());
					}
					delete type;
					item = item->NextSiblingElement();
				}
				itemType = itemType->NextSiblingElement();
			}
		}
	}

	void GameObjectFactory::LoadNPCFromFile(std::string fileName) {
		npcVector = std::vector<NPC*>();

		tinyxml2::XMLDocument doc;
		doc.LoadFile(fileName.c_str());
		if (doc.ErrorID() == 0)
		{
			XMLElement *tod = doc.FirstChildElement("TOD");
			XMLElement *npc = tod->FirstChildElement("NPC");

			while (npc != NULL)
			{
				XMLElement *element = npc->FirstChildElement("name");
				std::string name = element->GetText();
				element = element->NextSiblingElement("hp");
				int hp = atoi(element->GetText());
				element = element->NextSiblingElement("level");
				int level = atoi(element->GetText());
				element = element->NextSiblingElement("attack");
				int attack = atoi(element->GetText());
				element = element->NextSiblingElement("defense");
				int defense = atoi(element->GetText());

				NPCType *type = new NPCType(name, hp, attack, defense, level);
				npcVector.push_back(type->createNPC());
				delete type;
				npc = npc->NextSiblingElement();
			}
		}
	}

	void GameObjectFactory::LoadBossFromFile(std::string fileName) {
		bossVector = std::vector<EndBoss*>();

		tinyxml2::XMLDocument doc;
		doc.LoadFile(fileName.c_str());
		if (doc.ErrorID() == 0)
		{
			XMLElement *tod = doc.FirstChildElement("TOD");
			XMLElement *npc = tod->FirstChildElement("Boss");

			while (npc != NULL)
			{
				XMLElement *element = npc->FirstChildElement("name");
				std::string name = element->GetText();
				element = element->NextSiblingElement("hp");
				int hp = atoi(element->GetText());
				element = element->NextSiblingElement("level");
				int level = atoi(element->GetText());
				element = element->NextSiblingElement("attack");
				int attack = atoi(element->GetText());
				element = element->NextSiblingElement("defense");
				int defense = atoi(element->GetText());

				NPCType *type = new NPCType(name, hp, attack, defense, level);
				bossVector.push_back(type->createBoss());
				delete type;
				npc = npc->NextSiblingElement();
			}
		}
	}

	void GameObjectFactory::LoadExitsFromFile(std::string fileName) {
		exitVector = std::vector<std::string>();

		tinyxml2::XMLDocument doc;
		doc.LoadFile(fileName.c_str());
		if (doc.ErrorID() == 0)
		{
			XMLElement *tod = doc.FirstChildElement("TOD");
			XMLElement *exit = tod->FirstChildElement("Exit");

			while (exit != NULL)
			{
				XMLElement *element = exit->FirstChildElement("description");
				std::string name = element->GetText();

				exitVector.push_back(name);
				exit = exit->NextSiblingElement();
			}
		}
	}

	ItemKind GameObjectFactory::GetItemKind(std::string str) {
		if (str == "weapons") {
			return WEAPON;
		}
		else if (str == "armor") {
			return ARMOR;
		}
		else if (str == "medkit") {
			return MEDKIT;
		}
	}

	GameObjectFactory::~GameObjectFactory()
	{
		std::vector<Trap*>::iterator tIt;
		for (tIt = trapVector.begin(); tIt != trapVector.end();) {
			delete *tIt;
			tIt = trapVector.erase(tIt);
		}

		std::vector<Scenery*>::iterator sIt;
		for (sIt = sceneryVector.begin(); sIt != sceneryVector.end();) {
			delete *sIt;
			sIt = sceneryVector.erase(sIt);
		}

		std::vector<NPC*>::iterator nIt;
		for (nIt = npcVector.begin(); nIt != npcVector.end();) {
			delete *nIt;
			nIt = npcVector.erase(nIt);
		}

		std::vector<Weapon*>::iterator wIt;
		for (wIt = weaponVector.begin(); wIt != weaponVector.end();) {
			delete *wIt;
			wIt = weaponVector.erase(wIt);
		}

		std::vector<Armor*>::iterator aIt;
		for (aIt = armorVector.begin(); aIt != armorVector.end();) {
			delete *aIt;
			aIt = armorVector.erase(aIt);
		}

		std::vector<Medkit*>::iterator mIt;
		for (mIt = medkitVector.begin(); mIt != medkitVector.end();) {
			delete *mIt;
			mIt = medkitVector.erase(mIt);
		}

		std::vector<ItemType*>::iterator itIt;
		for (itIt = tempTypes.begin(); itIt != tempTypes.end();) {
			delete *itIt;
			itIt = tempTypes.erase(itIt);
		}

		std::vector<NPCType*>::iterator tnIt;
		for (tnIt = tempNPC.begin(); tnIt != tempNPC.end();) {
			delete *tnIt;
			tnIt = tempNPC.erase(tnIt);
		}
	}
}
