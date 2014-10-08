#pragma once
#include "Usable.h"

namespace TOD {
	class ItemType;

	class Medkit :
		public Usable
	{

	public:
		Medkit(ItemType *type);
		virtual ~Medkit();
	};
}

