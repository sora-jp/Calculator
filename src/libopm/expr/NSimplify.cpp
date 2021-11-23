#include "NSimplify.h"
#include "Expressions.h"
#include <stack>

NExpressionNode* NSimplify::rewrite(const NExpressionNode* node)
{
	if (node->op.type == NOpType::Binary && (node->op.payload == "+" || node->op.payload == "-"))
	{
		if (Expression::isConstant(node->left)  && is_zero()) return rewrite(node->right);
		if (Expression::isConstant(node->right)) 
	}

	return node->deepCopy();
}