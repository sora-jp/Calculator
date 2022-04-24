#include "OpmComplex.hpp"
#include "cordic/Tables.hpp"

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

OpmComplex mul_i(const OpmComplex& a) { return { -a.imag, a.real }; }
OpmComplex asin(const OpmComplex& a)
{
	return mul_i(ln(sqrt(1e0_opm - a * a) + mul_i(a)));
}

OpmComplex acos(const OpmComplex& a)
{
	return Constants::half_pi - asin(a);
}

OpmComplex atan(const OpmComplex& a)
{
	const auto ia = mul_i(a);
	return OpmComplex(0, -5e-1_opm) * ln((1e0_opm + ia) / (1e0_opm - ia));
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