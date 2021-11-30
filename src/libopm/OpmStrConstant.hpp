#pragma once
#include "OpmNum.hpp"
#include <cstdint>

template<char C>
int32_t ParseExp(int32_t exponent)
{
	return exponent * 10 + (C - '0');
}

template<char C, char D0, char... D>
int32_t ParseExp(int32_t exponent)
{
	if (C == '-')
	{
		return -ParseExp<D0, D...>(0);
	}

	return ParseExp<D0, D...>(exponent * 10 + (C - '0'));
}

template<uint32_t Digit, char C>
void ParseOpm(OpmNum& output)
{

}

template<uint32_t Digit, char C, char D0, char... D>
void ParseOpm(OpmNum& output)
{
	if (C == '-')
	{
		output.isNegative = true;
		ParseOpm<Digit, D0, D...>(output);
	}
	else if (C == '.')
	{
		ParseOpm<Digit, D0, D...>(output);
	}
	else if (C == 'e' || C == 'E')
	{
		output.exponent = ParseExp<D0, D...>(0);
		return;
	}
	else
	{
		//static_assert(C == '0' || C == '1' || C == '2' || C == '3' || C == '4' || C == '5' || C == '6' || C == '7' || C == '8' || C == '9', "Invalid character found in literal");
		
		if (Digit < DIGITCOUNT) output.groups[(Digit >> 3)] |= static_cast<uint32_t>(C - '0') << ((7 - (Digit & 7)) * 4);
		ParseOpm<Digit + 1, D0, D...>(output);
	}
}

template<char... D>
OpmNum operator ""_opm()
{
	OpmNum o;
	ParseOpm<0, D...>(o);
	return o;
}
