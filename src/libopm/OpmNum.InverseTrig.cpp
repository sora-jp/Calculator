#include <cassert>

#include "OpmNum.hpp"
#include "cordic/Tables.hpp"
#include "Utils.hpp"

OpmNum atan2(const OpmNum& x, const OpmNum& y)
{
	uint8_t coeffs[DIGITCOUNT] = {};

	if (is_zero(x))
	{
		if (is_zero(y)) return 0e0_opm;
		return y.isNegative ? -Constants::half_pi : Constants::half_pi;
	}
	if (is_zero(y))
	{
		return x.isNegative ? Constants::pi : 0e0_opm;
	}

	const bool neg = x.isNegative ^ y.isNegative;

	OpmNum nx = x;
	OpmNum ny = y;
	nx.isNegative = ny.isNegative = false;

	for (int i = 0; i < DIGITCOUNT; i++)
	{
		OpmNum z = ny;
		z.exponent += i;
		while (true)
		{
			auto zs = z - nx;
			if (zs.isNegative) break;

			auto xs = z;
			xs.exponent -= 2 * i;
			nx = nx + xs;
			z = zs;
			coeffs[i]++;
		}
		z.exponent -= i;
		ny = z;
	}

	auto o = PsMul(Tables::atanTable, coeffs);
	o.isNegative = neg;

	if (x.isNegative) o = o + (y.isNegative ? -Constants::pi : Constants::pi);

	return o;
}

OpmNum atan(const OpmNum& arg)
{
	return atan2(1e0_opm, arg);
}

OpmNum asin(const OpmNum& arg)
{
	if (abs(arg) > 1e0_opm) return Constants::nan;
	const auto term = arg.exponent <= -36 ? Constants::one - Constants::one_half * arg * arg : pow(Constants::one - arg * arg, Constants::one_half);
	return atan(arg / term);
}

OpmNum acos(const OpmNum& arg)
{
	if (abs(arg) > 1e0_opm) return Constants::nan;
	return Constants::half_pi - asin(arg);
}