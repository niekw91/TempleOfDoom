#include "stdafx.h"
#include "GameObjectFactory.h"
#include "tinyxml2.h"
#include "NPCType.h"
#include "ItemType.h"

#include <string>
#include <random>
#include <iterator>

using namespace tinyxml2;

namespace TOD {
	GameObjectFactory::GameObjectFactory() {

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

	Item* GameObjectFactory::GetRandomItem() {
		return *select_randomly(itemVector.begin(), itemVector.end());
	}

	NPC* GameObjectFactory::GetRandomNPC() {
		return *select_randomly(npcVector.begin(), npcVector.end());
	}

	Scenery* GameObjectFactory::GetRandomScenery() {
		return *select_randomly(sceneryVector.begin(), sceneryVector.end());
	}

	Trap* GameObjectFactory::GetRandomTrap() {
		return *select_randomly(trapVector.begin(), trapVector.end());
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
		itemVector = std::vector<Item*>();

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
					// Create itemType
					ItemType *type = new ItemType(name, rating, rare, kind);
					itemVector.push_back(type->CreateItem());

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

				npc = npc->NextSiblingElement();
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
		// Delete traps
		for (auto trap : trapVector) 
			delete trap;
		
		// Delete scenery
		for (auto scenery : sceneryVector) 
			delete scenery;
		
		// Delete items
		for (auto item : itemVector) 
			delete item;
		
		// Delete npcs
		for (auto npc : npcVector)
			delete npc;
	}
}
