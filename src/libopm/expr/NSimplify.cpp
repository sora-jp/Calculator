#include "NSimplify.h"
#include "Expressions.h"
#include <stack>

bool is_one(const OpmValue& val)
{
	if (val.type() == ValueType::Real) return *unwrap<OpmNum>(val) == 1e0_opm;
	if (val.type() == ValueType::Complex) 
	{
		const auto& num = *unwrap<OpmComplex>(val);
		return num.real == 1e0_opm && is_zero(num.imag);
	}

	return false;
}

bool is_neg_one(const OpmValue& val)
{
	if (val.type() == ValueType::Real) return *unwrap<OpmNum>(val) == -1e0_opm;
	if (val.type() == ValueType::Complex)
	{
		const auto& num = *unwrap<OpmComplex>(val);
		return num.real == -1e0_opm && is_zero(num.imag);
	}

	return false;
}

// https://stackoverflow.com/questions/7540227/strategies-for-simplifying-math-expressions
NExpressionNode* NSimplify::rewrite(const NExpressionContext& ctx, const NExpressionNode* node)
{
	NExpressionNode* cur = node->copy();
	while (true)
	{
		totNodes = totFailed = 0;
		auto* tmp = rewriteInternal(cur);
		delete cur;
		cur = tmp;
		if (totNodes == totFailed) break;
	}

	return cur;
}

NExpressionNode* NSimplify::rewriteInternal(const NExpressionNode* node)
{
	if (node == nullptr) return nullptr;
	totNodes++;

	if (is_add(node) || is_sub(node))
	{
		if (Expression::isConstant(node->child(0)) && is_zero(Expression::constantEval(node->child(0))))  return is_sub(node) ? neg(rewriteInternal(node->child(1))) : rewriteInternal(node->child(1));
		if (Expression::isConstant(node->child(1)) && is_zero(Expression::constantEval(node->child(1)))) return rewriteInternal(node->child(0));
	}
	if (is_mul(node) || is_div(node))
	{
		if (is_mul(node))
		{
			if (Expression::isConstant(node->child(0)) && is_one(Expression::constantEval(node->child(0)))) return rewriteInternal(node->child(1));
			if (Expression::isConstant(node->child(1)) && is_zero(Expression::constantEval(node->child(1)))) return constant(0e0_opm);
			if (Expression::isConstant(node->child(0)) && is_neg_one(Expression::constantEval(node->child(0)))) return neg(rewriteInternal(node->child(1)));
		}

		if (Expression::isConstant(node->child(1)) && is_one(Expression::constantEval(node->child(1)))) return rewriteInternal(node->child(0));
		if (Expression::isConstant(node->child(0)) && is_zero(Expression::constantEval(node->child(0)))) return constant(0e0_opm);
		if (Expression::isConstant(node->child(1)) && is_neg_one(Expression::constantEval(node->child(1)))) return neg(rewriteInternal(node->child(0)));
	}
	if (is_pow(node))
	{
		if (Expression::isConstant(node->child(0)) && is_one(Expression::constantEval(node->child(0)))) return constant(1e0_opm);
		if (Expression::isConstant(node->child(0)) && is_zero(Expression::constantEval(node->child(0)))) return constant(0e0_opm);

		if (Expression::isConstant(node->child(1)) && is_one(Expression::constantEval(node->child(1)))) return rewriteInternal(node->child(0));
		if (Expression::isConstant(node->child(1)) && is_zero(Expression::constantEval(node->child(1)))) return constant(1e0_opm);
	}
	
	auto* o = new NExpressionNode(node->op);
	o->children.reserve(node->children.size());
	for (const auto* c : node->children) o->children.push_back(rewriteInternal(c));

	totFailed++;
	return o;
}
