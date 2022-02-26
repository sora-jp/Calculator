#include "Timing.h"
#include "OpmRand.hpp"
#include "rt_poly/OpmValue.h"

struct FnData1
{
	std::string name;
	OpmNum(*fnPtr)(const OpmNum&);
	OpmNum min, max;
};

struct FnData2
{
	std::string name;
	OpmNum(*fnPtr)(const OpmNum&, const OpmNum&);
	OpmNum min, max;
};

const std::vector<FnData1> fnMap1 =
{
	{"ln",  &ln, 0e0_opm, 1e2_opm},
	{"exp", &exp, -1e2_opm, 1e2_opm},
	{"sin", &sin, -7e0_opm, 7e0_opm},
	{"cos", &cos, -7e0_opm, 7e0_opm},
	{"tan", &tan, -1e2_opm, 1e2_opm},
	{"arctan", &atan, -1e2_opm, 1e2_opm},
	{"arcsin", &asin, -1e0_opm, 1e0_opm},
	{"arccos", &acos, -1e0_opm, 1e0_opm},
	{"1 / x", &invert, 0e0_opm, 1e4_opm}
};

const std::vector<FnData2> fnMap2 =
{
	{"addition", &operator+, 1e0_opm, 1e10_opm},
	{"subtraction", &operator-, 1e0_opm, 1e10_opm},
	{"multiplication", &operator*, -1e10_opm, 1e10_opm},
	{"division", &operator/, -1e10_opm, 1e10_opm},
	{"pow", &pow, 1e0_opm, 1e10_opm},
	{"log", &log, 1e0_opm, 1e10_opm},
};

void TimeSingle(const FnData1& data)
{
	auto t = Time(data.fnPtr, data.min, data.max, 10000U);
	std::cout << data.name << " took " << t << "ms / invocation, " << (1000.0l / t) << " invocations / second" << std::endl;
}

void TimeSingle(const FnData2& data)
{
	auto t = Time(data.fnPtr, data.min, data.max, 10000U);
	std::cout << data.name << " took " << t << "ms / invocation, " << (1000.0l / t) << " invocations / second" << std::endl;
}

void TimeAll()
{
	for (const auto& fn : fnMap1)
	{
		TimeSingle(fn);
	}
	std::cout << std::endl;
	for (const auto& fn : fnMap2)
	{
		TimeSingle(fn);
	}
}
