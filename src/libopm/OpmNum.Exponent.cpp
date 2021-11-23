#include "OpmNum.hpp"
#include "Utils.hpp"
#include <cstring>
#include <iostream>

#include "cordic/Tables.hpp"

OpmNum exp(const OpmNum& arg)
{
	if (is_nan(arg)) return Constants::nan;
	if (is_pinf(arg)) return Constants::nan;
	if (is_ninf(arg)) return 0e0_opm;

    OpmNum accumulator = arg;
	accumulator.isNegative = false;
	
    const bool shouldInvert = arg.isNegative;
    const uint32_t scale = Prescale(accumulator, Constants::ln10);

	uint8_t counts[GROUPS * 8] = {};

    PsDiv(accumulator, Tables::lnTable, counts);
	
	accumulator = 1e0_opm;
	
    for (int32_t i = 0; i < GROUPS * 8; i++)
    {
		for (int j = 0; j < counts[i]; j++)
		{
			OpmNum y = accumulator;
			y.exponent -= i;

			accumulator = accumulator + y;
		}
    }

	accumulator.isNegative = false;
	accumulator.exponent += scale;
	
	return shouldInvert ? invert(accumulator) : accumulator;
}

OpmNum exp10(const OpmNum& num)
{
	return exp(Constants::ln10 * num);
}

OpmNum exp2(const OpmNum& num)
{
	return exp(Constants::ln2 * num);
}

OpmNum pow(const OpmNum& x, const OpmNum& y)
{
	if (is_nan(x) || is_nan(y)) return Constants::nan;
	if (x.isNegative) return Constants::nan;

	const bool zy = is_zero(y);
	if (is_zero(x) && zy) return Constants::one;
	if (x == Constants::one && is_inf(y)) return Constants::one;
	if (is_inf(x) && zy) return Constants::one;

	return exp(y * ln(x));
}

OpmNum sqrt(const OpmNum& x)
{
	if (x.isNegative) return Constants::nan;
	return exp(5e-1_opm * ln(x));
}