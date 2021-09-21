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
#include "rt_poly/OpmDynamic.h"

#define TIMER_BEGIN(timer) auto _##timer##_1 = std::chrono::steady_clock::now()
#define TIMER_END(timer) auto _##timer##_2 = std::chrono::steady_clock::now()
#define TIME(timer) (std::chrono::duration<double, std::milli>(_##timer##_2 - _##timer##_1).count())

#define CALC_FN(s, f) {s, [](auto& stack) { f; }},
std::map<std::string, void(*)(OpmStack<10>&)> cfnMap = 
{
	CALC_FN("+",     stack.Push(stack.Pop() + stack.Pop()))
	CALC_FN("-",     stack.Push(stack.Pop() - stack.Pop()))
	CALC_FN("*",     stack.Push(stack.Pop() * stack.Pop()))
	CALC_FN("/",     stack.Push(stack.Pop() / stack.Pop()))
	
	CALC_FN("ln",    stack.Push(ln   (stack.Pop()).roundToNearest()))
	CALC_FN("log2",  stack.Push(log2 (stack.Pop()).roundToNearest()))
	CALC_FN("log10", stack.Push(log10(stack.Pop()).roundToNearest()))
	CALC_FN("log",   stack.Push(log  (stack.Pop(), stack.Pop()).roundToNearest()))
	
	CALC_FN("exp",   stack.Push(exp  (stack.Pop()).roundToNearest()))
	CALC_FN("exp2",  stack.Push(exp2 (stack.Pop()).roundToNearest()))
	CALC_FN("exp10", stack.Push(exp10(stack.Pop()).roundToNearest()))
	CALC_FN("pow",   stack.Push(pow  (stack.Pop(), stack.Pop()).roundToNearest()))

	CALC_FN("sin",   stack.Push(sin(stack.Pop()).roundToNearest()))
	CALC_FN("cos",   stack.Push(cos(stack.Pop()).roundToNearest()))
	CALC_FN("tan",   stack.Push(tan(stack.Pop()).roundToNearest()))
};

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		bool exit;
		const auto res = TestPrecision(argc, argv, exit);
		if (exit) return res;
	}

	//print(-1e7_opm);
	//print(1e7_opm);
	auto v1 = 7e1_opm;
	auto v2 = OpmComplex(4e0_opm, -3e1_opm);

	auto w1 = wrap(v1);
	auto w2 = wrap(v2);

	auto a1 = invert(w1);
	auto a2 = invert(w2);

	auto r1 = *unwrap<OpmNum>(a1);
	auto r2 = *unwrap<OpmComplex>(a2);

	print(r1);
	print(r2.real);
	print(r2.imag);
	//std::cout << Time(operator+, -1e7_opm, 1e7_opm, 1000000)  * 1000 << std::endl;
	//std::cout << Time(operator*, -1e7_opm, 1e7_opm, 1000000)  * 1000 << std::endl;
	//std::cout << Time(invert,  1e0_opm, 1e1_opm, 100000) * 1000 << std::endl;
	//std::cout << Time(invert3, 1e0_opm, 1e1_opm, 100000) * 1000 << std::endl;
	
	//ExpressionParser parser;
	//parser.RegisterFn("ln", ln);
	//parser.RegisterFn("exp", exp);
	//parser.RegisterFn("pow", pow);
	//parser.RegisterFn("sin", sin);
	//parser.RegisterFn("cos", cos);
	//parser.RegisterFn("tan", tan);

	//const auto expr = parser.Parse("1 / x");
	//auto ctx = ExpressionContext();
	//ctx.set(1.414e0_opm, "x");
	//
	//const auto res = expr(ctx);

	//char str[256] = {};
	//format(res, str, FormatMode::Standard);
	//std::cout << str << std::endl;
	
	//std::cout << "Ln(x)  took   " << Time(ln, 1e0_opm, 1e100_opm) << "ms" << std::endl;
	//std::cout << "Exp(x) took   " << Time(exp, -1e1_opm, 1e1_opm) << "ms" << std::endl;
	//std::cout << "Inv(x) took   " << Time(invert, -1e1_opm, 1e1_opm) << "ms" << std::endl;
	
	return 0;

	//OpmNum num;
	//std::string ss;
	//while (ss.length() == 0) std::getline(std::cin, ss);

	//num = parse(ss.c_str());

	//OpmNum s, c, t;
	//trig(num, s, c, t);

	//char sss[128];

	//memset(sss, 0, 128);
	//format(s, sss, FormatMode::Standard);
	//std::cout << sss << std::endl;

	//memset(sss, 0, 128);
	//format(c, sss, FormatMode::Standard);
	//std::cout << sss << std::endl;

	//memset(sss, 0, 128);
	//format(t, sss, FormatMode::Standard);
	//std::cout << sss << std::endl;

	//return 0;
	OpmStack<10> stack;
	while (true)
	{
		std::string ns;
		std::cin >> ns;
		
		for (int i = 0; i < 30; i++) std::cout << std::endl;

		bool didOp = false;
		for(const auto& [op, opFn] : cfnMap)
		{
			if (op == ns)
			{
				didOp = true;
				opFn(stack);
				break;
			}
		}
		if (!didOp)
		{
			auto n = parse(ns.c_str());
			stack.Push(n);
		}
		
		char buf[256];

		for (int i = 0; i < stack.StackSize(); i++) 
		{
			memset(buf, 0, 256);
			format(stack[i], buf, FormatMode::Standard);
			std::cout << buf << std::endl;
		}
	}
}
