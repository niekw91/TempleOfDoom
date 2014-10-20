#pragma once

#include <iostream>
#include <random>
using namespace std;

namespace TOD {
	class Random
	{
	public:
		static int Next(int bottom, int top);
	private:
		static random_device dev;
	};
}
