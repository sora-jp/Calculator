#include "OpmNum.hpp"
#include "cordic/Tables.hpp"
constexpr int32_t gammaA = 80;

OpmNum gamma(const OpmNum& x)
{
	OpmNum a = x - 1;

	OpmNum cNeg, cNegC, cPos, cPosC;
	for (int32_t i = 0; i < gammaA - 1; i++)
	{
		auto cur = Tables::gammaTable[i] / (a + (i + 1));
		if (i % 2 == 0)
		{
			auto y = cur - cNegC;
			auto t = cNeg + y;
			cNegC = (t - cNeg) - y;
			cNeg = t;
		}
		else
		{
			auto y = cur - cPosC;
			auto t = cPos + y;
			cPosC = (t - cPos) - y;
			cPos = t;
		}
	}

	auto c = (cPos + cNeg) - (cPosC + cNegC) + sqrt(2 * Constants::pi);
	return pow(a + gammaA, a + 5e-1_opm) * exp(-a - gammaA) * c;
}
