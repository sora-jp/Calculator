#pragma once
#include "../rt_poly/OpmDynamic.h"
#include <string>
#include <vector>

enum class NOpType
{
	Invalid, Binary, Unary, Constant, Variable, FunctionCall
};

typedef OpmValue(*BinaryOp)(const OpmValue&, const OpmValue&);
typedef OpmValue(*UnaryOp)(const OpmValue&);

struct NOperation
{
	NOpType type;
	std::string payload;
};

struct NExpressionNode
{
	NOperation op;

	NExpressionNode* parent;
	NExpressionNode* left;
	NExpressionNode* right;
};

struct NExpression
{
	NExpressionNode top;
};

class NCompiledExpression
{
	
};

class NExpressionParser
{
public:
	NExpression parse(const std::string& in);
	NCompiledExpression compile(const NExpression& expr);
};