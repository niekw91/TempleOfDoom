#pragma once
#include "Usable.h"

#include <string>

namespace TOD {
	class ItemType;

	class Medkit :
		public Usable
	{

	public:
		Medkit(ItemType *type);
		virtual ~Medkit();

		std::string ToString();
	};
}

