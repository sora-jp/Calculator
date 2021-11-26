#pragma once
#include "NExpression.h"
#include "NExpressionNode.h"

class NSimplify final : public NExpressionRewriter
{
	uint32_t totNodes = 0, totFailed = 0;
	NExpressionNode* rewrite(const NExpressionNode* node) override;
	NExpressionNode* rewriteInternal(const NExpressionNode* node);
};