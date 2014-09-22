#pragma once

namespace TOD {
	class Room
	{

	public:
		Room();
		virtual ~Room();

	private:
		Room *north;
		Room *east;
		Room *south;
		Room *west;
		int size;
	};
}

