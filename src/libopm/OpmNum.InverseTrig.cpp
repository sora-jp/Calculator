#include "OpmNum.hpp"
#include "cordic/Tables.hpp"
#include "Utils.hpp"

OpmNum atan2(const OpmNum& x, const OpmNum& y)
{
	uint8_t coeffs[DIGITCOUNT] = {};

	OpmNum nx = x;
	OpmNum ny = y;

	for (int i = 0; i < DIGITCOUNT; i++)
	{
		while (true)
		{
			OpmNum xs = nx;
			OpmNum ys = ny;

			xs.exponent -= i;
			xs = ny - xs;
			if (xs.isNegative) break;

			ys = nx + ys;

			ny = xs;
			nx = ys;
			coeffs[i]++;
		}
	}

	return PsMul(Tables::atanTable, coeffs);
}

OpmNum atan(const OpmNum& arg)
{
	return atan2(1e0_opm, arg);
}