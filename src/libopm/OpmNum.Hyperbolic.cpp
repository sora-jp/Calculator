#include "OpmNum.hpp"

OpmNum sinh(const OpmNum& arg)
{
	const auto d = invert(2 * exp(-arg));
	return d - d * exp(-2 * arg);
}

OpmNum cosh(const OpmNum& arg)
{
	const auto d = invert(2 * exp(-arg));
	return d + d * exp(-2 * arg);
}

OpmNum tanh(const OpmNum& arg)
{
	const auto d = exp(2e0_opm * arg);
	return (d - 1) / (d + 1);
}