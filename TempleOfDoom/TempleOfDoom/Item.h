#pragma once
#include "GameObject.h"

#include <string>

namespace TOD {
	class ItemType;

	class Item :
		public GameObject
	{

	public:
		Item(std::string name, bool rare);
		Item(ItemType *type);
		virtual ~Item();

		bool GetRare();

		virtual std::string ToString() = 0;
	private:
		bool rare;
	};
}

