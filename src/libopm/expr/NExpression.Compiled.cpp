#include <cassert>

#include "NExpression.h"
#include "cordic/Tables.hpp"

void NCompiledOp::operator()(NErrorCollection& outErrors, const NExpressionContext& ctx, OpmStack<EXPR_STACK_DEPTH>& stack) const
{
	if (type == NOpType::Constant) stack.Push(constant);
	if (type == NOpType::Variable) 
	{
		if (ctx.m_variables.find(var) == ctx.m_variables.end())
		{
			outErrors.push_back(NExpressionError{ ErrorType::Error, ErrorClass::Evaluation, "Undefined variable '" + var + "'" });
			return;
		}
		stack.Push(ctx.get(var)); //FIXME
	}
	if (type == NOpType::Unary) stack.Push(unary(stack.Pop()));
	if (type == NOpType::Binary) stack.Push(binary(stack.Pop(), stack.Pop()));
	if (type == NOpType::FunctionCall) 
	{
		NExpressionContext ctx2 = ctx;
		auto* fnimp = ctx.get(fn);
		if (fnimp == nullptr) 
		{
			outErrors.push_back(NExpressionError{ ErrorType::Error, ErrorClass::Evaluation, "Undefined function '" + fn.name + "(" + std::to_string(fn.paramCount) + ")'" });
			return;
		}
		for (uint32_t i = 0; i < fn.paramCount; i++)
		{
			ctx2.set(stack.Pop(), fnimp->arguments[fn.paramCount - (i + 1)]);
		}
		stack.Push(fnimp->cachedExpr.exec(outErrors, ctx2));
	}
}

OpmValue NCompiledExpression::exec(NErrorCollection& outErrors, const NExpressionContext& ctx) const
{
	OpmStack<EXPR_STACK_DEPTH> stack;
	if (!outErrors.empty()) return wrap(Constants::nan);
	for (const auto& op : m_ops)
	{
		op(outErrors, ctx, stack);
		if (!outErrors.empty()) return wrap(Constants::nan);
	}
	auto res = stack.Pop();
	return res.roundToNearest();
}

void NExpressionContext::set(const FunctionImplementation& val, const FunctionDefinition& fn)
{
	m_userFuncs.emplace_back(fn, val);
}

const FunctionImplementation* NExpressionContext::get(const FunctionDefinition& f) const
{
	for (const auto& v : m_userFuncs)
	{
		if (v.first.paramCount == f.paramCount && v.first.name == f.name) return &v.second;
	}
	return nullptr;
}

bool NExpressionContext::has(const FunctionDefinition& f) const
{
	for (const auto& v : m_userFuncs)
	{
		if (v.first.paramCount == f.paramCount && v.first.name == f.name) return true;
	}
	return false;
}
