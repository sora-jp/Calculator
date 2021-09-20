#include "OpmNum.hpp"

OpmNum parse(const char* str)
{
	OpmNum o;
	bool negative = str[0] == '-';
	if (negative) str++;
	
	int exponent = -1;
	for (int i = 0; str[i] != '.' && str[i] != '\0'; i++) exponent++;

	int ds = 0;
	for (; str[ds] == '0' || str[ds] == '.'; ds++) if (str[ds] == '0') exponent--;

	int d = 0;
	while (d < GROUPS * 8)
	{
		if (str[d + ds] == '.') ds++;
		if (str[d + ds] == '\0') break;
		o.groups[d >> 3] |= (str[d + ds] - '0') << ((7 - (d & 7)) * 4);
		d++;
	}

	o.exponent = exponent;
	o.isNegative = negative;

	//if (is_zero(o)) 
	//{
	//	o.exponent = 0;
	//	o.isNegative = false;
	//}

	return o;
}