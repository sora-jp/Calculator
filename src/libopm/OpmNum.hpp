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
    
    OpmNum() : isNegative(false), isNan(false), isInfinity(false), exponent(0) {}
    OpmNum(const OpmNum& copy) = default;
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
OpmNum invert3(const OpmNum& a);

OpmNum ln(const OpmNum& arg);
OpmNum log2(const OpmNum& arg);
OpmNum log10(const OpmNum& arg);
OpmNum log(const OpmNum& arg, const OpmNum& base);

OpmNum exp(const OpmNum& arg);
OpmNum exp2(const OpmNum& arg);
OpmNum exp10(const OpmNum& arg);
OpmNum pow(const OpmNum& x, const OpmNum& y);

OpmNum sin(const OpmNum& arg);
OpmNum cos(const OpmNum& arg);
OpmNum tan(const OpmNum& arg);
OpmNum cot(const OpmNum& arg);
void trig(const OpmNum& arg, OpmNum& sin, OpmNum& cos, OpmNum& tan);

OpmNum asin(const OpmNum& arg);
OpmNum acos(const OpmNum& arg);
OpmNum atan(const OpmNum& arg);
OpmNum atan2(const OpmNum& x, const OpmNum& y);

OpmNum horner(const OpmNum& x, const OpmNum* coeffs, size_t size);

template<size_t Size>
OpmNum horner(const OpmNum& x, const OpmNum (&coeffs)[Size]) { return horner(x, coeffs, Size); }

OpmNum parse(const char* str);

enum class FormatMode { Standard, Scientific, DebugRaw, Full };
int format(const OpmNum& num, char* buffer, FormatMode mode);

inline void print(const OpmNum& num)
{
	char str[256] = {};
	format(num, str, FormatMode::Scientific);
	std::cout << str << std::endl;
}

#include "OpmStrConstant.hpp"

template<int32_t A, int32_t B>
struct equal : std::false_type{};

template<int32_t A>
struct equal<A, A> : std::true_type{};

template<size_t Size, int32_t Index>
OpmNum horner_impl(const OpmNum& x, const OpmNum(&coeffs)[Size], std::false_type)
{
	return coeffs[Index];
}

template<size_t Size, int32_t Index>
OpmNum horner_impl(const OpmNum& x, const OpmNum(&coeffs)[Size], std::true_type)
{
	return coeffs[Index] + x * horner_impl<Size, Index + 1>(x, coeffs, equal<Index + 2, Size> {});
}

template<size_t Size>
OpmNum horner_c(const OpmNum& x, const OpmNum(&coeffs)[Size])
{
	return horner_impl<Size, 0>(x, coeffs, std::true_type {});
}