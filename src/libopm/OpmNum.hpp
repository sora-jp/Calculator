#pragma once
#include "Config.h"
#include <cstdint>
#include <cstring>
#include <iostream>

class OpmNum;
template<uint32_t n, uint32_t t0> constexpr void copy(OpmNum& o);
template<uint32_t n, uint32_t t0, uint32_t t1, uint32_t... t> constexpr void copy(OpmNum& o);

class OpmNum
{
public:
    bool isNegative : 1, isNan : 1, isInfinity : 1;
    int32_t exponent;
    uint32_t groups[GROUPS] {};
    
    OpmNum() : isNegative(false), isNan(false), isInfinity(false), exponent(0) { }
    OpmNum(const OpmNum& copy);
    explicit OpmNum(int32_t num);

	template<uint32_t... gs>
	static OpmNum Constant(const bool n, const int32_t e)
    {
        static_assert(sizeof...(gs) == GROUPS, "Invalid constant size");
        OpmNum o;
        copy<0, gs...>(o);
        o.isNegative = n;
        o.exponent = e;
        return o;
    }

    void Clear()
    {
		isNegative = false;
        isNan = false;
        isInfinity = false;
        exponent = 0;
        for (unsigned int& group : groups) group = 0;
    }

	uint32_t& operator[](size_t idx);
    const uint32_t& operator[](size_t idx) const;
	
    OpmNum& roundToNearest();
    OpmNum& normalize();
};

template<uint32_t n, uint32_t t0> constexpr void copy(OpmNum& o)
{
    o.groups[n] = t0;
}

template<uint32_t n, uint32_t t0, uint32_t t1, uint32_t... t> constexpr void copy(OpmNum& o)
{
    o.groups[n] = t0;
    copy<n+1, t1, t...>(o);
}

inline OpmNum::OpmNum(int32_t num): isNegative(false), isNan(false), isInfinity(false), exponent(0)
{
	isNegative = num < 0;

	if (num < 0) num = -num;

	uint8_t digits[10]{};

	auto cur = 0;
	do
	{
		const uint8_t r = num % 10;
		num = num / 10;

		digits[cur] = r;

		exponent++;
		cur++;
	}
	while (num > 10);

	digits[cur] = static_cast<uint8_t>(num);

	for (auto i = 0; i <= cur; i++)
	{
		const auto group = i >> 3;
		const auto digit = 7 - (i & 7);

		groups[group] |= digits[cur - i] << (digit * 4);
	}
}

inline OpmNum::OpmNum(const OpmNum& copy): OpmNum()
{
	isNegative = copy.isNegative;
	isNan = copy.isNan;
	isInfinity = copy.isInfinity;
	exponent = copy.exponent;
	for (auto i = 0u; i < GROUPS; i++) groups[i] = copy.groups[i];
}

bool operator==(const OpmNum& a, const OpmNum& b);
bool operator!=(const OpmNum& a, const OpmNum& b);
bool operator<(const OpmNum& a, const OpmNum& b);
bool operator>(const OpmNum& a, const OpmNum& b);
bool operator<=(const OpmNum& a, const OpmNum& b);
bool operator>=(const OpmNum& a, const OpmNum& b);
bool is_zero(const OpmNum& a);

OpmNum operator>>(const OpmNum& a, int amt);
OpmNum operator<<(const OpmNum& a, int amt);
OpmNum& operator>>=(OpmNum& a, int amt);
OpmNum& operator<<=(OpmNum& a, int amt);

OpmNum operator+(const OpmNum& a, const OpmNum& b);
OpmNum operator-(const OpmNum& a, const OpmNum& b);
OpmNum operator*(const OpmNum& a, const OpmNum& b);
OpmNum operator/(const OpmNum& a, const OpmNum& b);

OpmNum operator-(const OpmNum& a);

OpmNum abs(const OpmNum& a);
OpmNum invert(const OpmNum& a);

OpmNum ln(const OpmNum& arg);
OpmNum log2(const OpmNum& arg);
OpmNum log10(const OpmNum& arg);
OpmNum log(const OpmNum& arg, const OpmNum& base);

OpmNum exp(const OpmNum& arg);
OpmNum exp2(const OpmNum& arg);
OpmNum exp10(const OpmNum& arg);
OpmNum pow(const OpmNum& x, const OpmNum& y);

OpmNum tan(const OpmNum& arg);
OpmNum cot(const OpmNum& arg);
OpmNum sin(const OpmNum& arg);
OpmNum cos(const OpmNum& arg);
void trig(const OpmNum& arg, OpmNum& sin, OpmNum& cos, OpmNum& tan);

OpmNum parse(const char* str);

enum class FormatMode { Standard, Scientific, DebugRaw, Full };
int format(const OpmNum& num, char* buffer, FormatMode mode);

OpmNum rand(OpmNum min, OpmNum max);

inline void print(const OpmNum& num)
{
	char str[256];
	memset(str, 0, 256);
	format(num, str, FormatMode::Scientific);
	std::cout << str << std::endl;
}

#include "OpmStrConstant.hpp"