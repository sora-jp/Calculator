#include "OpmNum.hpp"
#include <memory>

bool operator==(const OpmNum& a, const OpmNum& b)
{
	if (is_nan(a) || is_nan(b)) return false;
	if (is_inf(a) || is_inf(b)) return false;

	if (a.exponent != b.exponent) return false;
	if (a.isNegative != b.isNegative) return false;
	for (auto i = 0u; i < GROUPS; i++) if (a.groups[i] != b.groups[i]) return false;
	return true;
}

bool operator!=(const OpmNum& a, const OpmNum& b)
{
	if (is_nan(a) || is_nan(b)) return false;
	return !(a == b);
}

bool operator>(const OpmNum& a, const OpmNum& b)
{
	if (is_nan(a) || is_nan(b)) return false;

	if (is_inf(a))
	{
		if (a.isNegative && !is_ninf(b)) return false;
		if (!a.isNegative && !is_pinf(b)) return true;
		return false;
	}

	if (is_inf(b))
	{
		if (b.isNegative && !is_ninf(a)) return true;
		if (!b.isNegative && !is_pinf(a)) return false;
		return false;
	}

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
	if (is_nan(a) || is_nan(b)) return false;
	return a > b || a == b;
}

bool operator<(const OpmNum& a, const OpmNum& b)
{
	if (is_nan(a) || is_nan(b)) return false;
	return !(a >= b);
}

bool operator<=(const OpmNum& a, const OpmNum& b)
{
	if (is_nan(a) || is_nan(b)) return false;
	return !(a > b);
}

bool is_zero(const OpmNum& a)
{
	for (auto g : a.groups) if (g != 0) return false;
	return true;
}

bool is_nan(const OpmNum& a)
{
	return a.isNan;
}

bool is_pinf(const OpmNum& a)
{
	return a.isInfinity && !a.isNegative;
}

bool is_ninf(const OpmNum& a)
{
	return a.isInfinity && a.isNegative;
}

bool is_inf(const OpmNum& a)
{
	return a.isInfinity;
}