#include "stdafx.h"

#include <iostream>
#include <random>
#include <vector>

#include "World.h"

World::World(int floorCount, int size) {
	World::floorCount = floorCount;
	World::size = size;

	Generate();
}

World::~World() {
}

void World::Generate() {
	//floors = new std::vector<TOD::Floor*>;

	//default_random_engine dre;
	//uniform_int_distribution<int> dist(1, 6);

	//for (int i = 0; i < World::size; ++i) {
	//	cout << dist(dre) << " ";
	//}
	//cout << endl;

	//std::cin.get();
}