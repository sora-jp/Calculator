#include "Timing.h"
#include "OpmRand.hpp"

std::chrono::duration<double, std::milli> Time(std::function<OpmNum(const OpmNum&)> fn, const OpmNum& min, const OpmNum& max, uint32_t iters)
{
	std::chrono::duration<double, std::milli> d(0);
	random_distribution r(min, max);
	for (uint32_t i = 0; i < iters; i++)
	{
		const auto num = r.rand();
		auto t1 = std::chrono::high_resolution_clock::now();
		volatile auto res = fn(num);
		auto t2 = std::chrono::high_resolution_clock::now();
		d += (t2 - t1) / iters;
	}

	return d;
}
