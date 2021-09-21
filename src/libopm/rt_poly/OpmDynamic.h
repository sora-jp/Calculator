#pragma once
#include "OpmValue.h"

#define DECLARE_DYN_1(name) OpmValue name(const OpmValue& value);
#define IMPL_DYN_1(name) OpmValue name(const OpmValue& value) \
	{ \
		if (value.type() == TypeOf<OpmNum>)     return wrap(name(*unwrap<OpmNum>    (value))); \
		if (value.type() == TypeOf<OpmComplex>) return wrap(name(*unwrap<OpmComplex>(value))); \
		return Invalid; \
	}
//#define CALL_DYN(name, ...) dyn_##name(__VA_ARGS__)

DECLARE_DYN_1(invert);