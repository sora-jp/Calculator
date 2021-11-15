#include "OpmComplex.hpp"

int format(const OpmComplex& num, char* buffer, FormatMode mode)
{
	size_t p = format(num.real, buffer, mode);
	buffer[p + 1] = ' ';
	buffer[p + 2] = num.imag.isNegative ? '-' : '+';
	buffer[p + 3] = ' ';
	p += static_cast<size_t>(format(abs(num.imag), buffer + p + 4, mode)) + 4;
	buffer[p + 1] = 'i';
	return static_cast<int>(p + 1);
}