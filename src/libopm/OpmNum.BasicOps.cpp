#include "OpmNum.hpp"
#include "Utils.hpp"
#include <cstring>

uint32_t& OpmNum::operator[](size_t idx)
{
    return this->groups[idx];
}

const uint32_t& OpmNum::operator[](size_t idx) const
{
    return this->groups[idx];
}

OpmNum operator>>(const OpmNum& a, int amt)
{
    if (is_nan(a) || is_inf(a)) return a;
    if (amt <= 0) return a;

    OpmNum out(a);

	if ((amt >> 3) > GROUPS)
	{
		memset(out.groups, 0, sizeof(uint32_t) * GROUPS);
		out.exponent = 0;
		out.isNegative = false;
		return out;
	}

    if ((amt >> 3) > 0) 
    {
    	// Group move
        memmove(&out.groups[amt >> 3], out.groups, sizeof(uint32_t) * (GROUPS - (amt >> 3)));
        memset(out.groups, 0, sizeof(uint32_t) * (amt >> 3));
    }

    amt &= 7;
    if (amt == 0) return out;

	// Move remaining amount
    out[GROUPS - 1] >>= 4 * amt;
    for (int i = GROUPS - 2; i >= 0; --i) 
    {
        out[i + 1] |= out[i] << (32 - (4 * amt));
        out[i] >>= 4 * amt;
    }
    return out;
}

OpmNum operator<<(const OpmNum& a, int amt)
{
    if (is_nan(a) || is_inf(a)) return a;
    if (amt <= 0) return a;

    OpmNum out(a);

	if ((amt >> 3) > GROUPS)
	{
		memset(out.groups, 0, sizeof(uint32_t) * GROUPS);
		out.exponent = 0;
		out.isNegative = false;
		return out;
	}

    if ((amt >> 3) > 0) 
    {
    	// Group move
        memmove(out.groups, &out.groups[amt >> 3], sizeof(uint32_t) * (GROUPS - (amt >> 3)));
        memset(&out.groups[amt >> 3], 0, sizeof(uint32_t) * (amt >> 3));
    }

    amt &= 7;
    if (amt == 0) return out;

	// Move remaining amount
    out[0] <<= 4 * amt;
    for (int i = 0; i <= GROUPS - 2; i++) 
    {
        out[i] = (out[i] << (4 * amt)) | (out[i + 1] >> (32 - (4 * amt)));
    }
    return out;
}

OpmNum& operator>>=(OpmNum& a, int amt)
{
    if (is_nan(a) || is_inf(a)) return a;
    a = a >> amt;
    return a;
}

OpmNum& operator<<=(OpmNum& a, int amt)
{
    if (is_nan(a) || is_inf(a)) return a;
    a = a << amt;
    return a;
}

OpmNum abs(const OpmNum& a)
{
    if (is_nan(a)) return a;
    auto o = a;
	o.isNegative = false;
	return o;
}

OpmNum& OpmNum::roundToNearest()
{
    if (is_nan(*this) || is_inf(*this)) return *this;
    if ((this->groups[GROUPS - 1] & 0xf0000000) >= 0x50000000) 
    {
        if (PartialAddD(*this, 0x1, GROUPS - 2)) 
        {
            (*this) >>= 1;
            this->groups[0] |= 0x10000000;
            return *this;
        }
    }
	
    this->groups[GROUPS - 1] = 0;
    return *this;
}

OpmNum& OpmNum::normalize()
{
    //if (groups[0] & 0x10000000) return *this;
    if (is_nan(*this) || is_inf(*this)) return *this;

    bool zero = true;
	for (auto g : groups) zero &= g == 0;
	if (zero) return *this;
	
	while(!(groups[0] & 0xf0000000))
	{
	    for (int i = 0; i <= GROUPS - 2; ++i) 
	    {
	        groups[i] = (groups[i] << (4)) | (groups[i + 1] >> (32 - 4));
	    }
		groups[GROUPS - 1] <<= 4;
		exponent--;
	}

	return *this;
}
