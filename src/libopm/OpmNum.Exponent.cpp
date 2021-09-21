#include "OpmNum.hpp"
#include "Utils.hpp"
#include <cstring>
#include <iostream>

#include "cordic/Tables.hpp"

OpmNum exp(const OpmNum& arg)
{
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
	return exp(y * ln(x));
}

OpmNum sqrt(const OpmNum& x)
{
	return exp(5e-1_opm * ln(x));
}