#pragma once
#include <cassert>
#include <map>

#include "OpmNum.hpp"
#include "StackBindings.hpp"

struct Token;
typedef OpmNum(*UnaryOp)(const OpmNum&);
typedef OpmNum(*BinaryOp)(const OpmNum&, const OpmNum&);

class Operation
{
	bool m_valid = true;
	UnaryOp m_unary = nullptr;
	BinaryOp m_binary = nullptr;
	OpmNum m_constant;

public:
	std::string m_debug;
	Operation(const std::string& debug = "") : m_valid(false), m_debug(debug) {}
	explicit Operation(const UnaryOp op, const std::string& debug = "") : m_unary(op), m_debug(debug) {}
	explicit Operation(const BinaryOp op, const std::string& debug = "") : m_binary(op), m_debug(debug) {}
	explicit Operation(const OpmNum& constant, const std::string& debug = "") : m_constant(constant), m_debug(debug) {}

	void operator()(OpmStack<10>& stack) const
	{
		assert(m_valid);
		
		if (m_unary) stack.Push(m_unary(stack.Pop()));
		else if (m_binary) stack.Push(m_binary(stack.Pop(), stack.Pop()));
		else stack.Push(m_constant);
	}
};

class Expression
{
	std::vector<Operation> m_ops;

public:
	void PushOp(const Operation& op) { m_ops.push_back(op); }

	OpmNum operator()() const
	{
		OpmStack<10> stack;
		for (const auto& op : m_ops) op(stack);
		return stack.Pop();
	}

	void Print()
	{
		for (auto& op : m_ops) std::cout << op.m_debug << std::endl;
	}
};

class ExpressionParser
{
	std::map<std::string, UnaryOp> m_unaryFns = {};
	std::map<std::string, BinaryOp> m_binaryFns = {};

public:
	void RegisterFn(const std::string& id, const UnaryOp op) { m_unaryFns[id] = op; }
	void RegisterFn(const std::string& id, const BinaryOp op) { m_binaryFns[id] = op; }
	Operation ToOp(const Token& token, bool unary = false) const;
	
	[[nodiscard]] Expression Parse(const std::string& string) const;
};