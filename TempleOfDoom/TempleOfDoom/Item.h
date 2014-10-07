#pragma once
#include "GameObject.h"

namespace TOD {
	class ItemType;

	class Item :
		public GameObject
	{

	public:
		Item(ItemType *type);
		virtual ~Item();
	private:
		bool rare;
	};
}

