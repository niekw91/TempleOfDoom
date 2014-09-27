#pragma once

#include <vector>

#include "Floor.h"

class World
{

public:
	World(int floorCount, int size);
	virtual ~World();
	void Generate();

	int floorCount;
	int size;

private:
	std::vector<TOD::Floor*> floors;
};

