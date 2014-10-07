#include "stdafx.h"
#include "GameObjectFactory.h"
#include "tinyxml2.h"
#include "NPCType.h"

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

	NPC* GameObjectFactory::GetRandomNPC() {
		return *select_randomly(npcVector.begin(), npcVector.end());
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
					XMLElement *element = itemType->FirstChildElement("name");
					std::string name = element->GetText();
					element = element->NextSiblingElement();
					int rating = atoi(element->GetText());
					element = element->NextSiblingElement();
					bool rare = element->GetText() == "true" ? true : false;

					// Create itemType
					// itemTpye.CreateItem

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

	GameObjectFactory::~GameObjectFactory()
	{
	}
}
