#pragma once
#include <chrono>
#include <functional>
#include "OpmNum.hpp"
#include "OpmRand.hpp"
#include "rt_poly/OpmValue.h"

template<typename T, enable_if_opm_type<T> = true>
long double Time(T(*fn)(const T&), const T& min, const T& max, uint32_t iters = 100000)
{
	long double d = 0;
	random_distribution<T> r(min, max);
	for (uint32_t i = 0; i < iters; i++)
	{
		const auto num = r.rand();
		auto t1 = std::chrono::high_resolution_clock::now();
		volatile auto res = fn(num);
		auto t2 = std::chrono::high_resolution_clock::now();
		d += static_cast<long double>((t2 - t1).count());
	}

	return d / (1000000.0l * iters);
}

template<typename T, enable_if_opm_type<T> = true>
long double Time(T(*fn)(const T&, const T&), const T& min, const T& max, uint32_t iters = 100000)
{
	long double d = 0;
	random_distribution<T> r(min, max);
	for (uint32_t i = 0; i < iters; i++)
	{
		const auto num1 = r.rand();
		const auto num2 = r.rand();
		//print(num1);
		//print(num2);

		auto t1 = std::chrono::high_resolution_clock::now();
		volatile auto res = fn(num1, num2);
		auto t2 = std::chrono::high_resolution_clock::now();
		d += static_cast<long double>((t2 - t1).count());
	}

	return d / (1000000.0l * iters);
}
