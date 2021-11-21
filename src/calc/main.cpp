#include <cstring>
#include <iostream>
#include <chrono>
#include <functional>
#include <string>
#include <map>

#include "OpmNum.hpp"
#include <StackBindings.hpp>

#include "PrecisionTest.h"
#include "OpmRand.hpp"
#include "Timing.h"
#include "cordic/Tables.hpp"
#include "expr/NDerivative.h"
#include "rt_poly/OpmDynamic.h"
#include "expr/NExpression.h"

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		bool exit;
		const auto res = TestPrecision(argc, argv, exit);
		if (exit) return res;
	}

	NExpressionParser nparser;
	nparser.registerFn("ln", ln);
	nparser.registerFn("exp", exp);
	nparser.registerFn("pow", pow);
	nparser.registerFn("sin", sin);
	nparser.registerFn("cos", cos);
	nparser.registerFn("tan", tan);

	NExpressionContext ctx;
	ctx.set(5e0_opm, "k");
	ctx.set(5e0_opm, "x");

	NDerivativeRewriter rw;

	auto expr2 = nparser.parse("x)z");
	auto expr3 = nparser.rewrite(rw, expr2);
	auto cmp = nparser.compile(expr3);
	auto res = cmp.exec(ctx);

	NExpressionParser::Print(expr2);
	NExpressionParser::Print(expr3);

	char str[256] = {};
	format(res, str, FormatMode::Standard);
	std::cout << str << std::endl;

	//std::cout << std::endl << "AFTER REWRITE" << std::endl;
	////NExpressionParser::Print(expr3);

	//auto ctx2 = NExpressionContext();
	//ctx2.set(8e0_opm, "x");

	//auto res2 = cmp.exec(ctx2);
	//char str2[256] = {};
	//format(res2, str2, FormatMode::Standard);
	//std::cout << str2 << std::endl;

	//ExpressionParser parser;
	//parser.RegisterFn("ln", ln);
	//parser.RegisterFn("exp", exp);
	//parser.RegisterFn("pow", pow);
	//parser.RegisterFn("sin", sin);
	//parser.RegisterFn("cos", cos);
	//parser.RegisterFn("tan", tan);

	//const auto expr = parser.Parse("(-2)^(0.5)");
	//auto ctx = ExpressionContext();
	//ctx.set(OpmComplex(0e0_opm, 1e0_opm), "i");
	//
	//const auto res = expr(ctx);

	//char str[256] = {};
	//format(res, str, FormatMode::Standard);
	//std::cout << str << std::endl;

	//std::cout << "Ln(x)  took   " << Time(ln, 1e0_opm, 1e100_opm) << "ms" << std::endl;
	//std::cout << "Exp(x) took   " << Time(exp, -1e1_opm, 1e1_opm) << "ms" << std::endl;
	//std::cout << "Inv(x) took   " << Time(invert, -1e1_opm, 1e1_opm) << "ms" << std::endl;
	
	return 0;
}
