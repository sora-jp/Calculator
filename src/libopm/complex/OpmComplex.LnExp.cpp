#include "OpmComplex.hpp"

OpmComplex exp(const OpmComplex& a)
{
	const auto p1 = exp(a.real);
	const auto x = cos(a.imag);
	const auto y = sin(a.imag);
	return OpmComplex(p1 * x, p1 * y);
}

OpmComplex ln(const OpmComplex& a)
{
	return OpmComplex(ln(sqrt(a.real * a.real + a.imag * a.imag)), atan2(a.real, a.imag));
}

OpmComplex pow(const OpmComplex& a, const OpmComplex& b)
{
	return exp(b * ln(a));
}

OpmComplex sqrt(const OpmComplex& a)
{
	auto l = ln(a);
	l.real = l.real * 5e-1_opm;
	l.imag = l.imag * 5e-1_opm;
	return exp(l);
}