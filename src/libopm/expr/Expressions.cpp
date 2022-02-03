#include "Expressions.h"

static OpmValue ident(const OpmValue& val) { return val; }

static const NExpressionParser s_parser
({
	{"-", operator-},
	{"+", ident},
	{"sin", sin},
	{"cos", cos},
	{"tan", tan},
	{"sinh", sinh},
	{"cosh", cosh},
	{"tanh", tanh},
	{"asin", asin},
	{"acos", acos},
	{"atan", atan},
	{"sqrt", sqrt},
	{"exp", exp},
	{"log", log10},
	{"log2", log2},
	{"ln", ln}
},
{
	{"+", operator+},
	{"-", operator-},
	{"*", operator*},
	{"/", operator/},
	{"^", pow},
	{"pow", pow},
	{"log", log}
});

NExpression Expression::parse(NErrorCollection& outErrors, const std::string& str)
{
	return s_parser.parse(outErrors, str);
}

NExpression Expression::rewrite(const NExpression& expr, NExpressionRewriter& writer)
{
	return s_parser.rewrite(writer, expr);
}

NCompiledExpression Expression::compile(NErrorCollection& outErrors, const NExpression& expr)
{
	return s_parser.compile(outErrors, expr);
}

bool Expression::isConstant(const NExpressionNode* node)
{
	return s_parser.IsConstant(node);
}

OpmValue Expression::constantEval(const NExpressionNode* node)
{
	return s_parser.ConstantEval(node);
}
