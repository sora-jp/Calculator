#include <cstring>
#include <iostream>
#include <chrono>
#include <functional>
#include <string>
#include <map>

#include "OpmNum.hpp"
#include <StackBindings.hpp>

#include "PrecisionTest.h"

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

template<OpmNum(*Fn)(const OpmNum& num)>
void Handle(OpmStack<10>& stack)
{
	stack.Push(Fn(stack.Pop()));
}

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		bool exit;
		auto res = TestPrecision(argc, argv, exit);
		if (exit) return res;
	}


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
		Handle<sin>(stack);
		
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