#pragma once
#include "OpmValue.h"

#define DECLARE_DYN_1(name) OpmValue name(const OpmValue& value)
#define IMPL_DYN_1(name) OpmValue name(const OpmValue& value) \
	{ \
		if (value.type() == TypeOf<OpmNum>)     return wrap(name(*unwrap<OpmNum>    (value))); \
		if (value.type() == TypeOf<OpmComplex>) return wrap(name(*unwrap<OpmComplex>(value))); \
		return OpmValue(); \
	}

#define DECLARE_DYN_2(name) OpmValue name(const OpmValue& a, const OpmValue& b)
#define IMPL_DYN_2(name) OpmValue name(const OpmValue& a, const OpmValue& b) \
	{ \
		auto t1 = a.type(); \
		auto t2 = b.type(); \
		if (t1 == TypeOf<OpmComplex> && t2 == TypeOf<OpmComplex>) return wrap(name(*unwrap<OpmComplex>(a), *unwrap<OpmComplex>(b))); \
		if (t1 == TypeOf<OpmComplex> && t2 == TypeOf<OpmNum>)	  return wrap(name(*unwrap<OpmComplex>(a), *unwrap<OpmNum>    (b))); \
		if (t1 == TypeOf<OpmNum>     && t2 == TypeOf<OpmComplex>) return wrap(name(*unwrap<OpmNum>    (a), *unwrap<OpmComplex>(b))); \
		if (t1 == TypeOf<OpmNum>     && t2 == TypeOf<OpmNum>)     return wrap(name(*unwrap<OpmNum>    (a), *unwrap<OpmNum>    (b))); \
		return OpmValue(); \
	}

bool is_zero(const OpmValue& value);

DECLARE_DYN_1(invert);
DECLARE_DYN_1(operator-);

DECLARE_DYN_2(operator+);
DECLARE_DYN_2(operator-);
DECLARE_DYN_2(operator*);
DECLARE_DYN_2(operator/);

DECLARE_DYN_1(ln);
DECLARE_DYN_2(log);
DECLARE_DYN_1(exp);
DECLARE_DYN_1(sqrt);
DECLARE_DYN_2(pow);

DECLARE_DYN_1(sin);
DECLARE_DYN_1(cos);
DECLARE_DYN_1(tan);

DECLARE_DYN_1(sinh);
DECLARE_DYN_1(cosh);
DECLARE_DYN_1(tanh);

DECLARE_DYN_1(asin);
DECLARE_DYN_1(acos);
DECLARE_DYN_1(atan);

int format(const OpmValue& value, char* buffer, FormatMode mode);