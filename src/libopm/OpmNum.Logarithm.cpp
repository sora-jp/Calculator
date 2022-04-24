#include "OpmNum.hpp"
#include "Utils.hpp"
#include "cordic/Tables.hpp"
#include <cstring>

OpmNum ln(const OpmNum& arg)
{
	if (is_nan(arg)) return arg;
	if (arg.isNegative || is_zero(arg)) return Constants::nan;
	if (is_inf(arg)) return arg;

    OpmNum accumulator = arg;
    accumulator.exponent = 0;

	if (accumulator.groups[0] == 0x10000000)
	{
		bool isOne = true;
		for (auto i = 1u; i < GROUPS; i++)
		{
			isOne &= accumulator.groups[i] == 0;
		}
		if (isOne) return Constants::ln10 * OpmNum(arg.exponent);
	}

	uint8_t counts[GROUPS * 8] = {};

	OpmNum tmp;
	for (uint32_t i = 0; i < GROUPS * 8; i++)
	{
        uint8_t count = 0;
		
		do
		{
			tmp = accumulator;
            tmp.exponent -= static_cast<int32_t>(i);

			const OpmNum t = accumulator + tmp;
            if (t.exponent > 0) break;
			
			accumulator = t;
			
            ++count;
		} while (true);
		
		counts[i] = count;
	}


	tmp.Clear();
	tmp.groups[0] = 0x10000000;
    tmp.exponent = 1;
    
	auto almost = tmp - accumulator;
	almost.exponent--;
	
    for (int32_t i = GROUPS * 8 - 1; i >= 0; i--)
    {
		for (auto j = 0; j < counts[i]; j++) 
		{
			almost = almost + Tables::lnTable[i];
		}
    }
	auto o = OpmNum(arg.exponent);
	return Constants::ln10 + Constants::ln10 * o - almost;
}

OpmNum log10(const OpmNum& arg)
{
	return ln(arg) / Constants::ln10;
}

OpmNum log2(const OpmNum& arg)
{
	return ln(arg) / Constants::ln2;
}

OpmNum log(const OpmNum& arg, const OpmNum& base)
{
	return ln(arg) / ln(base);
}