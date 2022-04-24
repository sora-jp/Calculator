#include "OpmComplex.hpp"

OpmComplex operator+(const OpmComplex& a, const OpmComplex& b)
{
	return OpmComplex(a.real + b.real, a.imag + b.imag);
}

OpmComplex operator-(const OpmComplex& a)
{
	return OpmComplex(-a.real, -a.imag);
}

OpmComplex operator-(const OpmComplex& a, const OpmComplex& b)
{
	return OpmComplex(a.real - b.real, a.imag - b.imag);
}

OpmComplex operator*(const OpmComplex& a, const OpmComplex& b)
{
	return OpmComplex(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real);
}

OpmComplex invert(const OpmComplex& a)
{
	const auto invSqrMag = invert(a.real * a.real + a.imag * a.imag);
	return OpmComplex(a.real * invSqrMag, -a.imag * invSqrMag);
}

OpmComplex operator/(const OpmComplex& a, const OpmComplex& b)
{
	return a * invert(b);
}