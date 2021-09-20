#include "PrecisionTest.h"
#include <iostream>
#include <map>

#include "OpmNum.hpp"
#include "Utils.hpp"

const std::map<std::string, OpmNum(*)(const OpmNum&)> fnMap = 
{
	{"ln",  &ln},
	{"exp", &exp},
	{"sin", &sin},
	{"cos", &cos},
	{"tan", &tan},
	{"atan", &atan},
	{"inv", &invert},
	{"inv3", &invert3}
};

inline OpmNum get()
{
	std::string s;
	std::cin >> s;
	return parse(s.c_str());
}

inline void echo(const OpmNum& num)
{
	std::cout << (num.isNegative ? '-' : '+');
	std::cout << static_cast<char>(DIGIT(num, 0) + '0') << '.';
	for (uint32_t i = 1; i < DIGITCOUNT; i++)
	{
		std::cout << static_cast<char>(DIGIT(num, i) + '0');
	}
	std::cout << std::endl << num.exponent << std::endl;
}

int TestPrecision(int argc, char** argv, bool& exit)
{
	if (strcmp("--info", argv[1]) == 0) 
	{
		std::cout << GROUPS << std::endl;
		
		exit = true;
		return 0;
	}
	
	if (strcmp("--test", argv[1]) == 0) 
	{
		std::string targetFn;
		std::cin >> targetFn;
		//targetFn = targetFn.substr(0, targetFn.size() - 1);

		auto* const fnPtr = fnMap.at(targetFn);
		
		size_t count;
		std::cin >> count;
		
		for (size_t i = 0; i < count; i++)
		{
			const auto res = fnPtr(get()).roundToNearest();
			echo(res);
			//TODO: Echo result back
		}

		exit = true;
		return 0;
	}

	exit = false;
	return 0;
}
