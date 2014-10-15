#pragma once
#include "GameObject.h"

#include <string>

namespace TOD {
	class ItemType;

	class Item :
		public GameObject
	{

	public:
		Item(ItemType *type);
		virtual ~Item();

		virtual std::string ToString() = 0;
	private:
		bool rare;
	};
}

