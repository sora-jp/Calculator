#include "OpmNum.hpp"
#include "Utils.hpp"
#include "cordic/Tables.hpp"

const uint32_t TC = 0x99999999;
OpmNum operator+(const OpmNum& a, const OpmNum& b)
{
    if (a.exponent < b.exponent) return b + a;

	if (is_zero(b)) return a;
    if (is_zero(a)) return b;

    OpmNum out, nb = b;

    nb >>= a.exponent - nb.exponent;
    out.exponent = a.exponent;

    bool isSub = a.isNegative != nb.isNegative;
    bool tcA = a.isNegative && isSub, tcB = nb.isNegative && isSub;
    bool carry = isSub;

    for (int i = GROUPS - 1; i >= 0; --i) 
    {
        out[i] = AddGroup(tcA ? TC - a[i] : a[i], tcB ? TC - nb[i] : nb[i], carry);
    }
	
    out.isNegative = isSub ? !carry : a.isNegative;

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
	out.normalize();
    return out;
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

inline void MulPass(OpmNum& out, int64_t* partialS)
{

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

    out.normalize();
    return out;
}

const OpmNum divPoly[4] =
{
        OpmNum::Constant<0x14986832,0x98050964,0x82742067,0x30439523,0x66230461,0x87429202,0x59636146,0x67358990,0x68738638>(false, 0),
        OpmNum::Constant<0x66125796,0x29489886,0x88927665,0x98275696,0x98963457,0x06396934,0x14872640,0x48435871,0x66542804>(true, -1),
        OpmNum::Constant<0x10481649,0x06581789,0x93427391,0x70156588,0x50880384,0x38786165,0x08659762,0x61251146,0x07168912>(false, -1),
        OpmNum::Constant<0x53308417,0x50369191,0x34030308,0x76979078,0x02451145,0x22748542,0x16562836,0x26420482,0x09293003>(true, -3)
};

const OpmNum divPoly2[3] =
{
        OpmNum::Constant<0x11824555,0x32034212,0x76300561,0x14500599,0x95749103,0x04307447,0x93153610,0x27279028,0x24951218>(false, 0),
        OpmNum::Constant<0x32698738,0x63616123,0x51790334,0x42777330,0x82625112,0x87899286,0x68690785,0x46114962,0x60592856>(true, -1),
        OpmNum::Constant<0x23088615,0x70207237,0x96404203,0x54508776,0x23157839,0x68390415,0x33913508,0x37790497,0x39356145>(false, -2)
};

OpmNum invert(const OpmNum& num)
{
	const int32_t nexp = -num.exponent;

	OpmNum o2 = num;
	o2.exponent = 0;
	o2.isNegative = false;
	
    OpmNum out = horner(o2, divPoly);
    
    for (int i = 0; i < 9; i++) {
        out = (out + out * (Constants::one - (out * o2)));
    }

    out.exponent += nexp;
	out.isNegative = num.isNegative;
    return out;
}

//TODO: This function really doesn't work. wierd error at x=7, about 10^51 ulp
OpmNum invert3(const OpmNum& num)
{
    return invert(num); // TODO: FIX THIS

	const int32_t nexp = -num.exponent;

	OpmNum o2 = num;
	o2.exponent = 0;
	o2.isNegative = false;
	
    OpmNum out = divPoly2[0] + o2 * (divPoly2[1] + o2 * divPoly2[2]);
    
    for (int i = 0; i < 4; i++) {
        OpmNum e = Constants::one - o2 * out;
        OpmNum y = out * e;
        out = out + y + y * e;
    }

    out.exponent += nexp;
	out.isNegative = num.isNegative;
    return out;
}

OpmNum operator/(const OpmNum& a, const OpmNum& b)
{
    return a * invert(b);
}
