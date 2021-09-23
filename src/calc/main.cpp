#include <cstring>
#include <iostream>
#include <chrono>
#include <functional>
#include <string>
#include <map>

#include "OpmNum.hpp"
#include <StackBindings.hpp>

#include "Expressions.hpp"
#include "PrecisionTest.h"
#include "OpmRand.hpp"
#include "Timing.h"
#include "cordic/Tables.hpp"
#include "rt_poly/OpmDynamic.h"

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		bool exit;
		const auto res = TestPrecision(argc, argv, exit);
		if (exit) return res;
	}

	ExpressionParser parser;
	parser.RegisterFn("ln", ln);
	parser.RegisterFn("exp", exp);
	parser.RegisterFn("pow", pow);
	parser.RegisterFn("sin", sin);
	parser.RegisterFn("cos", cos);
	parser.RegisterFn("tan", tan);

	const auto expr = parser.Parse("(2+3i) * (4+5i)");
	auto ctx = ExpressionContext();
	ctx.set(OpmComplex(0e0_opm, 1e0_opm), "i");
	
	const auto res = expr(ctx);

	if (res.type() == TypeOf<OpmNum>) 
	{
		char str[256] = {};
		format(*unwrap<OpmNum>(res), str, FormatMode::Standard);
		std::cout << str << std::endl;
	}
	if (res.type() == TypeOf<OpmComplex>)
	{
		auto prs = unwrap<OpmComplex>(res);
		char str[256] = {};
		format(prs->real, str, FormatMode::Standard);
		std::cout << str << std::endl;
		memset(str, 0, 256);
		format(prs->imag, str, FormatMode::Standard);
		std::cout << str << "i" << std::endl;
	}

	//std::cout << "Ln(x)  took   " << Time(ln, 1e0_opm, 1e100_opm) << "ms" << std::endl;
	//std::cout << "Exp(x) took   " << Time(exp, -1e1_opm, 1e1_opm) << "ms" << std::endl;
	//std::cout << "Inv(x) took   " << Time(invert, -1e1_opm, 1e1_opm) << "ms" << std::endl;
	
	return 0;
}
