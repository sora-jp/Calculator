#include <cassert>

#include "NExpression.h"

void NCompiledOp::operator()(const NExpressionContext& ctx, OpmStack<EXPR_STACK_DEPTH>& stack) const
{
	if (type == NOpType::Constant) stack.Push(constant);
	if (type == NOpType::Variable) stack.Push(ctx.get(var)); //FIXME
	if (type == NOpType::Unary) stack.Push(unary(stack.Pop()));
	if (type == NOpType::Binary) stack.Push(binary(stack.Pop(), stack.Pop()));
	if (type == NOpType::FunctionCall) 
	{
		NExpressionContext ctx2 = ctx;
		auto& fnimp = ctx.get(fn);
		for (uint32_t i = 0; i < fn.paramCount; i++)
		{
			ctx2.set(stack.Pop(), fnimp.arguments[fn.paramCount - (i + 1)]);
		}
		stack.Push(fnimp.cachedExpr.exec(ctx2));
	}
}

OpmValue NCompiledExpression::exec(const NExpressionContext& ctx) const
{
	OpmStack<EXPR_STACK_DEPTH> stack;
	for (const auto& op : m_ops)
	{
		op(ctx, stack);
	}
	auto res = stack.Pop();
	return res.roundToNearest();
}

void NExpressionContext::set(const FunctionImplementation& val, const FunctionDefinition& fn)
{
	m_userFuncs.emplace_back(fn, val);
}

const FunctionImplementation& NExpressionContext::get(const FunctionDefinition& f) const
{
	for (auto& v : m_userFuncs)
	{
		if (v.first.paramCount == f.paramCount && v.first.name == f.name) return v.second;
	}
	assert(false);
}