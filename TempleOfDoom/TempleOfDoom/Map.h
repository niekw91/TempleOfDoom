#pragma once
#include "Usable.h"

namespace TOD {
	class ItemType;

	class Map :
		public Usable
	{

	public:
		Map(ItemType *type);
		virtual ~Map();
	};
}

