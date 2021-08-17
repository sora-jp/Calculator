#include "OpmNum.hpp"
#include "Utils.hpp"
#include "cordic/Tables.hpp"

const uint32_t TC = 0x99999999;
OpmNum operator+(const OpmNum& a, const OpmNum& b)
{
    if (is_zero(a)) return b;
	if (is_zero(b)) return a;
	
    OpmNum out, na = a, nb = b;
    if (na.exponent < nb.exponent) std::swap(na, nb);
    
    nb >>= na.exponent - nb.exponent;
    out.exponent = na.exponent;

    bool isSub = na.isNegative != nb.isNegative;
    bool tcA = na.isNegative && isSub, tcB = nb.isNegative && isSub;
    bool carry = isSub;

    for (int i = GROUPS - 1; i >= 0; --i) 
    {
        out[i] = AddGroup(tcA ? TC - na[i] : na[i], tcB ? TC - nb[i] : nb[i], carry);
    }
	
    out.isNegative = isSub ? !carry : na.isNegative;

    if (!carry && isSub) 
    {
        // Result is 10's compliment.
        carry = true;
        for (int i = GROUPS - 1; i >= 0; --i) out[i] = AddGroup(TC - out[i], 0, carry);
    }
    if (carry && !isSub) 
    {
        // We need to shift the carry in, and make the number 10x bigger (add 1 to the exponent)
        ++out.exponent;
        out >>= 1;
        out[0] |= 0x10000000;
    }
	
    return out.normalize();
}

OpmNum operator-(const OpmNum& a)
{
    OpmNum out(a);
    out.isNegative = !out.isNegative;
    return out;
}

OpmNum operator-(const OpmNum& a, const OpmNum& b)
{
    return a + (-b);
}

OpmNum operator*(const OpmNum& a, const OpmNum& b)
{
    OpmNum out;
    out.exponent   = a.exponent   + b.exponent;
    out.isNegative = a.isNegative ^ b.isNegative;

    uint64_t ovrflow = 0;
    for (int ai = GROUPS - 1; ai >= 0; --ai) 
    {
        if (a[ai] == 0) continue;
        uint64_t nxt = 0;

        for (int bi = GROUPS - (ai + 1); bi >= -ai; --bi) 
        {
            if (nxt == 0 && bi < 0) break;
            auto m = bi >= 0 ? MulGroup(a[ai], b[bi]) : 0;

            if (m != 0) nxt = AddDGroupNoCarry(nxt, m);
            nxt = AddDGroupNoCarry(out[ai + bi], nxt);

            out[ai + bi] = static_cast<uint32_t>(nxt);
            nxt >>= 32;
        }

        ovrflow = AddDGroupNoCarry(nxt, ovrflow);
    }
	
    if ((ovrflow & 0xf0000000) != 0) 
    {
        out >>= 8;
        out[0] = static_cast<uint32_t>(ovrflow);
        ++out.exponent;
    }
    else 
    {
        out >>= 7;
        out[0] |= ovrflow << 4;
    }

    return out.normalize();
}

static const OpmNum ia = OpmNum::Constant<0x49700000, 0, 0, 0, 0, 0, 0, 0, 0>(false, -2);
static const OpmNum ib = OpmNum::Constant<0x54670000, 0, 0, 0, 0, 0, 0, 0, 0>(false, -1);

OpmNum invert(const OpmNum& num)
{
	const int32_t nexp = -num.exponent;

	OpmNum o2 = num;
	o2.exponent = 0;
	o2.isNegative = false;
	
    OpmNum out = (ib - (o2 * ia));
    
    for (int i = 0; i < 10; i++) {
        out = (out + out * (Constants::one - (out * o2)));
    }

    out.exponent += nexp;
	out.isNegative = num.isNegative;
    return out;
}

OpmNum operator/(const OpmNum& a, const OpmNum& b)
{
    return a * invert(b);
}