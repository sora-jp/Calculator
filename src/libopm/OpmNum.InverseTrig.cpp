#include "OpmNum.hpp"
#include "cordic/Tables.hpp"
#include "Utils.hpp"

OpmNum atan2(const OpmNum& x, const OpmNum& y)
{
	uint8_t coeffs[DIGITCOUNT] = {};

	bool neg = x.isNegative ^ y.isNegative;

	OpmNum nx = x;
	OpmNum ny = y;
	nx.isNegative = ny.isNegative = false;

	for (int i = 0; i < DIGITCOUNT; i++)
	{
		OpmNum z = ny;
		z.exponent += i;
		while (true)
		{
			//xs.exponent -= i;
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
	return o;
}

OpmNum atan(const OpmNum& arg)
{
	return atan2(1e0_opm, arg);
}