#pragma once
#include "expr/NExpression.h"
#include "rt_poly/OpmValue.h"

namespace Algorithm
{
	OpmValue adaptiveSimpson(const NCompiledExpression& expr, const OpmNum& left, const OpmNum& right, const OpmNum& tolerance);
}
