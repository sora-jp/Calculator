#include "OpmNum.hpp"
#include "Utils.hpp"
#include "cordic/Tables.hpp"

bool cordic_trig(const OpmNum& arg, OpmNum& ox, OpmNum& oy)
{
	oy = abs(arg);

	const auto o = Prescale(oy, Constants::pi);

	if (arg.isNegative) oy = Constants::pi - oy;

	uint8_t coeffs[DIGITCOUNT] = {};
	PsDiv(oy, Tables::atanTable, coeffs);
	
	ox = Constants::one;

	for (int32_t i = 0; i < DIGITCOUNT; i++)
	{
		for (auto j = 0; j < coeffs[i]; j++) 
		{
			OpmNum x = ox;
			OpmNum y = oy;

			x.exponent -= i;
			y.exponent -= i;

			ox = ox - y;
			oy = oy + x;
		}
	}

	if (ox.exponent <= -DIGITCOUNT) ox = 0e0_opm;
	if (oy.exponent <= -DIGITCOUNT) oy = 0e0_opm;

	return o & 1;
}

OpmNum tan(const OpmNum& arg)
{
	OpmNum ox, oy;
	cordic_trig(arg, ox, oy);
	
	return oy / ox;
}

OpmNum cot(const OpmNum& arg)
{
	OpmNum ox, oy;
	cordic_trig(arg, ox, oy);

	return ox / oy;
}

OpmNum sin(const OpmNum& arg)
{
	OpmNum ox, oy;
	const auto n = cordic_trig(arg, ox, oy);
	const auto t = oy / ox;

	auto o = t / pow(Constants::one + t * t, Constants::one_half);
	if (is_zero(o)) return 0e0_opm;

	o.isNegative ^= n ^ t.isNegative ^ arg.isNegative;

	return o;
}

OpmNum cos(const OpmNum& arg)
{
	OpmNum ox, oy;
	const auto n = cordic_trig(arg, ox, oy);
	const auto c = ox / oy;

	auto o = c / pow(Constants::one + c * c, Constants::one_half);
	if (is_zero(o)) return 0e0_opm;

	o.isNegative ^= n ^ arg.isNegative;

	return o;
}

void trig(const OpmNum& arg, OpmNum& sin, OpmNum& cos, OpmNum& tan)
{
	OpmNum ox, oy;
	const bool n = cordic_trig(arg, ox, oy);
	
	tan = oy / ox;
	ox = ox / oy;

	sin = tan / pow(Constants::one + tan * tan, Constants::one_half);
	cos = ox / pow(Constants::one + ox * ox, Constants::one_half);

	sin.isNegative ^= n ^ tan.isNegative ^ arg.isNegative;
	cos.isNegative ^= n ^ arg.isNegative;
}