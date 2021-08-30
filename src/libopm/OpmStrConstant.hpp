#pragma once

template<char C, char... D>
constexpr int32_t ParseExp(int32_t exponent)
{
	if constexpr (C == '-')
	{
		return -ParseExp<D...>(0);
	}
	
	if constexpr (sizeof...(D) == 0) return exponent * 10 + (C - '0');
	else return ParseExp<D...>(exponent * 10 + (C - '0'));
}

template<uint32_t Digit, char C, char... D>
constexpr void ParseOpm(OpmNum& output)
{
	if constexpr (C == '-')
	{
		output.isNegative = true;
		ParseOpm<Digit, D...>(output);
	}
	else if constexpr (C == '.')
	{
		ParseOpm<Digit, D...>(output);
	}
	else if constexpr (C == 'e' || C == 'E')
	{
		output.exponent = ParseExp<D...>(0);
		return;
	}
	else
	{
		static_assert(C == '0' || C == '1' || C == '2' || C == '3' || C == '4' || C == '5' || C == '6' || C == '7' || C == '8' || C == '9', "Invalid character found in literal");
		
		if constexpr (Digit < DIGITCOUNT) output.groups[(Digit >> 3)] |= (C - '0') << ((7 - (Digit & 7)) * 4);
		if constexpr (sizeof...(D) > 0) ParseOpm<Digit + 1, D...>(output);
	}
}

template<char... D>
constexpr OpmNum operator ""_opm()
{
	OpmNum o;
	ParseOpm<0, D...>(o);
	return o;
}