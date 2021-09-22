#include "OpmComplex.hpp"

OpmComplex sin(const OpmComplex& a)
{
	return OpmComplex(sin(a.real) * cosh(a.imag), cos(a.real) * sinh(a.imag));
}

OpmComplex cos(const OpmComplex& a)
{
	return OpmComplex(cos(a.real) * cosh(a.imag), -sin(a.real) * sinh(a.imag));
}

OpmComplex tan(const OpmComplex& a)
{
	return sin(a) / cos(a);
}

OpmComplex sinh(const OpmComplex& a)
{
	return OpmComplex(sinh(a.real) * cos(a.imag), cosh(a.real) * sin(a.imag));
}

OpmComplex cosh(const OpmComplex& a)
{
	return OpmComplex(cosh(a.real) * cos(a.imag), sinh(a.real) * sin(a.imag));
}

OpmComplex tanh(const OpmComplex& a)
{
	return sinh(a) / cosh(a);
}