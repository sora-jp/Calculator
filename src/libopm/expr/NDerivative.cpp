#include "NDerivative.h"

NExpressionNode* NDerivativeRewriter::rewrite(const NExpressionNode* node)
{
	return derive(node);
}

NExpressionNode* NDerivativeRewriter::derive(const NExpressionNode* node) const
{
	if (node == nullptr) return nullptr;
	NExpressionNode* output = nullptr;

	if (NExpressionParser::IsConstant(node) || (node->op.type == NOpType::Variable && node->op.payload != "x"))
	{
		output = new NExpressionNode{ {NOpType::Constant, wrap(0e0_opm)} };
	}
	if (node->op.type == NOpType::Variable && node->op.payload == "x")
	{
		output = new NExpressionNode{ {NOpType::Constant, wrap(1e0_opm)} };
	}

	if (node->op.type == NOpType::Binary && node->op.payload == "*")
	{
		output = add(mul(node->left->deepCopy(), derive(node->right)), mul(node->right->deepCopy(), derive(node->left)));
	}
	if (node->op.type == NOpType::Binary && (node->op.payload == "+" || node->op.payload == "-"))
	{
		auto* l = derive(node->left), * r = derive(node->right);
		output = node->op.payload == "+" ? add(l, r) : sub(l, r);
	}
	if (node->op.type == NOpType::Binary && node->op.payload == "/")
	{
		output = div(sub(mul(node->right->deepCopy(), derive(node->left)), mul(node->left->deepCopy(), node->right)), mul(node->right->deepCopy(), node->right->deepCopy()));
	}
	if (node->op.type == NOpType::Unary && node->op.payload == "-")
	{
		output = neg(derive(node->left));
	}
	if (node->op.type == NOpType::FunctionCall && node->op.payload == "pow")
	{
		auto *ld = derive(node->left), *rd = derive(node->right);
		auto *l = node->left, *r = node->right;
		
		auto* lp = mul(r->deepCopy(), pow(l->deepCopy(), sub(r->deepCopy(), constant(1e0_opm))));
		auto* rp = mul(pow(l->deepCopy(), r->deepCopy()), ln(l->deepCopy()));
		output = add(mul(lp, ld), mul(rp, rd));
	}
	if (node->op.type == NOpType::FunctionCall && node->op.payload == "exp")
	{
		output = mul(derive(node->left), node->deepCopy());
	}
	if (node->op.type == NOpType::FunctionCall && node->op.payload == "ln")
	{
		output = mul(derive(node->left), div(constant(1e0_opm), node->left->deepCopy()));
	}
	
	return output;
}