#include <cstdint>
#include <cstring>
#include <iostream>
#include <chrono>
#include <functional>
#include <string>
#include <map>

#include "OpmNum.hpp"
#include <StackBindings.hpp>

#include "PrecisionTest.h"
#include "cordic/Tables.hpp"

#define TIMER_BEGIN(timer) auto _##timer##_1 = std::chrono::steady_clock::now()
#define TIMER_END(timer) auto _##timer##_2 = std::chrono::steady_clock::now()
#define TIME(timer) (std::chrono::duration<double, std::milli>(_##timer##_2 - _##timer##_1).count())

void LogNumRaw(const OpmNum& num) {
  std::cout << (num.isNegative ? "-" : "");
  for (int i = 0; i < GROUPS - 1; i++) {
    for (int j = sizeof(uint32_t) * 2 - 1; j >= 0; j--) {
      std::cout << ((num.groups[i] >> (j << 2)) & 0xf);
      if (!i && j == (sizeof(uint32_t) * 2 - 1)) std::cout << ".";
    }
  }
  //std::cout << "E" << num.exponent << std::endl;
}

#define TEST_ITERS 1000
void TestOp(const OpmNum& a, const OpmNum& b, const std::string& id, const std::function<OpmNum(const OpmNum&, const OpmNum&)> op)
{
	auto n2 = op(a, b);
	double aggregate = 0;
	for (int i = 0; i < TEST_ITERS; i++) {
		TIMER_BEGIN(subtimer);
		n2 =  op(a, b);
		TIMER_END(subtimer);
		aggregate += TIME(subtimer);
	}

	std::cout << (aggregate) << "ms total" << std::endl;
	std::cout << (aggregate / TEST_ITERS) << "ms per op" << std::endl;
	std::cout << ("  ");
	LogNumRaw(a);
	std::cout << id << (" ");
	LogNumRaw(b);
	std::cout << ("= ");
	LogNumRaw(n2);
	std::cout << std::endl;
}

void TestOp(const OpmNum& a, const std::string& id, const std::function<OpmNum(const OpmNum&)> op)
{
	auto n2 = op(a);
	double aggregate = 0;
	for (int i = 0; i < 1; i++) {
		TIMER_BEGIN(subtimer);
		n2 =  op(a);
		TIMER_END(subtimer);
		aggregate += TIME(subtimer);
	}

	std::cout << (aggregate) << std::endl;
	std::cout << (aggregate / 1000) << std::endl;
	std::cout << id;
	LogNumRaw(a);
	std::cout << std::endl << ("=  ");
	char s[128];
	
	memset(s, 0, 128);
	format(n2, s, FormatMode::Standard);
	std::cout << s << std::endl;
	
	//LogNumRaw(n2);
}

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
};

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		bool exit;
		auto res = TestPrecision(argc, argv, exit);
		if (exit) return res;
	}

	OpmNum num;
	std::string ss;
	while (ss.length() == 0) std::getline(std::cin, ss);

	num = parse(ss.c_str());

	OpmNum s, c, t;
	trig(num, s, c, t);

	char sss[128];

	memset(sss, 0, 128);
	format(s, sss, FormatMode::Standard);
	std::cout << sss << std::endl;

	memset(sss, 0, 128);
	format(c, sss, FormatMode::Standard);
	std::cout << sss << std::endl;

	memset(sss, 0, 128);
	format(t, sss, FormatMode::Standard);
	std::cout << sss << std::endl;

	return 0;
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
	
	//for(;;) 
	{
		OpmNum num;
		num.groups[0] = 0x20000000;
		num.exponent = 0;

		OpmNum num2 = num;
		num2.exponent = 0;
		num2.groups[0] = num2.groups[1] = 0x23000000;

		TestOp(num, num2, "+", std::plus<>());
		TestOp(num, num2, "-", std::minus<>());
		TestOp(num, num2, "*", std::multiplies<>());
		TestOp(num, num2, "/", std::divides<>());
		TestOp(num, "ln ", [](const OpmNum& n) { return ln(n); });
	}
}