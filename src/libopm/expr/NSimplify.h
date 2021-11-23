#pragma once
#include "NExpression.h"
#include "NExpressionNode.h"

class NSimplify final : public NExpressionRewriter
{
	NExpressionNode* rewrite(const NExpressionNode* node) override;
};