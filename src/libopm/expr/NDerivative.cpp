#include "NDerivative.h"
#include "Expressions.h"

NExpressionNode* NDerivative::rewrite(const NExpressionNode* node)
{
	return derive(node);
}

NExpressionNode* NDerivative::derive(const NExpressionNode* node) const
{
	if (node == nullptr) return nullptr;
	NExpressionNode* output = nullptr;

	if (Expression::isConstant(node) || (node->op.type == NOpType::Variable && node->op.payload != "x"))
	{
		output = new NExpressionNode{ {NOpType::Constant, wrap(0e0_opm)} };
	}
	if (node->op.type == NOpType::Variable && node->op.payload == "x")
	{
		output = new NExpressionNode{ {NOpType::Constant, wrap(1e0_opm)} };
	}

	if (node->op.type == NOpType::Binary && node->op.payload == "*")
	{
		output = add(mul(node->child(0)->copy(), derive(node->child(1))), mul(node->child(1)->copy(), derive(node->child(0))));
	}
	if (node->op.type == NOpType::Binary && (node->op.payload == "+" || node->op.payload == "-"))
	{
		auto* l = derive(node->child(0)), * r = derive(node->child(1));
		output = node->op.payload == "+" ? add(l, r) : sub(l, r);
	}
	if (node->op.type == NOpType::Binary && node->op.payload == "/")
	{
		output = div(sub(mul(node->child(1)->copy(), derive(node->child(0))), mul(node->child(0)->copy(), node->child(1))), mul(node->child(1)->copy(), node->child(1)->copy()));
	}
	if (node->op.type == NOpType::Unary && node->op.payload == "-")
	{
		output = neg(derive(node->child(0)));
	}
	if (node->op.type == NOpType::FunctionCall && node->op.payload == "pow")
	{
		auto *ld = derive(node->child(0)), *rd = derive(node->child(1));
		auto *l = node->child(0), *r = node->child(1);
		
		auto* lp = mul(r->copy(), pow(l->copy(), sub(r->copy(), constant(1e0_opm))));
		auto* rp = mul(pow(l->copy(), r->copy()), ln(l->copy()));
		output = add(mul(lp, ld), mul(rp, rd));
	}
	if (node->op.type == NOpType::FunctionCall && node->op.payload == "exp")
	{
		output = mul(derive(node->child(0)), node->copy());
	}
	if (node->op.type == NOpType::FunctionCall && node->op.payload == "ln")
	{
		output = mul(derive(node->child(0)), div(constant(1e0_opm), node->child(1)->copy()));
	}
	
	return output;
}