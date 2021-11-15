#pragma once
#include <map>

#include "../rt_poly/OpmDynamic.h"
#include <string>
#include <vector>

#include "StackBindings.hpp"
#define EXPR_STACK_DEPTH 16

enum class NOpType
{
	Invalid, Binary, Unary, Constant, Variable, FunctionCall
};

typedef OpmValue(*BinaryOp)(const OpmValue&, const OpmValue&);
typedef OpmValue(*UnaryOp)(const OpmValue&);

struct NOperation
{
	NOpType type = NOpType::Invalid;
	union {
		std::string payload = {};
		OpmValue constant;
	};

	NOperation() : payload() {}
	~NOperation()
	{
		if (type == NOpType::Constant) constant.~OpmValue();
		else payload.~basic_string();
	}

	NOperation(NOpType type, const std::string& payload) : type(type), payload(payload) {}
	NOperation(NOpType type, const OpmValue& constant) : type(type), constant(constant) {}

	NOperation(const NOperation& other)
	{
		type = other.type;
		if (type == NOpType::Constant) constant = other.constant;
		else payload = other.payload;
	}

	NOperation& operator=(const NOperation& other)
	{
		type = other.type;
		if (type == NOpType::Constant) constant = other.constant;
		else payload = other.payload;
		return *this;
	}
};

class NExpressionContext
{
	friend struct NCompiledOp;
	std::map<std::string, OpmValue> m_variables;

public:
	NExpressionContext() = default;
	OpmValue get(const std::string& s) const { return m_variables.at(s); }
	void set(const OpmNum& val, const std::string& s) { m_variables[s] = wrap(val); }
	void set(const OpmComplex& val, const std::string& s) { m_variables[s] = wrap(val); }
};

struct NCompiledOp
{
	NOpType type;

	std::string var;
	OpmValue constant;
	union
	{
		UnaryOp unary = nullptr;
		BinaryOp binary;
	};

	NCompiledOp(const std::string& var) : type(NOpType::Variable), var(var) {}
	NCompiledOp(const OpmValue& constant) : type(NOpType::Constant), constant(constant) {}
	NCompiledOp(UnaryOp op) : type(NOpType::Unary), unary(op) {}
	NCompiledOp(BinaryOp op) : type(NOpType::Binary), binary(op) {}

	void operator()(const NExpressionContext& ctx, OpmStack<EXPR_STACK_DEPTH>& stack) const
	{
		if (type == NOpType::Constant) stack.Push(constant);
		if (type == NOpType::Variable) stack.Push(ctx.get(var)); //FIXME
		if (type == NOpType::Unary) stack.Push(unary(stack.Pop()));
		if (type == NOpType::Binary) stack.Push(binary(stack.Pop(), stack.Pop()));
	}
};

struct NExpressionNode
{
	NOperation op;

	NExpressionNode* parent = nullptr;
	NExpressionNode* left = nullptr;
	NExpressionNode* right = nullptr;
};

struct NExpression
{
	NExpressionNode top;
};

class NCompiledExpression
{
	friend class NExpressionParser;
	std::vector<NCompiledOp> m_ops;

public:
	OpmValue exec(const NExpressionContext& ctx)
	{
		OpmStack<EXPR_STACK_DEPTH> stack;
		for (const auto& op : m_ops)
		{
			op(ctx, stack);
		}
		auto res = stack.Pop();
		return res.roundToNearest();
	}
};

class NExpressionParser
{
	std::unordered_map<std::string, UnaryOp> m_unary;
	std::unordered_map<std::string, BinaryOp> m_binary;

	void compileRecursive(std::vector<NCompiledOp>& ops, const NExpressionNode* node);

public:
	NExpressionParser();
	void registerFn(const std::string& name, UnaryOp val) { m_unary[name] = val; }
	void registerFn(const std::string& name, BinaryOp val) { m_binary[name] = val; }

	NExpression parse(const std::string& in);
	NCompiledExpression compile(const NExpression& expr);
};