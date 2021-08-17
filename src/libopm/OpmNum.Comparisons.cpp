#include "OpmNum.hpp"
#include <memory>

bool operator==(const OpmNum& a, const OpmNum& b)
{
	if (a.exponent != b.exponent) return false;
	if (a.isNegative != b.isNegative) return false;
	for (auto i = 0u; i < GROUPS; i++) if (a.groups[i] != b.groups[i]) return false;
	return true;
}

bool operator!=(const OpmNum& a, const OpmNum& b)
{
	return !(a == b);
}

bool operator>(const OpmNum& a, const OpmNum& b)
{
	if (a.isNegative != b.isNegative) return !a.isNegative;
	if (a.exponent > b.exponent) return !a.isNegative;
	
	for (auto i = 0u; i < GROUPS; i++) 
    {
		if (a.groups[i] > b.groups[i] && !a.isNegative) return true;
		if (a.groups[i] < b.groups[i] && a.isNegative) return true;
    }
	return false;
}

bool operator>=(const OpmNum& a, const OpmNum& b)
{
	return a > b || a == b;
}

bool operator<(const OpmNum& a, const OpmNum& b)
{
	return !(a >= b);
}

bool operator<=(const OpmNum& a, const OpmNum& b)
{
	return !(a > b);
}

bool is_zero(const OpmNum& a)
{
	for (auto g : a.groups) if (g != 0) return false;
	return true;
}