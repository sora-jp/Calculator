#include "OpmDynamic.h"

#include "cordic/Tables.hpp"

bool is_zero(const OpmValue& value)
{
	if (value.type() == TypeOf<OpmNum>) return is_zero(*unwrap<OpmNum>(value));
	if (value.type() == TypeOf<OpmComplex>) return is_zero(*unwrap<OpmComplex>(value));
	return true;
};

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

OpmValue log(const OpmValue& a, const OpmValue& b)
{
	return ln(a) / ln(b);
}

OpmValue log10(const OpmValue& value) { return ln(value) / wrap(Constants::ln10); }
OpmValue log2(const OpmValue& value) { return ln(value) / wrap(Constants::ln2); }

IMPL_DYN_1(exp);
OpmValue pow(const OpmValue& a, const OpmValue& b)
{
	return exp(b * ln(a));
}

IMPL_DYN_1(sqrt);

IMPL_DYN_1(sin);
IMPL_DYN_1(cos);
IMPL_DYN_1(tan);

IMPL_DYN_1(sinh);
IMPL_DYN_1(cosh);
IMPL_DYN_1(tanh);

IMPL_DYN_1(asin);
IMPL_DYN_1(acos);
IMPL_DYN_1(atan);

int format(const OpmValue& value, char* buffer, FormatMode mode)
{
	if (value.type() == ValueType::Real) return format(*unwrap<OpmNum>(value), buffer, mode);
	if (value.type() == ValueType::Complex) return format(*unwrap<OpmComplex>(value), buffer, mode);
	return -1;
}