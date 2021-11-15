#pragma once
#include "../OpmNum.hpp"

class OpmComplex
{
public:
	OpmNum real, imag;

	constexpr OpmComplex(const OpmNum& real) : real(real) {}
	constexpr OpmComplex(const OpmNum& real, const OpmNum& imag) : real(real), imag(imag) {}

	OpmComplex conjugate() const { return OpmComplex(real, -imag); }
	OpmNum magnitude() const { return sqrt(real * real + imag * imag); }
	OpmNum argument() const { return atan2(real, imag); }

	OpmComplex& roundToNearest()
	{
		real.roundToNearest();
		imag.roundToNearest();
		return *this;
	}

	OpmComplex& normalize()
	{
		real.normalize();
		imag.normalize();
		return *this;
	}
};

inline OpmComplex conjugate(const OpmComplex& a) { return a.conjugate(); }
inline OpmNum magnitude(const OpmComplex& a) { return a.magnitude(); }
inline OpmNum argument(const OpmComplex& a) { return a.argument(); }

OpmComplex operator+(const OpmComplex& a, const OpmComplex& b);
OpmComplex operator-(const OpmComplex& a);
OpmComplex operator-(const OpmComplex& a, const OpmComplex& b);
OpmComplex operator*(const OpmComplex& a, const OpmComplex& b);
OpmComplex operator/(const OpmComplex& a, const OpmComplex& b);
OpmComplex invert(const OpmComplex& a);

OpmComplex exp(const OpmComplex& a);
OpmComplex ln(const OpmComplex& a);
OpmComplex pow(const OpmComplex& a, const OpmComplex& b);

OpmComplex sin(const OpmComplex& a);
OpmComplex cos(const OpmComplex& a);
OpmComplex tan(const OpmComplex& a);

OpmComplex sinh(const OpmComplex& a);
OpmComplex cosh(const OpmComplex& a);
OpmComplex tanh(const OpmComplex& a);

int format(const OpmComplex& num, char* buffer, FormatMode mode);