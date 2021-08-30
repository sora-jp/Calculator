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

const OpmNum divPoly[4] =
{
        OpmNum::Constant<0x14986832,0x98050964,0x82742067,0x30439523,0x66230461,0x87429202,0x59636146,0x67358990,0x68738638>(false, 0),
        OpmNum::Constant<0x66125796,0x29489886,0x88927665,0x98275696,0x98963457,0x06396934,0x14872640,0x48435871,0x66542804>(true, -1),
        OpmNum::Constant<0x10481649,0x06581789,0x93427391,0x70156588,0x50880384,0x38786165,0x08659762,0x61251146,0x07168912>(false, -1),
        OpmNum::Constant<0x53308417,0x50369191,0x34030308,0x76979078,0x02451145,0x22748542,0x16562836,0x26420482,0x09293003>(true, -3)
};

OpmNum invert(const OpmNum& num)
{
	const int32_t nexp = -num.exponent;

	OpmNum o2 = num;
	o2.exponent = 0;
	o2.isNegative = false;
	
    OpmNum out = horner(o2, divPoly);
    
    for (int i = 0; i < 6; i++) {
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