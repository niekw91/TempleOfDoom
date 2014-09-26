#pragma once
#include "GameObject.h"
#include "Item.h"

namespace TOD {
	class Character :
		public GameObject
	{

	public:
		Character();
		virtual ~Character();


	private:
		int hp;
		int accuracy;
		int agility;
		int attack;
		int defense;
		Item inventory[20];
		int level;
	};
}

