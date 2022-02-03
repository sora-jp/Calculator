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
#include "expr/Expressions.h"
#include "expr/NDerivative.h"
#include "rt_poly/OpmDynamic.h"
#include "expr/NExpression.h"
#include "expr/NSimplify.h"
#include "alg/Algorithm.h"

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"  // for Ref

using namespace ftxui;

std::ostream& operator<<(std::ostream& s, const OpmValue& n)
{
	char o[256] = {};
	format(n, o, FormatMode::Standard);
	s << o;

	return s;
}

struct HistoryData
{
	std::string input;
	NExpression expr;
	OpmValue answer;
};

std::vector<HistoryData> s_history;

Element renderStack()
{
	Elements elems;

	for (int i = 0; i < s_history.size(); i++)
	{
		std::string ss;
		if (s_history[i].answer.type() == ValueType::Invalid) 
		{
			ss = NExpressionParser::ToString(s_history[i].expr);
		}
		else 
		{
			char s[256] = {};
			format(s_history[i].answer, s, FormatMode::Standard);
			ss = s;
		}

		elems.push_back(
			vbox({
				text(s_history[i].input),
				hbox(
					text(L"\u2570\u2500[" + std::to_wstring(s_history.size() - i) + L"]") | color(Color::GrayDark),
					text(L"\u2500\u2500> ") | color(Color::GrayDark),
					text(ss) | color(Color::Green)
				),
				text(""),
				separatorLight() | color(Color::GrayDark),
				text("")
			})
		);
	}

	return vbox(std::move(elems));
}

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		bool exit;
		const auto res = TestPrecision(argc, argv, exit);
		if (exit) return res;
	}

	NExpressionContext ctx;
	ctx.set(OpmComplex(0, 1), "i");
	ctx.set(Constants::pi, "pi");
	
	std::string cmd;
	InputOption opt;
	opt.on_enter = [&]
	{
		bool de = false;
		if (cmd.substr(0, 3) == "/d ")
		{
			de = true;
			cmd = cmd.substr(3);
		}

		auto expr = Expression::parse(cmd);
		if (de)
		{
			NDerivative d;
			NSimplify s;
			expr = Expression::rewrite(Expression::rewrite(expr, d), s);
		}

		auto ce = Expression::compile(expr);
		if (expr.type == NExpressionType::FunctionDefinition)
		{
			std::string fnName = expr.fnData.front();

			ctx.set(FunctionImplementation{ expr, ce, std::vector<std::string> {expr.fnData.begin() + 1, expr.fnData.end()} }, FunctionDefinition{ fnName, static_cast<uint32_t>(expr.fnData.size() - 1) });
			s_history.push_back({ cmd, expr, OpmValue {} });
		}
		else if (expr.type == NExpressionType::VariableAssignment)
		{
			auto res = ce.exec(ctx);
			ctx.set(ce.exec(ctx), expr.varName);
			s_history.push_back({ cmd, expr, res });
		}
		else
		{
			auto res = ce.exec(ctx);
			s_history.push_back({ cmd, expr, res });
		}

		cmd.clear();
	};

	auto inp = Input(&cmd, "Enter command", opt);

	auto component = Container::Vertical({
		inp
	});

	auto renderer = Renderer(inp, [&] {
		Element elem = text(" ") | inverted;
		if (!cmd.empty()) elem = inp->Render();

		return vbox({
					renderStack(),
					filler(),
					hbox(text("> ") | color(Color::GrayDark), elem)
			});
		}
	);

	auto screen = ScreenInteractive::Fullscreen();
	screen.Loop(renderer);

	return 0;
}


//int main(int argc, char** argv)
//{
//	if (argc > 1)
//	{
//		bool exit;
//		const auto res = TestPrecision(argc, argv, exit);
//		if (exit) return res;
//	}
//	Term::Terminal term(true);
//	std::string scr;
//	std::string cl;
//	scr.reserve(16 * 1024);
//	cl.reserve(16 * 1024);
//
//	NExpressionContext ctx;
//	ctx.set(OpmComplex(0, 1), "i");
//	ctx.set(Constants::pi, "pi");
//
//	scr.append(Term::clear_screen());
//	scr.append(Term::move_cursor(0, 0));
//
//	while (true)
//	{
//		scr.append(Term::cursor_off());
//		scr.append(Term::color(Term::fg::gray));
//		scr.append("> ");
//		scr.append(Term::color(Term::fg::white));
//		scr.append(Term::cursor_on());
//		std::cout << scr << std::flush;
//
//		std::getline(std::cin, cl);
//
//		auto expr = Expression::parse(cl);
//		auto ce = Expression::compile(expr);
//		auto res = ce.exec(ctx);
//
//		scr.append(cl);
//		cl.clear();
//		//scr.append("\n");
//		scr.append(Term::cursor_off());
//		scr.append(Term::color(Term::fg::gray));
//		scr.append(" -> ");
//		char s[256] = {};
//		format(res, s, FormatMode::Standard);
//		scr.append(s);
//		scr.append("\n\n");
//		scr.append(Term::cursor_on());
//		std::cout << scr << std::flush;
//
//		s_stack.Push(res);
//	}
//	
//	return 0;
//}
