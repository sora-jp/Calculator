#pragma once
#include <map>

#include "../rt_poly/OpmDynamic.h"
#include "NExpressionNode.h"
#include <string>
#include <vector>

#include "StackBindings.hpp"
#define EXPR_STACK_DEPTH 16

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


class NCompiledExpression
{
	friend class NExpressionParser;
	std::vector<NCompiledOp> m_ops;

public:
	OpmValue exec(const NExpressionContext& ctx) const
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

class NExpressionRewriter
{
	friend class NExpressionParser;
public:
	virtual ~NExpressionRewriter() = default;
	virtual NExpressionNode* rewrite(const NExpressionNode* node) = 0;
};

class NExpressionParser
{
	std::unordered_map<std::string, UnaryOp> m_unary;
	std::unordered_map<std::string, BinaryOp> m_binary;

	void compileRecursive(std::vector<NCompiledOp>& ops, const NExpressionNode* node) const;
	bool ConstantFoldR(NExpressionNode* node) const;
	void ConstantFoldAll(NExpressionNode* node) const;

public:
	NExpressionParser();
	NExpressionParser(std::unordered_map<std::string, UnaryOp> unary, std::unordered_map<std::string, BinaryOp> binary) : m_unary(std::move(unary)), m_binary(std::move(binary)) {}
	void registerFn(const std::string& name, UnaryOp val) { m_unary[name] = val; }
	void registerFn(const std::string& name, BinaryOp val) { m_binary[name] = val; }

	NExpression parse(const std::string& in) const;
	NExpression rewrite(NExpressionRewriter& rew, const NExpression& expr) const;
	NCompiledExpression compile(const NExpression& expr) const;

	static bool IsConstant(const NExpressionNode* node);
	OpmValue ConstantEval(const NExpressionNode* node) const;
	static void Print(const NExpression& expr);
};