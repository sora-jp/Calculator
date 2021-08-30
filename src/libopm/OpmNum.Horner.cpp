#include "OpmNum.hpp"

OpmNum horner(const OpmNum& x, const OpmNum* coeffs, const size_t size)
{
	OpmNum acc = coeffs[size - 1];
	if (size == 1) return acc;

	for (int i = static_cast<int>(size) - 2; i >= 0; i--)
	{
		acc = coeffs[i] + acc * x;
	}

	return acc;
}