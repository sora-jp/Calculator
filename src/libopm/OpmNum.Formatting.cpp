#include <cstdlib>

#include "OpmNum.hpp"
#include "Utils.hpp"

int fmtlen(const OpmNum& num)
{
	return 128;
}

inline int getCutoffIdx(const OpmNum& num)
{
	//return DIGITCOUNT;
	for (int i = DIGITCOUNT - 9; i >= 0; i--)
	{
		if (DIGIT(num, i) != 0) return i + 1;
	}
	return 0;
}

int format(const OpmNum& num, char* buffer, FormatMode mode)
{
	if (mode == FormatMode::Standard)
	{
		if (num.exponent > FIXED_MAX_EXP || num.exponent < FIXED_MIN_EXP) mode = FormatMode::Scientific;
		else
		{
			const int dotIdx = num.exponent < 0 ? 0 : num.exponent;
			int startDigit = num.exponent < 0 ? num.exponent : 0;
			int len = getCutoffIdx(num) - startDigit;
			if (len < num.exponent) len = num.exponent;
			if (len > 32) len = 32;

			if (num.isNegative)
			{
				buffer[0] = '-';
				buffer++;
			}

			for (int i = 0; i <= len; i++)
			{
				const int curDigit = i + startDigit;
				buffer[i] = curDigit < 0 ? '0' : DIGIT(num, curDigit) + '0';

				if (i == dotIdx)
				{
					i++;
					startDigit--;
					if (i + 1 <= len) buffer[i] = '.';
				}
			}

			return 0;
		}
	}
	
	if (mode == FormatMode::Scientific || mode == FormatMode::DebugRaw)
	{
		if (num.isNegative)
		{
			buffer[0] = '-';
			buffer++;
		}
		else
		{
			//buffer[0] = '+';
		}
		
		buffer[0] = DIGIT(num, 0) + '0';
		buffer[1] = '.';

		int len = getCutoffIdx(num);
		if (len == 0)
		{
			len = -1;
			buffer[1] = ' ';
		}
		
		for (int i = 1; i <= len; i++)
		{
			buffer[i + 1] = DIGIT(num, i) + '0';
		}

		if (mode == FormatMode::Scientific) 
		{
			buffer[len + 1] = ' ';
			buffer[len + 2] = '*';
			buffer[len + 3] = ' ';
			buffer[len + 4] = '1';
			buffer[len + 5] = '0';
			buffer[len + 6] = '^';
			sprintf(&buffer[len + 7], "%d", num.exponent);
		}
		else
		{
			buffer[len + 1] = 'e';
			sprintf(&buffer[len + 2], "%d", num.exponent);
		}
		return 0;
	}

	return -1;
}
