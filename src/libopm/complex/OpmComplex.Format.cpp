#include "OpmComplex.hpp"

int format(const OpmComplex& num, char* buffer, FormatMode mode)
{
	size_t p = format(num.real, buffer, mode);
	buffer[p++] = ' ';
	buffer[p++] = num.imag.isNegative ? '-' : '+';
	buffer[p++] = ' ';
	p += static_cast<size_t>(format(abs(num.imag), buffer + p, mode));
	buffer[p++] = 'i';
	return static_cast<int>(p);
}