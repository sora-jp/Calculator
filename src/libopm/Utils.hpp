#pragma once
#include "Config.h"
#include "MulTable.hpp"
#include "OpmNum.hpp"
#include <cstdint>

#define DIGIT(n, d) (((n).groups[(d) >> 3] >> ((7 - ((d) & 7)) * 4)) & 0xf)

inline uint32_t AddGroup(const uint32_t a, const uint32_t b, bool& carry) {
    if (a == 0 && !carry) return b;
    if (b == 0 && !carry) return a;

    uint64_t a2 = a + 0x0666666666666666;

    uint64_t partial_sum = a2 + b + (carry ? 1 : 0);
    uint64_t bitwise_sum = a2 ^ b ^ (carry ? 1 : 0);
    uint64_t carry_mask = (~(partial_sum ^ bitwise_sum)) & 0x1111111111111111;

    uint64_t output = partial_sum - ((carry_mask >> 2) | (carry_mask >> 3));
    carry = output >> 32;
    return static_cast<uint32_t>(output);
}

inline uint32_t AddGroupNoCarry(const uint32_t a, const uint32_t b) {
    uint64_t a2 = a + 0x0666666666666666;

    uint64_t partial_sum = a2 + b;
    uint64_t bitwise_sum = a2 ^ b;
    uint64_t carry_mask = (~(partial_sum ^ bitwise_sum)) & 0x1111111111111111;
    
    return static_cast<uint32_t>(partial_sum - (carry_mask >> 2 | carry_mask >> 3));
}

inline uint64_t AddDGroupNoCarry(const uint64_t a, const uint64_t b) {
    const uint64_t a2 = a + 0x0666666666666666;
    const uint64_t partial_sum = a2 + b;
    const uint64_t bitwise_sum = a2 ^ b;
    const uint64_t carry_mask = (~(partial_sum ^ bitwise_sum)) & 0x1111111111111111;
    return partial_sum - ((carry_mask >> 2) | (carry_mask >> 3));
}

inline uint64_t MulGroup(const uint32_t a, const uint32_t b) {
    uint64_t out = 0;

    const uint64_t partialO1 = 
		  MultiplyByteWide(a, b)					// 0 0
		| MultiplyByteWide(a >> 8, b >> 8) << 16	// 1 1
		| MultiplyByteWide(a >> 16, b >> 16) << 32	// 2 2
		| MultiplyByteWide(a >> 24, b >> 24) << 48; // 3 3

    const uint64_t partialO2 = 
	  	  MultiplyByteWide(a, b >> 8) << 8			// 0 1
		| MultiplyByteWide(a >> 8, b >> 16) << 24	// 1 2
		| MultiplyByteWide(a >> 16, b >> 24) << 40; // 2 3

    const uint64_t partialO3 = 
		  MultiplyByteWide(a >> 8, b) << 8			// 1 0
		| MultiplyByteWide(a >> 16, b >> 8) << 24	// 2 1
		| MultiplyByteWide(a >> 24, b >> 16) << 40; // 3 2

    const uint64_t partialO4 = 
		  MultiplyByteWide(a >> 16, b) << 16		// 2 0
		| MultiplyByteWide(a >> 24, b >> 8) << 32;	// 3 1

    const uint64_t partialO5 = 
		  MultiplyByteWide(a, b >> 16) << 16		// 0 2
		| MultiplyByteWide(a >> 8, b >> 24) << 32;	// 1 3

    const uint64_t partialO6 = 
		MultiplyByteWide(a >> 24, b) << 24;			// 3 0

    const uint64_t partialO7 = 
		MultiplyByteWide(a, b >> 24) << 24;			// 0 3

	out = AddDGroupNoCarry(partialO1, partialO2);
	out = AddDGroupNoCarry(out, partialO3);
	out = AddDGroupNoCarry(out, partialO4);
	out = AddDGroupNoCarry(out, partialO5);
	out = AddDGroupNoCarry(out, partialO6);
	out = AddDGroupNoCarry(out, partialO7);

	return out;
}

// returns overflow
inline uint32_t PartialAddD(OpmNum& a, uint64_t val, uint32_t lowGroupStart) {
    bool carry = false;
    if (lowGroupStart < GROUPS) a[lowGroupStart] = AddGroup(a[lowGroupStart], static_cast<uint32_t>(val), carry);

    if (lowGroupStart < 1) [[unlikely]] return val >> 32;
    a[lowGroupStart - 1u] = AddGroup(a[lowGroupStart - 1u], val >> 32, carry);

    for (int32_t i = lowGroupStart - 2u; carry && i >= 0; i--) [[unlikely]] {
        a[i] = AddGroup(a[i], 0, carry);
    }

    return carry ? 1 : 0;
}

inline uint32_t Prescale(OpmNum& num, const OpmNum& scaleConstant)
{
	uint32_t out = 0;
	
	if (num.exponent >= scaleConstant.exponent)
	{
		OpmNum scaler = scaleConstant;
		scaler.isNegative = !num.isNegative;
		
		for (int i = num.exponent; i >= scaleConstant.exponent; i--)
		{
			scaler.exponent = i;
			out *= 10;
			
			do
			{
				const OpmNum t = num + scaler;
	            if (t.isNegative) break;
				
				num = t;
	            ++out;
			} while (true);
		}
	}

	return out;
}

inline void PsDiv(OpmNum& acc, const OpmNum* table, uint8_t* coeffs)
{
	for (uint32_t i = 0; i < GROUPS * 8; i++)
	{
        uint8_t count = 0;
		
		do
		{
			OpmNum y = -table[i];

			const OpmNum t = acc + y;
            if (t.isNegative) break;
			
			acc = t;
            ++count;
		} while (true);
		
		coeffs[i] = count;
	}
}

inline OpmNum PsMul(const OpmNum* table, const uint8_t* coeffs)
{
	OpmNum o;

	for (int i = DIGITCOUNT - 1; i >= 0; i--)
	{
		o = o + table[i] * OpmNum(coeffs[i]);
	}

	return o;
}