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
	NErrorCollection errs;
	NExpression expr;
	OpmValue answer;
};

std::vector<HistoryData> s_history;

NExpression& getHistoryRef(int idx)
{
	if (idx <= 0) abort();
	return s_history.at(s_history.size() - idx).expr;
}

std::string tostring(ErrorClass cls)
{
	if (cls == ErrorClass::Parsing) return "Parsing";
	if (cls == ErrorClass::Evaluation) return "Evaluation";
	if (cls == ErrorClass::Compilation) return "Compilation";
	if (cls == ErrorClass::Binding) return "Binding";
	if (cls == ErrorClass::Conversion) return "Conversion";
	return "Unknown";
}

std::string tostring(ErrorType type)
{
	if (type == ErrorType::Invalid) return "Invalid";
	if (type == ErrorType::Info) return "Info";
	if (type == ErrorType::Warning) return "Warning";
	if (type == ErrorType::Error) return "Error";
}

Decorator getcolor(ErrorType type)
{
	if (type == ErrorType::Invalid) return color(Color::GrayDark);
	if (type == ErrorType::Info) return color(Color::GrayDark);
	if (type == ErrorType::Warning) return color(Color::Yellow);
	if (type == ErrorType::Error) return color(Color::Red);
}

Element renderStack()
{
	Elements elems;
	int start = static_cast<int32_t>(s_history.size()) - 5;
	if (start < 0) start = 0;
	for (int i = start; i < s_history.size(); i++)
	{
		std::string ss;
		if (!s_history[i].errs.empty()) {}
		else if (s_history[i].answer.type() == ValueType::Invalid) 
		{
			ss = NExpressionParser::ToString(s_history[i].expr);
		}
		else 
		{
			char s[256] = {};
			format(s_history[i].answer, s, FormatMode::Standard);
			ss = s;
		}

		auto elem = hbox(
			text(L"\u2570\u2500[" + std::to_wstring(s_history.size() - i) + L"]") | color(Color::GrayDark),
			text(L"\u2500\u2500> ") | color(Color::GrayDark),
			text(ss) | color(Color::Green)
		);
		if (!s_history[i].errs.empty())
		{
			Elements errs;
			for (auto& e : s_history[i].errs)
			{
				errs.push_back(text(tostring(e.type) + " - " + tostring(e.cls) + ": " + e.err) | getcolor(e.type));
			}
			elem = vbox(std::move(errs));
		}

		elems.push_back(
			vbox({
				text(s_history[i].input),
				elem,
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
	//TimeAll();
	//return 0;

	if (argc > 1)
	{
		bool exit;
		const auto res = TestPrecision(argc, argv, exit);
		if (exit) return res;
	}

	NExpressionContext ctx { getHistoryRef };
	ctx.set(OpmComplex(0, 1), "i");
	ctx.set(Constants::pi, "pi");
	
	std::string cmd;
	InputOption opt;
	opt.on_enter = [&]
	{
		bool de = false;
		bool se = false;
		std::string inp = cmd;
		if (cmd.substr(0, 3) == "/d ")
		{
			se = de = true;
			inp = cmd.substr(3);
		}
		if (cmd.substr(0, 3) == "/s ")
		{
			se = true;
			inp = cmd.substr(3);
		}
		auto errs = NErrorCollection{};
		auto expr = Expression::parse(errs, ctx, inp);
		if (de && errs.empty())
		{
			NDerivative d;
			expr = Expression::rewrite(expr, ctx, d);
		}
		if (se && errs.empty()) 
		{
			NSimplify s;
			expr = Expression::rewrite(expr, ctx, s);
		}

		auto ce = Expression::compile(errs, expr);
		if (!errs.empty())
		{
			s_history.push_back({ cmd, errs, NExpression{}, wrap(Constants::nan) });
		}
		else if (expr.type == NExpressionType::FunctionDefinition)
		{
			std::string fnName = expr.fnData.front();

			ctx.set(FunctionImplementation{ expr, ce, std::vector<std::string> {expr.fnData.begin() + 1, expr.fnData.end()} }, FunctionDefinition{ fnName, static_cast<uint32_t>(expr.fnData.size() - 1) });
			s_history.push_back({ cmd, errs, expr, OpmValue {} });
		}
		else if (expr.type == NExpressionType::VariableAssignment)
		{
			auto res = ce.exec(errs, ctx);
			ctx.set(res, expr.varName);
			s_history.push_back({ cmd, errs, expr, res });
		}
		else
		{
			auto res = ce.exec(errs, ctx);
			s_history.push_back({ cmd, errs, expr, res });
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
