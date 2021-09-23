#include "OpmDynamic.h"

#include "cordic/Tables.hpp"

IMPL_DYN_1(invert);
IMPL_DYN_1(operator-);

IMPL_DYN_2(operator+);
IMPL_DYN_2(operator-);
IMPL_DYN_2(operator*);
IMPL_DYN_2(operator/);

OpmValue ln(const OpmValue& value)
{
	if (value.type() == TypeOf<OpmNum>) 
	{
		const auto* var = unwrap<OpmNum>(value);
		if (var->isNegative) return wrap(OpmComplex(ln(-*var), Constants::pi));
		return wrap(ln(*var));
	}
	if (value.type() == TypeOf<OpmComplex>) return wrap(ln(*unwrap<OpmComplex>(value)));
	return OpmValue();
};

IMPL_DYN_1(exp);
OpmValue pow(const OpmValue& a, const OpmValue& b)
{
	return exp(b * ln(a));
}

IMPL_DYN_1(sin);
IMPL_DYN_1(cos);
IMPL_DYN_1(tan);

IMPL_DYN_1(sinh);
IMPL_DYN_1(cosh);
IMPL_DYN_1(tanh);