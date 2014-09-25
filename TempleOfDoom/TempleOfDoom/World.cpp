#include "stdafx.h"
#include "World.h"

#include <iostream>
#include <random>
using namespace std;

namespace TOD {
	World::World(int floorCount, int size) {
		World::floorCount = floorCount;
		World::size = size;

		Generate();
	}


	World::~World() {
	}

	void World::Generate() {
		default_random_engine dre;
		uniform_int_distribution<int> dist(1, 6);

		for (int i = 0; i < World::size; ++i) {
			cout << dist(dre) << " ";
		}
		cout << endl;

		std::cin.get();
	}
}
