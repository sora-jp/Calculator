#pragma once
#include "OpmNum.hpp"
#include "OpmStrConstant.hpp"
#include <random>

class random_distribution
{
private:
	std::default_random_engine m_engine;
	std::uniform_int_distribution<> m_rand { 0, 9 };
	const OpmNum m_min, m_diff;

public:
	random_distribution(const OpmNum& min, const OpmNum& max) : m_min(min), m_diff(max - min)
	{
		std::random_device rd;
		m_engine = std::default_random_engine(rd());
	}

	OpmNum rand1to10()
	{
		OpmNum o;
		o.exponent = -1;

		for (uint32_t d = 0; d < DIGITCOUNT; d++)
		{
			const auto r = m_rand(m_engine);
			o.groups[d >> 3] |= r << (7 - (d & 7)) * 4;
		}

		return o.normalize();
	}

	OpmNum rand()
	{
		auto fac = rand1to10();
		return m_min + m_diff * fac;
	}
};
