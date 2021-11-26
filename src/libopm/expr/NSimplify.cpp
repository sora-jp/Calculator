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
NExpressionNode* NSimplify::rewrite(const NExpressionNode* node)
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
		if (Expression::isConstant(node->left) && is_zero(Expression::constantEval(node->left)))  return is_sub(node) ? neg(rewriteInternal(node->right)) : rewriteInternal(node->right);
		if (Expression::isConstant(node->right) && is_zero(Expression::constantEval(node->right))) return rewriteInternal(node->left);
	}
	if (is_mul(node) || is_div(node))
	{
		if (is_mul(node))
		{
			if (Expression::isConstant(node->left) && is_one(Expression::constantEval(node->left))) return rewriteInternal(node->right);
			if (Expression::isConstant(node->right) && is_zero(Expression::constantEval(node->right))) return constant(0e0_opm);
			if (Expression::isConstant(node->left) && is_neg_one(Expression::constantEval(node->left))) return neg(rewriteInternal(node->right));
		}

		if (Expression::isConstant(node->right) && is_one(Expression::constantEval(node->right))) return rewriteInternal(node->left);
		if (Expression::isConstant(node->left) && is_zero(Expression::constantEval(node->left))) return constant(0e0_opm);
		if (Expression::isConstant(node->right) && is_neg_one(Expression::constantEval(node->right))) return neg(rewriteInternal(node->left));
	}

	totFailed++;
	return new NExpressionNode{ node->op, rewriteInternal(node->left), rewriteInternal(node->right) };
}
