#pragma once
#include "Config.h"
#include "MulTable.hpp"
#include <cstdint>

#define DIGIT(n, d) (((n).groups[(d) >> 3] >> ((7 - ((d) & 7)) * 4)) & 0xf)

inline uint32_t AddGroup(const uint32_t a, const uint32_t b, bool& carry) {
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
    uint64_t a2 = a + 0x0666666666666666;
    uint64_t partial_sum = a2 + b;
    uint64_t bitwise_sum = a2 ^ b;
    uint64_t carry_mask = (~(partial_sum ^ bitwise_sum)) & 0x1111111111111111;
    return partial_sum - ((carry_mask >> 2) | (carry_mask >> 3));
}

inline uint64_t MulGroup(const uint32_t a, const uint32_t b) {
    uint64_t out = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            out = AddDGroupNoCarry(out, static_cast<uint64_t>(MultiplyByte(static_cast<uint8_t>(a >> i * 8), static_cast<uint8_t>(b >> j * 8))) << (i + j) * 8);
        }
    }
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
				OpmNum t = num + scaler;
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